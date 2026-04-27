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
} player;

typedef struct Tiro{
    Vector2 posicao;
    Vector2 velocidade; 
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

Tiro* Atirar(Tiro* lista, Vector2 origem, Vector2 alvo) {
    Tiro* novoTiro = (Tiro*)malloc(sizeof(Tiro));
    
    novoTiro->posicao = origem;
    novoTiro->raio = 4.0f;
    novoTiro->ativo = true;
    
    float dx = alvo.x - origem.x;
    float dy = alvo.y - origem.y;
    float distancia = sqrt(dx*dx + dy*dy);
    float velocidadeBase = 15.0f; 
    
    if (distancia != 0) {
        novoTiro->velocidade.x = (dx / distancia) * velocidadeBase;
        novoTiro->velocidade.y = (dy / distancia) * velocidadeBase;
    } else {
        novoTiro->velocidade.x = 0;
        novoTiro->velocidade.y = -velocidadeBase;
    }
    
    novoTiro->prox = lista;
    return novoTiro;
}

int main(void){
    
    const int larguraTela = 800;
    const int alturaTela = 600;

    InitWindow(larguraTela, alturaTela, "Defesa Celestial");

    struct Player nave;
    nave.vida = 100;
    nave.pontos = 0;

    Camera3D camara = { 0 };
    camara.position = (Vector3){ 0.0f, 0.0f, 0.0f }; 
    camara.target = (Vector3){ 0.0f, 0.0f, 10.0f };  
    camara.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camara.fovy = 45.0f;                             
    camara.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
    HideCursor(); 

    while (!WindowShouldClose()) {
        
        Vector2 miraMouse = GetMousePosition();

        BeginDrawing();
            ClearBackground(BLACK);

            // O grid 3D que você fez
            BeginMode3D(camara);
                DrawGrid(20, 1.0f); 
            EndMode3D();

            DrawRectangle(200, 420, 30, 80, MAROON); 
            DrawRectangle(570, 420, 30, 80, MAROON); 

            DrawRectangle(0, 450, larguraTela, 150, DARKGRAY); 
            DrawRectangle(0, 450, larguraTela, 10, BLACK);

            DrawCircleLines(miraMouse.x, miraMouse.y, 10, LIME);
            DrawPixel(miraMouse.x, miraMouse.y, LIME);

            DrawText(TextFormat("VIDA: %d%%", nave.vida), 30, 480, 20, GREEN);
            DrawText("RADAR OFF", 30, 520, 20, RED);
            DrawText("PAINEL DA NAVE", larguraTela/2 - 80, 500, 20, LIGHTGRAY);
            DrawText(TextFormat("PONTOS: %d", nave.pontos), larguraTela - 150, 480, 20, YELLOW);
            
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}