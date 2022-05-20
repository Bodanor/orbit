#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ncurses.h>

#include "constant.h"
#include "orbit.h"
#include "requests.h"
#include "parser.h"

int main()
{

    //NCURSES
    int startx, starty, width, height;
    WINDOW *KEY_INPUT_W;
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    cbreak();
   //BIGNUM
    int flag;
    const char *test;
    struct Constants *consts = InitConstant();
    mpf_t distance;
    mpf_t *Velocity;

    char *buffer;
    mpf_init(distance);
    
    height = 3;
    width = 30;
    starty = (LINES - height) / 2;	/* Calculating for a center placement */
    startx = (COLS - width) / 2;	

    KEY_INPUT_W = newwin(height, width, starty, startx);
    refresh();
    box(KEY_INPUT_W, 0,0);
    attron(COLOR_PAIR(1));
    mvwprintw(stdscr, (LINES - height - 2) / 2 ,(COLS - width) / 2 + (10/2), "Enter the API-KEY : ");
    attroff(COLOR_PAIR(1));
    wrefresh(KEY_INPUT_W);

    char API_KEY[100];
    struct MemoryStruct *data;
    struct json_object *asked;
    wrefresh(stdscr);
    wmove(KEY_INPUT_W, 1, 1);
    wgetnstr(KEY_INPUT_W, API_KEY, 28);
    buffer = malloc(sizeof(mpf_size(distance)));
    //endwin();
    do
    {
        data = call_API(API_KEY);
        asked = returnObject(data->memory, "positions");
        asked = returnObjectFromList(asked, "sataltitude");

        if (data != NULL && asked != NULL)
        {
            mp_exp_t exponent;
            test = json_object_get_string(asked);
            flag = mpf_set_str(distance, test, 10);
            assert(flag == 0);
            
            mpf_mul_ui(distance, distance, 1000);
            Velocity = computeVelocity(consts, &distance);
            wmove(stdscr, 0, 0);
            gmp_sprintf(buffer, "%.Ff", distance);
            printw("SAT DISTANCE : %s m\n", buffer);
            buffer = realloc(buffer, sizeof(mpf_size(consts->GRAVITATIONAL_CONSTANT)));
            gmp_sprintf(buffer, "%.Ff", consts->GRAVITATIONAL_CONSTANT);
            printw("GRAV : %s m3 kg-1 s-2\n", buffer);
            buffer = realloc(buffer, sizeof(mpf_size(consts->EARTH_RADIUS_METER)));
            gmp_sprintf(buffer, "%.Ff", consts->EARTH_RADIUS_METER);
            printw("EARTH_RADIUS_METER : %s m\n", buffer);
            buffer = realloc(buffer, sizeof(mpf_size(consts->EARTH_MASS)));
            gmp_sprintf(buffer, "%.Ff", consts->EARTH_MASS);
            printw("EARTH_MASS : %s kg\n\n", buffer);
            buffer = realloc(buffer, sizeof(mpf_size(*Velocity)));
            gmp_sprintf(buffer, "%.Ff", *Velocity);
            printw("VELOCITY : %s m/s\n", buffer);
            //gmp_printf("SAT DISTANCE  : %.Ff m\n", distance);
            //gmp_printf("GRAV : %.Ff m3 kg-1 s-2\n", consts->GRAVITATIONAL_CONSTANT);
            //gmp_printf("EARTH_RADIUS_METER : %.Ff m\n", consts->EARTH_RADIUS_METER);
            //gmp_printf("EARTH_MASS : %.Ff kg\n\n", consts->EARTH_MASS);
            
            //gmp_printf("VELOCITY : %.Ff m/s\n", *Velocity);
            wrefresh(KEY_INPUT_W);
            refresh();

        }   

    }while (data != NULL);



}