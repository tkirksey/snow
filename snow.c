#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

struct _screenData_t {

    int rows;
    int cols;

} screenData;

void init(){

    srand(time(NULL));

    initscr();
    noecho();
    halfdelay(5);
    curs_set(0);
}

void deInit(){
    curs_set(1);
    echo();
    nocbreak();
    endwin();
}

void snow();

int main(void) {

    init();

    // getting number of rows and cols to work with
    screenData.rows = getmaxy(stdscr) - 1;
    screenData.cols = getmaxx(stdscr) - 1;

    do {
        snow();
    } while(getch() != 'q');

    deInit();

    return 0;

}

void snow(){

    clear();

    // calc snow
    
    // draw snow

    // draw frame
    attron(A_DIM);
    mvprintw(screenData.rows, 0, "Press 'q' to quit");
    attroff(A_DIM);
    refresh();

}