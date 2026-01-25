#ifndef SNOW_H
#define SNOW_H

#include <stdbool.h>

const int DEFAULT_MAX_SNOWFLAKES = 64;

enum _snowMode_t {
    DEFAULT,
    LIGHT,
    HEAVY
};

enum _snowMode_t SNOW_MODE = DEFAULT;

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
void init(int);
void deInit();
void createSnow(int numFlakes);
void updateSnow();
void safeExitOnNull(void *ptr);
int intClamp(int val, int floor, int ceil);

#endif