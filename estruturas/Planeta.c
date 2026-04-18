#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

typedef enum  Tipo_planeta{
   char Gasoso,
   char Rochose,
   char  Gigante_de_gelo,
   char  Anoes,

} Tipo_planeta;
typedef struct Planeta{
    char nome[50];
    float temperatura;
    float radiacao;
    float gravidade;
    bool habitavel;
    float distancia;
    bool vida;
    char *Tipo_de_Gases;
    char *Tipo_de_elementos;
    float raio;
    Tipo_planeta Tipo_planeta;
}Planeta;

