#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

typedef enum {
    ESTRELA_GIGANTE_VERMELHA,
    ESTRELA_ANA_BRANCA,
    ESTRELA_VERMELHA,
    ESTRELA_AMARELA,
    ESTRELA_NEUTRONS,
    ESTRELA_GIGANTE_AZUL,
    ESTRELA_SUPERGIGANTE_AZUL,
    ESTRELA_SUPERGIGANTE_VERMELHA,
    ESTRELA_HIPERGIGANTE_AZUL,
    ESTRELA_HIPERGIGANTE_VERMELHA,
    ESTRELA_ANA_MARROM,
    ESTRELA_MAGNETAR;
} TipoEstrela;

typedef struct {
    char nome[100];
    float temperatura;
    TipoEstrela tipo;
    float massa;
    float luminosidade;  // comparada com o Sol
    float distancia;     // anos-luz
    float raio;          // comparado com o Sol
    Color cor;
    float idade;         // anos
    float raios;         // isso aqui é "raios" do quê? (UV? cósmicos?)
} Estrela;