#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
typedef struct Player {
int vida;
char nome[55];
float Radiacao;//0-1000;
int fome;//0-100;
int sede;//0-10;
float temperatura;//-50 a 50;

}player;
