#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// Define regras ou leis do jogo
#define MAXIMO FLT_MAX
#define ARQUIVO_SCORES "planetas.txt"

typedef struct Player{
    int vida;
    int pontuação;
} player;

typedef struct Tiro{
    Vector3 posicao;
    float velocidade;
    float raio;
    bool ativo;
    struct Tiro* prox;
} Tiro;

typedef struct Asteroide{
    Vector3 posicao;
    float velocidade;
    float raio;
    bool ativo;
    struct Asteroide* prox;
} Asteroide;
