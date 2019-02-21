#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <Button.h>
#include <Game.h>

extern "C" {
    #include <tftspi.h>
}

class Interface {
public:
    enum class Direction {
        D_LEFT,
        D_RIGHT,
        D_UP,
        D_DOWN,

        D_X,
        D_O,
        D_S,
        D_T
    };
    static void task(void *nullpar);
    static void set_button(Button *btn, Direction function);
    static void loaded();
    static void pre_init();

private:
    enum class State {
        NAME_INPUT,
        REC_INPUT,
        MAIN_MENU,
        PLAY,
        RECORD,
        OVERWRITE,
        REC_CANCEL,
        CHALLENGE,
        ERASE,
        ERASE_CONT,
        LISTEN,
        LISTEN_AGAIN,
        REPEAT,
        FAILED,
        SUCCESS,

        IDLE
    };

    enum class Option {
        PLAY,
        RECORD,
        CHALLENGE
    };

    static SemaphoreHandle_t load_cnt;

    static Button *b_blue;
    static Button *b_red;
    static Button *b_green;
    static Button *b_pink;

    static Button *b_left;
    static Button *b_right;
    static Button *b_up;
    static Button *b_down;

    static uint8_t key_x;
    static uint8_t key_y;
    static const uint8_t box_w;
    static const uint8_t box_h;
    static uint8_t char_x;
    static uint8_t limit_x;
    static const uint8_t char_y;
    static uint8_t add_w;
    static const char key_matrix[3][10];
    static uint8_t key_sz[52];
    static uint8_t key_cnt;
    static char name[52];

    static char rec[39];

    static Option opt;

    static State state;

    static std::vector<std::string> challenges;
    static uint8_t ch_sel;
    static uint8_t ch_top;
    static uint8_t ch_bot;

    static void init_tft();
    
    static void top_header(char *text);
    static void bot_box();

    static void loading_screen(char *hdr, char *msg, uint16_t total);
    static void name_screen();
    static void show_keyboard(uint8_t len);

    static void key_move(Direction dir);
    static void sel_char();
    static void del_char();

    static void main_menu();
    static void draw_arrow(uint8_t x, uint8_t y, color_t color);
    static void menu_move(Direction dir);
    static void menu_sel();

    static void play_menu();

    static void record_name();
    static void overwrite();
    static void record();
    static void rec_cancel();
    static void rec_end();

    static void challenge_menu();
    static void draw_arrow_down(uint8_t x, uint8_t y, color_t color);
    static void draw_arrow_up(uint8_t x, uint8_t y, color_t color);
    static void ch_move(Direction dir);
    static void simple_load(char *hdr, char *msg);
    static void print_list();
    static void erase_rec();
    static void erase_confirm();
    static void listen();
    static void check_listening();
    static void listen_scr();
    static void repeat_scr();
    static void check_repeat();
};

#endif /* _INTERFACE_H_ */