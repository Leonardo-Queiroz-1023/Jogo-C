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

int main(void){

    const int larguraTela = 800;
    const int alturaTela = 600;
    InitWindow(larguraTela, alturaTela, "Defesa Celestial");

    Camera3D camara = { 0 };
    camara.position = (Vector3){ 0.0f, 0.0f, 0.0f }; 
    camara.target = (Vector3){ 0.0f, 0.0f, 10.0f };  
    camara.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camara.fovy = 45.0f;                             
    camara.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    struct Player nave = { 100, 0 };

    while (!WindowShouldClose()) {
        
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode3D(camara);
                DrawGrid(20, 1.0f); 
            EndMode3D();

            DrawCircleLines(larguraTela / 2, alturaTela / 2, 5, LIME);
            DrawText(TextFormat("VIDA: %d%%", nave.vida), 20, 20, 20, GREEN);
            DrawText("RADAR OFF", 20, 50, 20, RED);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
