#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>

#define START_SNOWFLAKE_SIZE 32

struct _screenData_t {

    int rows;
    int cols;

} screenData;

struct snowflake_t {

    int x;
    int y;
    char graphic;
    bool finished;

};

const char graphics[] = {'*', '#', '+', 'o', '.'};
const int graphicsSize = 5;

struct _snowData_t {

    int maxSnowflakes;
    struct snowflake_t* arr;

} snowData;

void snow();
void init();
void deInit();
void createSnow(int numFlakes);
void updateSnow();
void safeExitOnNull(void *ptr);
int intClamp(int val, int floor, int ceil);

int main(void) {

    init();

    do {
        snow();
    } while(getch() != 'q');

    deInit();

    return 0;

}

void init(){

    srand(time(NULL));

    initscr();
    noecho();
    halfdelay(1);
    curs_set(0);

    screenData.rows = getmaxy(stdscr) - 1;
    screenData.cols = getmaxx(stdscr) - 1;

    snowData.maxSnowflakes = START_SNOWFLAKE_SIZE;
    snowData.arr = malloc(sizeof(struct snowflake_t) * snowData.maxSnowflakes);
    safeExitOnNull(snowData.arr);

    for(int i = 0; i < snowData.maxSnowflakes; i++){
        snowData.arr[i].finished = true;
    }

    createSnow(5);

}

void deInit(){

    free(snowData.arr);

    curs_set(1);
    echo();
    nocbreak();
    endwin();
}

void snow(){

    clear();

    // update snow falling
    updateSnow();

    // random chance to create a new snowflake
    if((rand() % 2) == 0){
        createSnow(1);
    }

    // draw snow
    for(int i = 0; i < snowData.maxSnowflakes; i++){

        if(snowData.arr[i].finished == false){
            mvaddch(snowData.arr[i].y, snowData.arr[i].x, snowData.arr[i].graphic);
        }

    }

    // draw frame
    attron(A_DIM);
    mvprintw(screenData.rows, 0, "Press 'q' to quit");
    attroff(A_DIM);
    refresh();

}

void createSnow(int numFlakes){

    for(int i = 0; i < numFlakes; i++){

        bool cappedOut = false;

        // find first available snow flake slot
        for(int j = 0; j < snowData.maxSnowflakes; j++){

            if(snowData.arr[j].finished == true){
                struct snowflake_t snow;
                snow.x = rand() % screenData.cols;
                snow.y = 0; 
                snow.graphic = graphics[(rand() % graphicsSize)];
                snow.finished = false;
                snowData.arr[j] = snow;
                break;
            }

            if(j == (snowData.maxSnowflakes - 1)){
                cappedOut = true;
            }

        }

        if(cappedOut){
            return;
        }

    }

}

void updateSnow(){
    
    for(int i = 0; i < snowData.maxSnowflakes; i++){

        if(snowData.arr[i].finished == false){

            struct snowflake_t snow = snowData.arr[i];

            snow.y += 1;

            // uncomment to add small sways to snow

            // switch(rand() % 3){
            //     case 0:
            //         snow.x -= 1;
            //         break;
            //     case 1:
            //         snow.x += 1;
            //         break;
            //     default:
            // }

            // snow.x = intClamp(snow.x, 0, screenData.cols);

            if(snow.y > screenData.rows){
                snow.finished = true;
            }

            snowData.arr[i] = snow;

        }

    }

}

void safeExitOnNull(void* ptr){

    if(ptr == NULL){
        deInit();
        printf("Fatal NULL pointer occurred. Exiting.\n");
        exit(1);
    }

}

int intClamp(int val, int floor, int ceil){

    if(val > ceil){
        return ceil;
    }

    if(val < floor){
        return floor;
    }

    return val;

}