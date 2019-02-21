#ifndef _GAME_H_
#define _GAME_H_

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <Button.h>
#include <Audio.h>
#include <Led.h>
#include <Urm37.h>
#include <vector>
#include <string>

struct beat_t {
    uint32_t d_time;
    uint16_t res0;
    uint8_t instr;
    uint8_t res1;
};

class Game {
public:
    enum class State {
        IDLE,
        PLAY,
        RECORD,
        LOAD_REC_LIST,
        ERASE,
        PLAY_LOADED,
        REPEAT,
        ADD_PLAYER,
        UNLOAD

    };
    enum class Instrument {
        CAXIXI,
        MOEDA,
        PRESA,
        SOLTA
    };

    static void task(void *nullpar);
    static void urm_task(void *nullpar);
    static void set_button(Button *btn, Instrument instr);
    static void set_audio(Audio *aud, Instrument instr);
    static void set_led(Led *led, Instrument instr);
    static void set_state(State sta);

    static bool overwrite(char *file);
    static void rec_cancel();
    static int32_t rec_end();
    static void rec_save(char *file);

    static void load_rec_list();
    static std::vector<std::string> get_rec_list();
    static int64_t get_file_sz(const char *file);

    static void erase(const char *rec);
    static int get_erase_st();

    static bool alloc_rec(const char *file);
    static void load(const char *file);
    static void unload();

    static int get_repeat_st();
    static uint8_t get_listen();
    static uint8_t get_tries();
    static uint8_t get_precision();

    static void set_player(char *name);

private:
    static const char *TAG;

    static State state;
    static SemaphoreHandle_t mtx;

    static Button *b_caxixi;
    static Button *b_moeda;
    static Button *b_solta;
    static Button *b_presa;

    static Audio *a_caxixi;
    static Audio *a_moeda;
    static Audio *a_solta;
    static Audio *a_presa;

    static Led *l_caxixi;
    static Led *l_moeda;
    static Led *l_solta;
    static Led *l_presa;

    static Urm37 urm;

    static std::vector<beat_t> rec_array;
    static std::vector<std::string> rec_list;
    static bool first_rec;

    static char rec_buf[56];
    static int rm_ret;

    static beat_t *rec_ptr;
    static uint16_t rec_sz;

    static int rpt_st;
    static uint8_t listens;
    static uint8_t tries;
    static uint64_t delta;
    static const uint16_t MAX_RPT_DELAY;

    static char player[52];
    static char rec_name[43];

    static void init_spiffs();
    static std::vector<std::string> ls(char *path);
    static int64_t get_sz(const char *file);

    static void record(Instrument instr);
    static void wait_sounds();
    static void rm();

    static void play_loaded();
    static void repeat();

    static void add_player();
};

#endif /* _GAME_H_ */