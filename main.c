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
    int pontos;
    float posX;
    float posY;
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

    struct Player nave;
    nave.vida = 100;
    nave.pontos = 0;
    nave.posX = larguraTela / 2.0f;
    nave.posY = alturaTela * 0.8f;

    Camera3D camara = { 0 };
    camara.position = (Vector3){ 0.0f, 0.0f, 0.0f }; 
    camara.target = (Vector3){ 0.0f, 0.0f, 10.0f };  
    camara.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camara.fovy = 45.0f;                             
    camara.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        
        if (IsKeyDown(KEY_RIGHT)) nave.posX += 5.0f;
        if (IsKeyDown(KEY_LEFT)) nave.posX -= 5.0f;

        BeginDrawing();
            ClearBackground(BLACK);

            // O grid 3D que você fez
            BeginMode3D(camara);
                DrawGrid(20, 1.0f); 
            EndMode3D();

            float baseNave = 60.0f;
            float alturaNave = 70.0f;

            Vector2 topo = { nave.posX, nave.posY - (alturaNave/2) };
            Vector2 esquerda = { nave.posX - (baseNave/2), nave.posY + (baseNave/2) };
            Vector2 direita = { nave.posX + (baseNave/2), nave.posY + (baseNave/2) };

            DrawTriangle(topo, esquerda, direita, LIME); // Desenha a nave verde

            DrawCircleLines(larguraTela / 2, alturaTela / 2, 5, LIME);
            DrawText(TextFormat("VIDA: %d%%", nave.vida), 20, 20, 20, GREEN);
            DrawText("RADAR OFF", 20, 50, 20, RED);

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}