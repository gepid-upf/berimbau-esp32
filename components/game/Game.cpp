#include <Game.h>

#include <freertos/task.h>

#include <esp_spiffs.h>
#include <esp_vfs.h>

#include <Interface.h>

#include <esp_log.h>

const char *Game::TAG = "GAME";

Game::State Game::state = State::IDLE;
SemaphoreHandle_t Game::mtx = nullptr;

Button *Game::b_caxixi = nullptr;
Button *Game::b_moeda = nullptr;
Button *Game::b_solta = nullptr;
Button *Game::b_presa = nullptr;

Audio *Game::a_caxixi = nullptr;
Audio *Game::a_moeda = nullptr;
Audio *Game::a_solta = nullptr;
Audio *Game::a_presa = nullptr;

Led *Game::l_caxixi = nullptr;
Led *Game::l_moeda = nullptr;
Led *Game::l_solta = nullptr;
Led *Game::l_presa = nullptr;

Urm37 Game::urm(GPIO_NUM_12, GPIO_NUM_27);

std::vector<std::string> Game::rec_list;
std::vector<beat_t> Game::rec_array;
bool Game::first_rec = true;

char Game::rec_buf[56];
int Game::rm_ret = 0;

beat_t *Game::rec_ptr = nullptr;
uint16_t Game::rec_sz = 0;

int Game::rpt_st = 0;
uint8_t Game::listens = 0;
uint8_t Game::tries = 0;

uint64_t Game::delta = 0;
const uint16_t Game::MAX_RPT_DELAY = 250;

char Game::player[52];
char Game::rec_name[43];

void Game::task(void *nullpar)
{
    State temp_state;
    mtx = xSemaphoreCreateMutex();

    init_spiffs();

    Interface::loaded();

    while(true){
        xSemaphoreTake(mtx, portMAX_DELAY);
        temp_state = state;
        xSemaphoreGive(mtx);

        switch(temp_state){
        case State::RECORD:
        case State::PLAY:
            if(b_moeda->get_state() == Button::State::PRESSED) {
                a_moeda->set_active();
                a_solta->set_active(false); // Moeda (coin) presses the string and the solta (loose) sound stops.
                l_moeda->blink(a_moeda->get_length()/44.101);
                l_solta->turn_off();
                if(temp_state == State::RECORD)
                    record(Instrument::MOEDA);
            }
            if(b_presa->get_state() == Button::State::PRESSED){
                a_presa->set_active();
                a_solta->set_active(false);
                l_presa->blink(a_presa->get_length()/44.101);
                l_solta->turn_off();
                if(temp_state == State::RECORD)
                    record(Instrument::PRESA);
            }
            if(b_caxixi->get_state() == Button::State::PRESSED){
                a_caxixi->set_active();
                l_caxixi->blink(a_caxixi->get_length()/44.101);
                if(temp_state == State::RECORD)
                    record(Instrument::CAXIXI);
            }
            if(b_solta->get_state() == Button::State::PRESSED){
                a_solta->set_active();
                l_solta->blink(a_solta->get_length()/44.101);
                if(temp_state == State::RECORD)
                    record(Instrument::SOLTA);
            }
            break;
        case State::LOAD_REC_LIST:
            load_rec_list();
            break;
        case State::ERASE:
            rm();
            break;
        case State::PLAY_LOADED:
            play_loaded();
            break;
        case State::REPEAT:
            repeat();
            break;
        case State::ADD_PLAYER:
            add_player();
            break;
        case State::UNLOAD:
            unload();
            break;
        default:
            break;
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void Game::set_button(Button *btn, Instrument instr)
{
    switch(instr){
    case Instrument::CAXIXI:
        b_caxixi = btn;
        break;
    case Instrument::MOEDA:
        b_moeda = btn;
        break;
    case Instrument::PRESA:
        b_presa = btn;
        break;
    case Instrument::SOLTA:
        b_solta = btn;
        break;
    }
}

void Game::set_audio(Audio *aud, Instrument instr)
{
    switch(instr){
    case Instrument::CAXIXI:
        a_caxixi = aud;
        break;
    case Instrument::MOEDA:
        a_moeda = aud;
        break;
    case Instrument::PRESA:
        a_presa = aud;
        break;
    case Instrument::SOLTA:
        a_solta = aud;
        break;
    }
}

void Game::set_led(Led *led, Instrument instr)
{
    switch(instr){
    case Instrument::CAXIXI:
        l_caxixi = led;
        break;
    case Instrument::MOEDA:
        l_moeda = led;
        break;
    case Instrument::PRESA:
        l_presa = led;
        break;
    case Instrument::SOLTA:
        l_solta = led;
        break;
    }
}

void Game::set_state(State sta)
{
    xSemaphoreTake(mtx, portMAX_DELAY);
    state = sta;
    xSemaphoreGive(mtx);
}

void Game::urm_task(void *nullpar)
{
    urm.init();

    Interface::loaded();

    while(true){
        switch(state){
        case State::PLAY:
            if(urm.pulse_trigger()) // No need for vTaskDelay. It already has a semaphore inside.
                Audio::set_muffle_cutoff(urm.get_pulse_us()*20);
            break;
        default:
            vTaskDelay(250 / portTICK_PERIOD_MS);
            break;
        }
    }
}

void Game::init_spiffs()
{
    ESP_LOGI(TAG, "Initializing SPIFFS");
    
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 1,
      .format_if_mount_failed = false
    };
    
    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

}

// https://github.com/loboris/ESP32_spiffs_example/blob/master/main/testSpiffs.c
std::vector<std::string> Game::ls(char *path)
{
    std::vector<std::string> ret;
    DIR *dir = NULL;
    struct dirent *ent = nullptr;

    // Open directory
    dir = opendir(path);
    if(!dir){
        ESP_LOGE(TAG, "Error opening directory");
        return ret;
    }

    // Read directory entries
    while((ent = readdir(dir)))
        ret.push_back(ent->d_name);

    closedir(dir);

    return ret;
}

// https://github.com/loboris/ESP32_spiffs_example/blob/master/main/testSpiffs.c
int64_t Game::get_sz(const char *file)
{
    struct stat sb;

    int statok = stat(file, &sb);

    if(statok)
        return -1;
    else
        return sb.st_size;  
    
}

void Game::record(Instrument instr)
{
    static uint64_t start_time = 0;
    if(first_rec){
        start_time = xTaskGetTickCount();
        first_rec = false;
    }

    beat_t beat {
        .d_time = (uint32_t)(xTaskGetTickCount() - start_time) * portTICK_PERIOD_MS,
        .res0 = 0x0000,
        .instr = (uint8_t)instr,
        .res1 = 0x00
    };

    rec_array.push_back(beat);
}

void Game::rec_cancel()
{
    set_state(State::IDLE);

    first_rec = true;
    rec_array.clear();
}

int32_t Game::rec_end()
{
    set_state(State::IDLE);

    size_t total, used, available;

    wait_sounds();
    esp_spiffs_info(nullptr, &total, &used);

    available = total - used;

    return rec_array.size() <= available ? rec_array.size() : -1;
}

void Game::rec_save(char *file)
{
    char buf[56];
    sprintf(buf, "/spiffs/recs/%s.dat", file);

    // Check if space available!
    FILE *fil = fopen(buf, "wb");
    for(uint16_t i = 0; i < rec_array.size(); i++)
        fwrite((const void*)&rec_array[i], sizeof(beat_t), 1, fil);
    
    fclose(fil);
    

    first_rec = true;
    rec_array.clear();
}

void Game::load_rec_list()
{
    rec_list = ls("/spiffs/recs");
    Interface::loaded();    
    state = State::IDLE;
}

std::vector<std::string> Game::get_rec_list()
{
    std::vector<std::string> tmp = rec_list;
    rec_list.clear();
    return tmp;
}

int64_t Game::get_file_sz(const char *file)
{
    char buf[56];
    sprintf(buf, "/spiffs/recs/%s", file);
    return get_sz(buf);
}

bool Game::overwrite(char *file)
{
    char buf[56];
    sprintf(buf, "/spiffs/recs/%s.dat", file);
    return get_sz(buf) < 0 ? false : true;
}

void Game::wait_sounds()
{
    bool playing;
    do {
        playing = false;
        for(uint8_t i = 0; i < Audio::get_voices_count(); i++)
            playing |= Audio::get_voice_ptr(i)->is_playing();
        vTaskDelay(50 / portTICK_PERIOD_MS);
    } while(playing);
}

void Game::erase(const char *rec)
{
    sprintf(rec_buf, "/spiffs/recs/%s", rec);
    set_state(State::ERASE);
}

void Game::rm()
{
    state = State::IDLE;
    rm_ret = remove(rec_buf);
    Interface::loaded();
}

int Game::get_erase_st()
{
    return rm_ret;
}

bool Game::alloc_rec(const char *file)
{
    rec_sz = get_file_sz(file);
    rec_ptr = nullptr;

    if(heap_caps_get_largest_free_block(0) >= rec_sz)
        return (bool)(rec_ptr = (beat_t*)malloc(rec_sz));

    return false;
}

void Game::load(const char *file)
{
    strcpy(rec_name, file);

    char buf[56];
    sprintf(buf, "/spiffs/recs/%s", file);
    FILE *recfile = fopen(buf, "rb");

    rec_sz /= sizeof(beat_t);

    fread(rec_ptr, sizeof(beat_t), rec_sz, recfile);

    fclose(recfile);

    listens = 0;
    tries = 0;
    rpt_st = -9;

    Interface::loaded();

    state = State::IDLE;
}

void Game::play_loaded()
{
    uint32_t last = 0;

    // Initial delay?
    State temp_state;

    listens++;

    rpt_st = -9;

    for(int i = 0; i < rec_sz; i++){
        xSemaphoreTake(mtx, portMAX_DELAY);
        temp_state = state; 
        xSemaphoreGive(mtx);

        if(temp_state != State::PLAY_LOADED)
            return;

        vTaskDelay( (rec_ptr[i].d_time - last) / portTICK_PERIOD_MS);
        last = rec_ptr[i].d_time;

        switch((Instrument)rec_ptr[i].instr){
        case Instrument::CAXIXI:
            a_caxixi->set_active();
            l_caxixi->blink(a_caxixi->get_length()/44.101);
            break;
        case Instrument::MOEDA:
            a_moeda->set_active();
            a_solta->set_active(false); // Moeda (coin) presses the string and the solta (loose) sound stops.
            l_moeda->blink(a_moeda->get_length()/44.101);
            l_solta->turn_off();
            break;
        case Instrument::PRESA:
            a_presa->set_active();
            a_solta->set_active(false);
            l_presa->blink(a_presa->get_length()/44.101);
            l_solta->turn_off();
            break;
        case Instrument::SOLTA:
            a_solta->set_active();
            l_solta->blink(a_solta->get_length()/44.101);
            break;
        default:
            break;
        }        
    }

    set_state(State::IDLE);

    rpt_st = -8;

    Interface::loaded();
}

void Game::unload()
{
    state = State::IDLE; 
    
    wait_sounds();
    free(rec_ptr);
    rec_ptr = nullptr;

    // Save log
    char buf[70];
    sprintf(buf, "/spiffs/logs/%s.csv", player);
    FILE *fil = fopen(buf, "a");
    char *rtm = strtok(rec_name, ".");

    char log_line[80];
    switch(rpt_st){
    case 0:
        sprintf(log_line, "%s,%u,%u,%u%%\n", rtm, get_listen(), get_tries(), get_precision());
        break;
    case -1:
        sprintf(log_line, "%s,%u,%u,%s\n", rtm, get_listen(), get_tries(), "acelerou ritmo");
        break;
    case -2:
        sprintf(log_line, "%s,%u,%u,%s\n", rtm, get_listen(), get_tries(), "instrumento errado");
        break;
    case -3:
        sprintf(log_line, "%s,%u,%u,%s\n", rtm, get_listen(), get_tries(), "atrasou ritmo");
        break;
    case -8:
        sprintf(log_line, "%s,%u,%u,%s\n", rtm, get_listen(), get_tries(), "nao tocou");
        break;
    case -9:
        sprintf(log_line, "%s,%u,%u,%s\n", rtm, get_listen(), get_tries(), "nao ouviu");
        break;
    default:
        break;
    }

    fprintf(fil, "%s", log_line);
    fclose(fil);

    Interface::loaded(); // signalize end
}

void Game::repeat()
{
    State temp_state;
    uint16_t i = 0;
    bool first = true;
    uint64_t then = 0;
    uint32_t last_d = 0;

    tries++;
    delta = 0;

    while(i < rec_sz){
        xSemaphoreTake(mtx, portMAX_DELAY);
        temp_state = state; 
        xSemaphoreGive(mtx);

        if(temp_state != State::REPEAT)
            return;

        uint64_t now = xTaskGetTickCount();
        if(b_moeda->get_state() == Button::State::PRESSED) {
            a_moeda->set_active();
            a_solta->set_active(false); // Moeda (coin) presses the string and the solta (loose) sound stops.
            l_moeda->blink(a_moeda->get_length()/44.101);
            l_solta->turn_off();
            
            if(first) {
                first = false;
                then = now;
                last_d = rec_ptr[i].d_time;
            }

            if(rec_ptr[i].instr != (uint8_t)Instrument::MOEDA){
                rpt_st = -2;
                set_state(State::IDLE);
                Interface::loaded();                
                return;
            }
            if((int64_t)(now - then) < ((int64_t)rec_ptr[i].d_time - last_d - MAX_RPT_DELAY) / portTICK_PERIOD_MS){ // Too soon
                rpt_st = -1;
                set_state(State::IDLE);
                Interface::loaded();                
                return;
            }

            delta += abs((int64_t)(now - then) - (rec_ptr[i].d_time - last_d)/portTICK_PERIOD_MS);
            last_d = rec_ptr[i++].d_time;
            then = now;
        }
        if(b_presa->get_state() == Button::State::PRESSED){
            a_presa->set_active();
            a_solta->set_active(false);
            l_presa->blink(a_presa->get_length()/44.101);
            l_solta->turn_off();

            if(first) {
                first = false;
                then = now;
                last_d = rec_ptr[i].d_time;
            }

            if(rec_ptr[i].instr != (uint8_t)Instrument::PRESA){
                rpt_st = -2;
                set_state(State::IDLE);
                Interface::loaded();                
                return;
            }
            if((int64_t)(now - then) < ((int64_t)rec_ptr[i].d_time - last_d - MAX_RPT_DELAY) / portTICK_PERIOD_MS){ // Too soon
                rpt_st = -1;
                set_state(State::IDLE);
                Interface::loaded();                
                return;
            }

            delta += abs((int64_t)(now - then) - (rec_ptr[i].d_time - last_d)/portTICK_PERIOD_MS);
            last_d = rec_ptr[i++].d_time;
            then = now;
        }
        if(b_caxixi->get_state() == Button::State::PRESSED){
            a_caxixi->set_active();
            l_caxixi->blink(a_caxixi->get_length()/44.101);
            
            if(first) {
                first = false;
                then = now;
                last_d = rec_ptr[i].d_time;
            }

            if(rec_ptr[i].instr != (uint8_t)Instrument::CAXIXI){
                rpt_st = -2;
                set_state(State::IDLE);
                Interface::loaded();                
                return;
            }
            if((int64_t)(now - then) < ((int64_t)rec_ptr[i].d_time - last_d - MAX_RPT_DELAY) / portTICK_PERIOD_MS){ // Too soon
                rpt_st = -1;
                set_state(State::IDLE);
                Interface::loaded();                
                return;
            }

            delta += abs((int64_t)(now - then) - (rec_ptr[i].d_time - last_d)/portTICK_PERIOD_MS);
            last_d = rec_ptr[i++].d_time;
            then = now;
        }
        if(b_solta->get_state() == Button::State::PRESSED){
            a_solta->set_active();
            l_solta->blink(a_solta->get_length()/44.101);
            
            if(first) {
                first = false;
                then = now;
                last_d = rec_ptr[i].d_time;
            }

            if(rec_ptr[i].instr != (uint8_t)Instrument::SOLTA){
                rpt_st = -2;
                set_state(State::IDLE);
                Interface::loaded();                
                return;
            }
            if((int64_t)(now - then) < ((int64_t)rec_ptr[i].d_time - last_d - MAX_RPT_DELAY) / portTICK_PERIOD_MS){ // Too soon
                rpt_st = -1;
                set_state(State::IDLE);
                Interface::loaded();                
                return;
            }

            delta += abs((int64_t)(now - then) - (rec_ptr[i].d_time - last_d)/portTICK_PERIOD_MS);
            last_d = rec_ptr[i++].d_time;
            then = now;
        }

        if(!first && (now - then > (rec_ptr[i].d_time - last_d + MAX_RPT_DELAY) / portTICK_PERIOD_MS )){
            rpt_st = -3;
            set_state(State::IDLE);
            Interface::loaded();
            return;
        }

        taskYIELD(); // Or a little delay    
    }

    rpt_st = 0;
    set_state(State::IDLE);
    Interface::loaded();
}

int Game::get_repeat_st()
{
    return rpt_st;
}

uint8_t Game::get_listen()
{
    return listens;
}

uint8_t Game::get_tries()
{
    return tries;
}

uint8_t Game::get_precision()
{
    return delta * -100.0/(rec_sz*MAX_RPT_DELAY/portTICK_PERIOD_MS) + 100;
}

void Game::set_player(char *name)
{
    strcpy(player, name);

    set_state(State::ADD_PLAYER);
}

void Game::add_player()
{
    char buf[70];
    sprintf(buf, "/spiffs/logs/%s.csv", player);
    if(get_sz(buf) <= 0){ // New player!
        FILE *fil = fopen(buf, "w");
        fprintf(fil, "#ritmo,audicoes,repeticoes,precisao (0 = desistencia)\n");
        fclose(fil);
    }

    state = State::IDLE;
    Interface::loaded();
}