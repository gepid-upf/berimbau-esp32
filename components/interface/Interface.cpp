#include <Interface.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_err.h>

#include <cstring>

extern "C" {
    #include <tft.h>
}

Button *Interface::b_blue = nullptr;
Button *Interface::b_red = nullptr;
Button *Interface::b_green = nullptr;
Button *Interface::b_pink = nullptr;

Button *Interface::b_left = nullptr;
Button *Interface::b_right = nullptr;
Button *Interface::b_up = nullptr;
Button *Interface::b_down = nullptr;

SemaphoreHandle_t Interface::load_cnt = nullptr;

uint8_t Interface::key_x = 0;
uint8_t Interface::key_y = 0;

const uint8_t Interface::box_w = 15;
const uint8_t Interface::box_h = 17;

uint8_t Interface::char_x = 0;
uint8_t Interface::limit_x = 0;
const uint8_t Interface::char_y = 28;

uint8_t Interface::add_w = 0;

const char Interface::key_matrix[3][10] = { {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
                                            {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',  (char)-1},
                                            {'Z', 'X', 'C', 'V', 'B', 'N', 'M', '_',  (char)-1,  (char)-1} };

uint8_t Interface::key_sz[52];
uint8_t Interface::key_cnt = 0;
char Interface::name[52];

char Interface::rec[39];

Interface::Option Interface::opt = Option::PLAY;

Interface::State Interface::state = State::IDLE;

std::vector<std::string> Interface::challenges;
uint8_t Interface::ch_sel = 0;
uint8_t Interface::ch_top = 0;
uint8_t Interface::ch_bot = 0;

void Interface::task(void *nullpar)
{    
    loading_screen("Berimbau", "Carregando...", 5);

    name_screen();

    while(true){
        switch(state){
        case State::REC_INPUT:
            if(b_pink->get_state() == Button::State::PRESSED){
                main_menu();
                break;
            }
        case State::NAME_INPUT:
            if(b_left->get_state() == Button::State::PRESSED)
                key_move(Direction::D_LEFT);
            else if(b_right->get_state() == Button::State::PRESSED)
                key_move(Direction::D_RIGHT);
            else if(b_up->get_state() == Button::State::PRESSED)
                key_move(Direction::D_UP);
            else if(b_down->get_state() == Button::State::PRESSED)
                key_move(Direction::D_DOWN);
            else if(b_blue->get_state() == Button::State::PRESSED)
                sel_char();
            else if(b_red->get_state() == Button::State::PRESSED)
                del_char();

            break;
        case State::MAIN_MENU:
            if(b_up->get_state() == Button::State::PRESSED)
                menu_move(Direction::D_UP);
            else if(b_down->get_state() == Button::State::PRESSED)
                menu_move(Direction::D_DOWN);
            else if(b_blue->get_state() == Button::State::PRESSED)
                menu_sel();

            break;
        case State::PLAY:
            if(b_pink->get_state() == Button::State::PRESSED)
                main_menu();
            
            break;
        case State::RECORD:
            if(b_red->get_state() == Button::State::PRESSED)
                rec_cancel();
            else if(b_blue->get_state() == Button::State::PRESSED)
                rec_end();

            break;
        case State::OVERWRITE:
            if(b_red->get_state() == Button::State::PRESSED)
                record_name();
            else if(b_green->get_state() == Button::State::PRESSED)
                record();
                
            break;
        case State::REC_CANCEL:
            if(b_blue->get_state() == Button::State::PRESSED)
                main_menu();

            break;
        case State::CHALLENGE:
            if(b_pink->get_state() == Button::State::PRESSED){
                challenges.clear();
                main_menu();
            } else if(b_down->get_state() == Button::State::PRESSED)
                ch_move(Direction::D_DOWN);
            else if(b_up->get_state() == Button::State::PRESSED)
                ch_move(Direction::D_UP);
            else if(b_red->get_state() == Button::State::PRESSED)
                erase_rec();
            else if(b_blue->get_state() == Button::State::PRESSED)
                listen();

            break;
        case State::ERASE:
            if(b_green->get_state() == Button::State::PRESSED)
                erase_confirm();
            else if(b_red->get_state() == Button::State::PRESSED)
                challenge_menu();

            break;
        case State::ERASE_CONT:
            if(b_blue->get_state() == Button::State::PRESSED)
                challenge_menu();

            break;
        case State::LISTEN:
            if(b_pink->get_state() == Button::State::PRESSED){
                load_cnt = xSemaphoreCreateCounting(1, 0);
                Game::set_state(Game::State::UNLOAD);
                simple_load("Aguarde", "Salvando log...");
                
                challenge_menu();
                break;
            }
            // Check if playback is over. Asks if wants to play again.
            check_listening();
            break;
        case State::LISTEN_AGAIN:
            if(b_pink->get_state() == Button::State::PRESSED){
                load_cnt = xSemaphoreCreateCounting(1, 0);
                Game::set_state(Game::State::UNLOAD);
                simple_load("Aguarde", "Salvando log...");

                challenge_menu();
            } else if(b_green->get_state() == Button::State::PRESSED)
                listen_scr();
            else if(b_blue->get_state() == Button::State::PRESSED)
                repeat_scr();
            
            break;
        case State::REPEAT:
            if(b_pink->get_state() == Button::State::PRESSED){
                Game::set_state(Game::State::UNLOAD);
                simple_load("Aguarde", "Salvando log...");
                
                challenge_menu();
                break;
            } else if(b_green->get_state() == Button::State::PRESSED){
                // Stop repeating.
                Game::set_state(Game::State::IDLE);
                vSemaphoreDelete(load_cnt);
                listen_scr();
                break;
            }
            
            // Check if missed, mistimed or ended.
            check_repeat();
            break;
        case State::FAILED:
            if(b_pink->get_state() == Button::State::PRESSED){
                load_cnt = xSemaphoreCreateCounting(1, 0);
                Game::set_state(Game::State::UNLOAD);
                simple_load("Aguarde", "Salvando log...");

                challenge_menu();
            } else if(b_green->get_state() == Button::State::PRESSED)
                listen_scr();
            else if(b_blue->get_state() == Button::State::PRESSED)
                repeat_scr();

            break;
        case State::SUCCESS:
            if(b_blue->get_state() == Button::State::PRESSED){
                load_cnt = xSemaphoreCreateCounting(1, 0);
                Game::set_state(Game::State::UNLOAD);
                simple_load("Aguarde", "Salvando log...");

                main_menu();
            }
            break;
        default:
            break;
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

// https://stackoverflow.com/questions/31215971/non-trivial-designated-initializers-not-supported
// http://bbs.esp32.com/viewtopic.php?t=3788
void Interface::init_tft()
{
    esp_err_t ret = 0;
    // === SET GLOBAL VARIABLES ==========================
    // ==== Set display type                         =====
    tft_disp_type = DISP_TYPE_ST7735R;

    // === Set display resolution if NOT using default ===
    _width = 128; // smaller dimension
    _height = 160; // larger dimension

    // ==== Set maximum spi clock for display read    ====
	//      operations, function 'find_rd_speed()'    ====
	//      can be used after display initialization  ====
	max_rdclock = 8000000;

    // === Pins MUST be initialized before SPI interface initialization ===
    TFT_PinsInit();

    // ====  CONFIGURE SPI DEVICES(s)  ====================================================================================
    spi_lobo_device_handle_t spi = {};

    spi_lobo_bus_config_t buscfg={
        .mosi_io_num=PIN_NUM_MOSI,				// set SPI MOSI pin
        .miso_io_num=-1,				// set SPI MISO pin
        .sclk_io_num=PIN_NUM_CLK,				// set SPI CLK pin
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
		.max_transfer_sz = 6*1024,
    };

    spi_lobo_device_interface_config_t devcfg = {};
    devcfg.clock_speed_hz=8000000;                // Initial clock out at 8 MHz
    devcfg.mode=0;                                // SPI mode 0
    devcfg.spics_io_num=PIN_NUM_CS;               // Dev 0 - 2 can use hardware CS.
    devcfg.spics_ext_io_num=-1;                   // No software-mode CS needed
    devcfg.flags=LB_SPI_DEVICE_HALFDUPLEX;        // ALWAYS SET  to HALF DUPLEX MODE!! for display spi

    vTaskDelay(500 / portTICK_RATE_MS);
    
    // ==== Initialize the SPI bus and attach the LCD to the SPI bus ====
	ret = spi_lobo_bus_add_device(TFT_HSPI_HOST, &buscfg, &devcfg, &spi);
    assert(ret==ESP_OK);

	disp_spi = spi;

    // ==== Test select/deselect ====
	ret = spi_lobo_device_select(spi, 1);
    assert(ret==ESP_OK);
	ret = spi_lobo_device_deselect(spi);
    assert(ret==ESP_OK);

    // ==== Initialize the Display ====
	TFT_display_init();

    // ---- Detect maximum read speed ----
    // No MISO in use here
	//max_rdclock = find_rd_speed();

    // ==== Set SPI clock used for display operations ====
	spi_lobo_set_speed(spi, 10000000); // Raise when possible. Will rely on cable length and quality.

	font_rotate = 0;
	text_wrap = 0;
	font_transparent = 0;
	font_forceFixed = 0;
	gray_scale = 0;
    TFT_setGammaCurve(DEFAULT_GAMMA_CURVE);
	TFT_setRotation(LANDSCAPE);
	TFT_setFont(DEFAULT_FONT, NULL);
	TFT_resetclipwin();
    TFT_fillScreen(TFT_BLACK);
}

void Interface::loading_screen(char *hdr, char *msg, uint16_t total)
{
    TFT_fillScreen(TFT_BLACK);
    top_header(hdr);

    _fg = TFT_CYAN;
    TFT_setFont(DEFAULT_FONT, NULL);
    TFT_resetclipwin();
	TFT_print(msg, CENTER, CENTER);


    TFT_drawRect(28, 86, 102, 22, TFT_CYAN);

    uint8_t cnt;
    while((cnt = uxSemaphoreGetCount(load_cnt)) < total){
        TFT_fillRect(29, 87, cnt*100/total, 20, TFT_WHITE);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    vSemaphoreDelete(load_cnt);
}

void Interface::top_header(char *text)
{
	TFT_resetclipwin();

	_fg = TFT_YELLOW;
	_bg = (color_t){ 64, 64, 64 };

    TFT_setFont(DEF_SMALL_FONT, NULL);

	TFT_fillRect(0, 0, _width-1, TFT_getfontheight()+8, _bg);
	TFT_drawRect(0, 0, _width-1, TFT_getfontheight()+8, TFT_CYAN);
    TFT_print(text, CENTER, 4);

	_bg = TFT_BLACK;
	TFT_setclipwin(0,TFT_getfontheight()+9, _width-1, _height-TFT_getfontheight()-10);
}

void Interface::bot_box()
{
    TFT_resetclipwin();

    _fg = TFT_YELLOW;
	_bg = (color_t){ 64, 64, 64 };
    TFT_setFont(DEF_SMALL_FONT, NULL);
    TFT_fillRect(0, _height-TFT_getfontheight()-9, _width-1, TFT_getfontheight()+8, _bg);
	TFT_drawRect(0, _height-TFT_getfontheight()-9, _width-1, TFT_getfontheight()+8, TFT_CYAN);

	//TFT_setclipwin(0,TFT_getfontheight()+9, _width-1, _height-TFT_getfontheight()-10);
}

void Interface::name_screen()
{
    state = State::NAME_INPUT;

    TFT_fillScreen(TFT_BLACK);
    top_header("Insira seu nome");

    show_keyboard(151);

    // Bottom header
    bot_box();

    _fg = TFT_RED;
    TFT_print("APAGA", 19, _height-TFT_getfontheight()-5);
    _fg = TFT_YELLOW;
    TFT_print(" | ", 60, _height-TFT_getfontheight()-5);
    _fg = TFT_BLUE;
    TFT_print("SELECIONA", 76, _height-TFT_getfontheight()-5);
	
    //TFT_setclipwin(0,TFT_getfontheight()+9, _width-1, _height-TFT_getfontheight()-10);
}

void Interface::show_keyboard(uint8_t len)
{
    // Espaco para Nome sublinhado
    TFT_setFont(DEFAULT_FONT, NULL);
    TFT_resetclipwin();

    char_x = (160-len)/2;
    limit_x = (160+len)/2;
    TFT_drawLine(char_x, 42, limit_x, 42, TFT_YELLOW);

    _fg = TFT_WHITE;
    _bg = TFT_BLACK;
    TFT_resetclipwin();

    // Monospace workaround

    // First row
    TFT_print("Q", 8, 52);
    TFT_print("W", 22, 52);
    TFT_print("E", 38, 52);
    TFT_print("R", 53, 52);
    TFT_print("T", 69, 52);
    TFT_print("Y", 84, 52);
    TFT_print("U", 98, 52);
    TFT_print("I", 116, 52);
    TFT_print("O", 126, 52);
    TFT_print("P", 143, 52);

    // Second row
    TFT_print("A", 8, 71);
    TFT_print("S", 23, 71);
    TFT_print("D", 38, 71);
    TFT_print("F", 54, 71);
    TFT_print("G", 68, 71);
    TFT_print("H", 83, 71);
    TFT_print("J", 101, 71);
    TFT_print("K", 114, 71);
    TFT_print("L", 128, 71);
    //TFT_print("Ç", 143, 52);
    
    TFT_print("Z", 8, 90);
    TFT_print("X", 24, 90);
    TFT_print("C", 38, 90);
    TFT_print("V", 53, 90);
    TFT_print("B", 69, 90);
    TFT_print("N", 83, 90);
    TFT_print("M", 98, 90);
    TFT_print("_", 115, 90);

    TFT_print("F", 128, 90);
    TFT_print("I", 137, 90);
    TFT_print("M", 143, 90);
    
    // Start at Q
    key_x = 5;
    key_y = 50;
    TFT_drawRect(key_x, key_y, box_w, box_h, TFT_LIGHTGREY);

    key_cnt = 0;
    add_w = 0;
}

void Interface::key_move(Direction dir)
{
    // Erase previous
    TFT_drawRect(key_x, key_y, box_w+add_w, box_h, TFT_BLACK);

    // Create new
    switch(dir){
    case Direction::D_RIGHT:
        key_x += 15;
        if(key_x >= 155 || (key_y > 50 && key_x >= 140)) key_x = 5;
        break;
    case Direction::D_DOWN:
        key_y += 19;
        if(key_y >= 107) key_y = 50;
        break;
    case Direction::D_UP:
        key_y -= 19;
        if(key_y < 50) key_y = 88;
        break;
    case Direction::D_LEFT:
        key_x -= 15;
        if(key_x > 200) key_x = 140;
        break;
    default:
        break;
    }
    if(key_x > 125 && key_y > 50) key_x = 125;

    if(key_x == 125 && key_y == 88) add_w = 15;
    else add_w = 0;

    TFT_drawRect(key_x, key_y, box_w+add_w, box_h, TFT_LIGHTGREY);
}

void Interface::set_button(Button *btn, Direction function)
{
    switch(function){
    case Direction::D_DOWN:
        b_down = btn;
        break;
    case Direction::D_UP:
        b_up = btn;
        break;
    case Direction::D_LEFT:
        b_left = btn;
        break;
    case Direction::D_RIGHT:
        b_right = btn;
        break;
    
    case Direction::D_O:
        b_red = btn;
        break;
    case Direction::D_X:
        b_blue = btn;
        break;
    case Direction::D_T:
        b_green = btn;
        break;
    case Direction::D_S:
        b_pink = btn;
        break;
    }
}

void Interface::sel_char()
{
    _bg = TFT_BLACK;
    _fg = TFT_ORANGE;
    TFT_setFont(DEFAULT_FONT, NULL);
    TFT_resetclipwin();

    char out = key_matrix[(key_y-50)/19][(key_x-5)/15];
    
    if(out != (char)-1){
        char temp[2] = {out, '\0'};
        uint8_t sz = TFT_getStringWidth(temp);

        if(sz + char_x < limit_x){
            TFT_print(temp, char_x, char_y);
            char_x += sz;

            switch(state){
            case State::NAME_INPUT:
                name[key_cnt] = out;
                break;
            case State::REC_INPUT:
                rec[key_cnt] = out;
                break;
            default:
                break;
            }
            
            key_sz[key_cnt] = sz;
            key_cnt++;
        }
    } else if(key_cnt) {
        switch(state){
        case State::NAME_INPUT:
            name[key_cnt] = '\0';
            load_cnt = xSemaphoreCreateCounting(1, 0);
            Game::set_player(name);
            simple_load("Berimbau", "Carregando...");
            main_menu();
            break;
        case State::REC_INPUT:
            rec[key_cnt] = '\0';
            if(Game::overwrite(rec))
                overwrite();
            else
                record();
            break;
        default:
            break;
        }
    }
    
}

void Interface::del_char()
{
    _bg = TFT_BLACK;
    _fg = TFT_BLACK;
    TFT_setFont(DEFAULT_FONT, NULL);
    TFT_resetclipwin();

    if(key_cnt){
        uint8_t sz = key_sz[--key_cnt];
        char_x -= sz;
        TFT_fillRect(char_x, char_y, sz, 13, TFT_BLACK);
    }
}

void Interface::main_menu()
{
    Game::set_state(Game::State::IDLE);
    state = State::MAIN_MENU;

    TFT_fillScreen(TFT_BLACK);
    top_header("Menu principal");
    TFT_resetclipwin();

    TFT_setFont(DEFAULT_FONT, NULL);

    // 3 Options:
    _bg = TFT_BLACK;
    _fg = TFT_YELLOW;
    TFT_print("1. TOCAR", CENTER, 36);
    TFT_print("2. GRAVAR", CENTER, 57); // Centered
    TFT_print("3. DESAFIO", CENTER, 78);

    //draw arrow
    draw_arrow(36, 41, TFT_CYAN);

    // Bottom header
    bot_box();

    _fg = TFT_BLUE;
    TFT_print("SELECIONA", CENTER, _height-TFT_getfontheight()-5);

    opt = Option::PLAY;
}

void Interface::draw_arrow(uint8_t x, uint8_t y, color_t color)
{
    TFT_drawFastHLine(x, y, 8, color);
    TFT_drawLine(x+4, y+4, x+8, y, color);
    TFT_drawLine(x+4, y-4, x+8, y, color);
}

void Interface::menu_move(Direction dir)
{
    // Erase old arrow
    switch(opt){
    case Option::PLAY:
        TFT_fillRect(36, 36, 9, 13, TFT_BLACK);
        break;
    case Option::RECORD:
        TFT_fillRect(32, 57, 9, 13, TFT_BLACK);
        break;
    case Option::CHALLENGE:
        TFT_fillRect(30, 78, 9, 13, TFT_BLACK);
        break;
    }

    // Change opt
    switch(dir){
    case Direction::D_UP:
        switch(opt){
        case Option::PLAY:
            opt = Option::CHALLENGE;
            break;
        case Option::CHALLENGE:
            opt = Option::RECORD;
            break;
        case Option::RECORD:
            opt = Option::PLAY;
            break;
        }
        break;
    case Direction::D_DOWN:
        switch(opt){
        case Option::PLAY:
            opt = Option::RECORD;
            break;
        case Option::RECORD:
            opt = Option::CHALLENGE;
            break;
        case Option::CHALLENGE:
            opt = Option::PLAY;
            break;
        }
        break;
    default:
        break;
    }

    // Create new arrow
    switch(opt){
    case Option::PLAY:
        draw_arrow(36, 41, TFT_CYAN);
        break;
    case Option::RECORD:
        draw_arrow(32, 62, TFT_CYAN);
        break;
    case Option::CHALLENGE:
        draw_arrow(30, 83, TFT_CYAN);
        break;
    default:
        break;
    }
}

void Interface::menu_sel()
{
    switch(opt){
    case Option::PLAY:
        play_menu();
        break;
    case Option::RECORD:
        record_name();
        break;
    case Option::CHALLENGE:
        challenge_menu();
        break;
    default:
        break;
    }
}

void Interface::play_menu()
{
    state = State::PLAY;

    TFT_fillScreen(TFT_BLACK);
    top_header("Tocar livremente");
    TFT_resetclipwin();

    TFT_setFont(DEFAULT_FONT, NULL);

    _bg = TFT_BLACK;
    _fg = TFT_YELLOW;
    
    TFT_print("Toque o instrumento", CENTER, 22);
    TFT_print("para descobrir seu", CENTER, 39);
    TFT_print("som. Dica: aproxime e", CENTER, 56);
    TFT_print("afaste o artefato do", CENTER, 73);
    TFT_print("corpo para abafar.", CENTER, 90);

    // Bottom header
    bot_box();

    _fg = TFT_PINK;
    TFT_print("VOLTA", CENTER, _height-TFT_getfontheight()-5);

    Game::set_state(Game::State::PLAY);
}

void Interface::record_name()
{
    state = State::REC_INPUT;

    TFT_fillScreen(TFT_BLACK);
    top_header("Insira o nome do ritmo");

    show_keyboard(113);

    // Bottom header
    bot_box();

    TFT_resetclipwin();

    _fg = TFT_PINK;
    TFT_print("VOLTA", 15, _height-TFT_getfontheight()-5);
    _fg = TFT_YELLOW;
    TFT_print("|", 57, _height-TFT_getfontheight()-5);
    _fg = TFT_RED;
    TFT_print("APAGA", 65, _height-TFT_getfontheight()-5);
    _fg = TFT_YELLOW;
    TFT_print("|", 110, _height-TFT_getfontheight()-5);
    _fg = TFT_BLUE;
    TFT_print("SEL.", 118, _height-TFT_getfontheight()-5);    

}

void Interface::record()
{
    state = State::RECORD;

    TFT_fillScreen(TFT_BLACK);
    top_header("Gravando");

    // Instructions
    TFT_resetclipwin();
    TFT_setFont(DEFAULT_FONT, NULL);

    _bg = TFT_BLACK;
    _fg = TFT_YELLOW;
    TFT_print("Toque qualquer som", CENTER, 39);
    TFT_print("para iniciar. Ao fim,", CENTER, 56);
    TFT_print("confirme ou cancele.", CENTER, 73);

    // Bottom header
    bot_box();

    TFT_resetclipwin();

    _fg = TFT_RED;
    TFT_print("CANCELA", 20, _height-TFT_getfontheight()-5);
    _fg = TFT_YELLOW;
    TFT_print("|", 79, _height-TFT_getfontheight()-5);
    _fg = TFT_BLUE;
    TFT_print("FINALIZA", 87, _height-TFT_getfontheight()-5);  

    // Change the game state
    // SPIFFS loaded on 'boot'
    Game::set_state(Game::State::RECORD);
}

void Interface::rec_cancel()
{
    TFT_fillScreen(TFT_BLACK);
    top_header("Cancelado");

    // Instructions
    TFT_resetclipwin();
    TFT_setFont(DEFAULT_FONT, NULL);

    _bg = TFT_BLACK;
    _fg = TFT_YELLOW;
    TFT_print("Gravacao descartada.", CENTER, 56);

    bot_box();

    Game::rec_cancel();

    _fg = TFT_BLUE;
    TFT_print("CONTINUA", CENTER, _height-TFT_getfontheight()-5);

    state = State::REC_CANCEL;
}

void Interface::rec_end()
{
    TFT_fillScreen(TFT_BLACK);

    int32_t ret;
    if((ret = Game::rec_end()) > 0){
        top_header("Sucesso");

        TFT_resetclipwin();
        TFT_setFont(DEFAULT_FONT, NULL);

        // Instructions
        _bg = TFT_BLACK;
        _fg = TFT_YELLOW;
        TFT_print("Sua gravacao agora", CENTER, 39);
        TFT_print("esta disponivel no", CENTER, 56);
        TFT_print("menu de desafio.", CENTER, 73);

        Game::rec_save(rec);
        
    } else {
        top_header("Erro");

        TFT_resetclipwin();
        TFT_setFont(DEFAULT_FONT, NULL);

        // Instructions
        _bg = TFT_BLACK;
        _fg = TFT_YELLOW;

        if(ret < 0){
            TFT_print("Espaco insuficiente.", CENTER, 48);
            TFT_print("Apague um desafio.", CENTER, 65);
        } else {
            TFT_print("Nada para gravar.", CENTER, 56);
        }
        
        Game::rec_cancel();
    }

    bot_box();

    _fg = TFT_BLUE;
    TFT_print("CONTINUA", CENTER, _height-TFT_getfontheight()-5);

    state = State::REC_CANCEL;
}

void Interface::loaded()
{
    xSemaphoreGive(load_cnt);
}

void Interface::pre_init()
{
    init_tft();

    load_cnt = xSemaphoreCreateCounting(5, 0);
}

void Interface::challenge_menu()
{
    load_cnt = xSemaphoreCreateCounting(1, 0);

    Game::set_state(Game::State::LOAD_REC_LIST);

    simple_load("Desafio", "Carregando lista...");

    challenges = Game::get_rec_list();

    TFT_fillScreen(TFT_BLACK);
    top_header("Escolha o desafio");

    // Instructions
    TFT_resetclipwin();
    TFT_setFont(DEFAULT_FONT, NULL);

    _bg = TFT_BLACK;
    _fg = TFT_YELLOW;

    ch_sel = 0;
    ch_top = 0;

    // Populate first challenges.
    print_list();

    challenges.size() > 4 ? ch_bot = 3 : ch_bot = challenges.size() - 1;

    draw_arrow(4, 38, TFT_CYAN); 

    if(challenges.size() > 4)
        draw_arrow_down(26, 97, TFT_LIGHTGREY);

    bot_box();

    TFT_resetclipwin();

    _fg = TFT_PINK;
    TFT_print("VOLTA", 15, _height-TFT_getfontheight()-5);
    _fg = TFT_YELLOW;
    TFT_print("|", 57, _height-TFT_getfontheight()-5);
    _fg = TFT_RED;
    TFT_print("APAGA", 65, _height-TFT_getfontheight()-5);
    _fg = TFT_YELLOW;
    TFT_print("|", 110, _height-TFT_getfontheight()-5);
    _fg = TFT_BLUE;
    TFT_print("SEL.", 118, _height-TFT_getfontheight()-5);

    state = State::CHALLENGE;    
}

void Interface::overwrite()
{
    TFT_fillScreen(TFT_BLACK);
    top_header("Sobrescrever");

    // Instructions
    TFT_resetclipwin();
    TFT_setFont(DEFAULT_FONT, NULL);

    _bg = TFT_BLACK;
    _fg = TFT_YELLOW;
    TFT_print("Arquivo existente.", CENTER, 48);
    TFT_print("Deseja sobrescrever?", CENTER, 65);

    // Bottom header
    bot_box();

    TFT_resetclipwin();

    _fg = TFT_RED;
    TFT_print("NAO", 50, _height-TFT_getfontheight()-5);
    _fg = TFT_YELLOW;
    TFT_print("|", 80, _height-TFT_getfontheight()-5);
    _fg = TFT_GREEN;
    TFT_print("SIM", 88, _height-TFT_getfontheight()-5);

    state = State::OVERWRITE;
}

void Interface::draw_arrow_up(uint8_t x, uint8_t y, color_t color)
{
    TFT_drawFastVLine(x, y, 9, color);
    TFT_drawLine(x-4, y+4, x, y, color);
    TFT_drawLine(x+4, y+4, x, y, color);
}

void Interface::draw_arrow_down(uint8_t x, uint8_t y, color_t color)
{
    TFT_drawFastVLine(x, y, 8, color);
    TFT_drawLine(x-4, y+4, x, y+8, color);
    TFT_drawLine(x+4, y+4, x, y+8, color);
}

void Interface::ch_move(Direction dir)
{
    TFT_resetclipwin();
    TFT_setFont(DEFAULT_FONT, NULL);
    _bg = TFT_BLACK;
    _fg = TFT_YELLOW;

    switch(dir){
    case Direction::D_UP:
        if(ch_sel){
            ch_sel--;
            // Roll up
            if(ch_top > ch_sel){
                // Erase all list.
                TFT_fillRect(0, 18, 159, 91, TFT_BLACK);
                
                // New ch_top and ch_bot
                ch_top = ch_sel;
                ch_bot--; // Guaranteed if going up

                // Print list starting with new ch_sel and end with ch_sel +4
                // If going up, size > 4 is guaranteed
                print_list();

                // Print arrow down - always needed if going up
                draw_arrow_down(26, 97, TFT_LIGHTGREY);

                // Check if needed to print arrow up
                if(ch_top)
                    draw_arrow_up(26, 22, TFT_LIGHTGREY);

            } else {
                // Erase previous arrow
                TFT_fillRect(4, (ch_sel - ch_top + 1)*17 + 32, 9, 11, TFT_BLACK);
            }

            // Draw arrow at ch_sel
            draw_arrow(4, (ch_sel - ch_top)*17 + 38, TFT_CYAN);
        }
        break;
    case Direction::D_DOWN:
        if(ch_sel+1 < challenges.size()){
            ch_sel++;

            // Roll down
            if(ch_bot < ch_sel){
                // Erase all list.
                TFT_fillRect(0, 18, 159, 91, TFT_BLACK);
                
                // New ch_top and ch_bot
                ch_top++; // Guaranteed if going down
                ch_bot = ch_sel; // Guaranteed if going up

                // Print list starting with new ch_sel and end with ch_sel +4
                // If going down is guaranteed to not overflow
                print_list();

                // Print arrow up - always needed if going down
                draw_arrow_up(26, 22, TFT_LIGHTGREY);

                // Check if needed to print arrow down
                if(ch_bot+1 < challenges.size())
                    draw_arrow_down(26, 97, TFT_LIGHTGREY);
                

            } else {
                // Erase previous arrow
                TFT_fillRect(4, (ch_sel - ch_top - 1)*17 + 32, 9, 11, TFT_BLACK);
            }

            // Draw arrow at ch_sel
            draw_arrow(4, (ch_sel - ch_top)*17 + 38, TFT_CYAN);
        }
        break;
    default:
        break;
    }
}

void Interface::simple_load(char *hdr, char *msg)
{
    TFT_fillScreen(TFT_BLACK);
    top_header(hdr);

    _fg = TFT_CYAN;
    TFT_setFont(DEFAULT_FONT, NULL);
    TFT_resetclipwin();
	TFT_print(msg, CENTER, CENTER);

    while(!uxSemaphoreGetCount(load_cnt)){
        // Display animation here
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    vSemaphoreDelete(load_cnt);
}

void Interface::print_list()
{
    char tmp[43]; // "##. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\0" 38 max. rec length
    char cstr[43];
    for(int i = 0; i < 4 && i < challenges.size(); i++){
        strcpy(cstr, challenges[i + ch_top].c_str());
        sprintf(tmp, "%02d. %s", ch_top+i+1, strtok(cstr, "."));
        TFT_print(tmp, 18, i*17 + 32);
    }
}

void Interface::erase_rec()
{
    TFT_fillScreen(TFT_BLACK);
    top_header("Apagar");

    // Instructions
    TFT_resetclipwin();
    TFT_setFont(DEFAULT_FONT, NULL);

    _bg = TFT_BLACK;
    _fg = TFT_YELLOW;
    TFT_print("Deseja apagar?", CENTER, 48);
    char buf[43];
    strcpy(buf, challenges[ch_sel].c_str());
    buf[strlen(buf)-4] = 0;
    TFT_print(buf, CENTER, 65);

    // Bottom header
    bot_box();

    TFT_resetclipwin();

    _fg = TFT_RED;
    TFT_print("NAO", 50, _height-TFT_getfontheight()-5);
    _fg = TFT_YELLOW;
    TFT_print("|", 80, _height-TFT_getfontheight()-5);
    _fg = TFT_GREEN;
    TFT_print("SIM", 88, _height-TFT_getfontheight()-5);

    state = State::ERASE;
}

void Interface::erase_confirm()
{
    load_cnt = xSemaphoreCreateCounting(1, 0);

    Game::erase(challenges[ch_sel].c_str());

    simple_load("Aguarde", "Apagando..."); // With message

    int st = Game::get_erase_st();

    TFT_fillScreen(TFT_BLACK);

    if(st){
        top_header("Erro");

        TFT_resetclipwin();
        TFT_setFont(DEFAULT_FONT, NULL);

        // Instructions
        _bg = TFT_BLACK;
        _fg = TFT_YELLOW;

        TFT_print("Impossivel apagar.", CENTER, 56);

    } else {
        top_header("Sucesso");

        TFT_resetclipwin();
        TFT_setFont(DEFAULT_FONT, NULL);

        // Instructions
        _bg = TFT_BLACK;
        _fg = TFT_YELLOW;

        TFT_print("Ritmo apagado.", CENTER, 56);
    }

    bot_box();
    _fg = TFT_BLUE;
    TFT_print("CONTINUA", CENTER, _height-TFT_getfontheight()-5);

    state = State::ERASE_CONT;
}

void Interface::listen()
{
    TFT_fillScreen(TFT_BLACK);
    if(Game::alloc_rec(challenges[ch_sel].c_str())){
        load_cnt = xSemaphoreCreateCounting(1, 0);

        Game::load(challenges[ch_sel].c_str());

        simple_load("Aguarde", "Carregando ritmo...");

        listen_scr();

    } else {
        top_header("Erro");

        TFT_resetclipwin();
        TFT_setFont(DEFAULT_FONT, NULL);

        // Instructions
        _bg = TFT_BLACK;
        _fg = TFT_YELLOW;
        TFT_print("Memoria insuficiente.", CENTER, 56);

        bot_box();
        _fg = TFT_BLUE;
        TFT_print("CONTINUA", CENTER, _height-TFT_getfontheight()-5);

        state = State::ERASE_CONT; // Just a continue.
    }
}

void Interface::listen_scr()
{
    // Listen screen.
    TFT_fillScreen(TFT_BLACK);
    top_header("Desafio");

    TFT_resetclipwin();
    TFT_setFont(DEFAULT_FONT, NULL);

    // Instructions
    _bg = TFT_BLACK;
    _fg = TFT_YELLOW;

    TFT_print("Escute atentamente.", CENTER, 56);

    bot_box();
    _fg = TFT_PINK;
    TFT_print("VOLTA", CENTER, _height-TFT_getfontheight()-5);

    load_cnt = xSemaphoreCreateCounting(1, 0);

    Game::set_state(Game::State::PLAY_LOADED);

    state = State::LISTEN;
}

void Interface::check_listening()
{
    // Ended
    if(uxSemaphoreGetCount(load_cnt)){
        vSemaphoreDelete(load_cnt);

        // Ask if wants to play again
        TFT_fillScreen(TFT_BLACK);
        top_header("Desafio");

        TFT_resetclipwin();
        TFT_setFont(DEFAULT_FONT, NULL);

        // Instructions
        _bg = TFT_BLACK;
        _fg = TFT_YELLOW;

        TFT_print("Ouvir novamente?", CENTER, 56);

        bot_box();
        _fg = TFT_PINK;
        TFT_print("VOLTA", 7, _height-TFT_getfontheight()-5);
        _fg = TFT_YELLOW;
        TFT_print("|", 49, _height-TFT_getfontheight()-5);
        _fg = TFT_GREEN;
        TFT_print("REPETE", 57, _height-TFT_getfontheight()-5);
        _fg = TFT_YELLOW;
        TFT_print("|", 108, _height-TFT_getfontheight()-5);
        _fg = TFT_BLUE;
        TFT_print("CONT.", 116, _height-TFT_getfontheight()-5);

        state = State::LISTEN_AGAIN;
    }
}

void Interface::repeat_scr()
{
    // Listen screen.
    TFT_fillScreen(TFT_BLACK);
    top_header("Desafio");

    TFT_resetclipwin();
    TFT_setFont(DEFAULT_FONT, NULL);

    // Instructions
    _bg = TFT_BLACK;
    _fg = TFT_YELLOW;

    TFT_print("Repita o que ouviu", CENTER, 48);
    TFT_print("mantendo o ritmo.", CENTER, 65);

    bot_box();
    _fg = TFT_PINK;
    TFT_print("DESISTE", 31, _height-TFT_getfontheight()-5);
    _fg = TFT_YELLOW;
    TFT_print("|", 86, _height-TFT_getfontheight()-5);
    _fg = TFT_GREEN;
    TFT_print("OUVE", 94, _height-TFT_getfontheight()-5);

    load_cnt = xSemaphoreCreateCounting(1, 0);

    Game::set_state(Game::State::REPEAT);

    state = State::REPEAT;
}

void Interface::check_repeat()
{
    if(uxSemaphoreGetCount(load_cnt)){
        vSemaphoreDelete(load_cnt);

        int st = Game::get_repeat_st();

        TFT_fillScreen(TFT_BLACK);

        char tmpbuf[20];

        if(!st){
            top_header("Sucesso");

            TFT_resetclipwin();
            TFT_setFont(DEFAULT_FONT, NULL);

            // Instructions
            _bg = TFT_BLACK;
            _fg = TFT_YELLOW;

            TFT_print("Parabens, voce venceu.", CENTER, 31);

            sprintf(tmpbuf, "Precisao: %d%%", Game::get_precision());
            TFT_print(tmpbuf, CENTER, 48);
            sprintf(tmpbuf, "Vezes ouvidas: %d", Game::get_listen());
            TFT_print(tmpbuf, CENTER, 65);
            sprintf(tmpbuf, "Tentativas: %d", Game::get_tries());
            TFT_print(tmpbuf, CENTER, 82);

            bot_box();
            _fg = TFT_BLUE;
            TFT_print("CONTINUA", CENTER, _height-TFT_getfontheight()-5);

            state = State::SUCCESS;

        } else {

            top_header("Falhou");

            TFT_resetclipwin();
            TFT_setFont(DEFAULT_FONT, NULL);

            // Instructions
            _bg = TFT_BLACK;
            _fg = TFT_YELLOW;
            
            TFT_print("Falhou!", CENTER, 31);
            if(st == -1){
                TFT_print("Acelerou o ritmo.", CENTER, 48);
            } else if(st == -2){
                TFT_print("Errou o instrumento.", CENTER, 48);
            } else {
                TFT_print("Atrasou o ritmo.", CENTER, 48);
            }
            sprintf(tmpbuf, "Vezes ouvidas: %d", Game::get_listen());
            TFT_print(tmpbuf, CENTER, 65);
            sprintf(tmpbuf, "Tentativas: %d", Game::get_tries());
            TFT_print(tmpbuf, CENTER, 82);

            bot_box();
            _fg = TFT_PINK;
            TFT_print("DESISTE", 2, _height-TFT_getfontheight()-5);
            _fg = TFT_YELLOW;
            TFT_print("|", 57, _height-TFT_getfontheight()-5);
            _fg = TFT_GREEN;
            TFT_print("OUVE", 65, _height-TFT_getfontheight()-5);
            _fg = TFT_YELLOW;
            TFT_print("|", 103, _height-TFT_getfontheight()-5);
            _fg = TFT_BLUE;
            TFT_print("REPETE", 111, _height-TFT_getfontheight()-5);

            state = State::FAILED;
        }
    }
}