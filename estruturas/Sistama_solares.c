#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "estrela.c"
#include "Planeta.c"

typedef struct sistema_solar{
    char nome[50];
    Estrela estrela;
    Planeta planetas[10];
    
    
