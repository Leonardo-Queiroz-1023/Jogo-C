#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

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
    Vector2 posicao;
    float velocidade;
    float raio;
    bool ativo;
    struct Asteroide* prox;
} Asteroide;

typedef enum TelaJogo {
    TELA_INICIO,
    TELA_SCORE,
    TELA_JOGO,
    TELA_GAMEOVER
} TelaJogo;

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

Asteroide* CriarAsteroide(Asteroide* lista, int larguraTela) {
    Asteroide* novo = (Asteroide*)malloc(sizeof(Asteroide));
    
    novo->posicao.x = (float)GetRandomValue(40, larguraTela - 40);
    novo->posicao.y = -50.0f; 
    
    novo->velocidade = (float)GetRandomValue(2, 5); 
    novo->raio = 30.0f; 
    novo->ativo = true;
    
    novo->prox = lista;
    return novo;
}

static void DesenharTextoCentralizado(const char* texto, int y, int tamanho, Color cor) {
    int larguraTexto = MeasureText(texto, tamanho);
    DrawText(texto, 400 - larguraTexto / 2, y, tamanho, cor);
}

static void DesenharTelaInicio(int larguraTela, int alturaTela) {
    float tempo = GetTime();
    Rectangle botaoIniciar = {
        larguraTela / 2.0f - 120.0f,
        alturaTela / 2.0f + 75.0f,
        240.0f,
        52.0f
    };

    ClearBackground((Color){ 8, 11, 24, 255 });

    for (int i = 0; i < 70; i++) {
        float x = (float)((i * 113) % larguraTela);
        float y = fmodf((float)((i * 79) % alturaTela) + tempo * (8.0f + (float)(i % 4)), (float)alturaTela);
        Color cor = (i % 3 == 0) ? SKYBLUE : LIGHTGRAY;
        DrawPixel((int)x, (int)y, cor);
    }

    DrawCircleGradient(larguraTela / 2, 215, 165, (Color){ 21, 44, 84, 180 }, (Color){ 8, 11, 24, 0 });
    DrawCircleLines(larguraTela / 2, 215, 118, (Color){ 65, 159, 255, 140 });
    DrawCircleLines(larguraTela / 2, 215, 82, (Color){ 129, 230, 217, 120 });

    DesenharTextoCentralizado("DEFESA CELESTIAL", 170, 44, RAYWHITE);
    DesenharTextoCentralizado("Proteja a nave dos perigos do espaco", 225, 20, LIGHTGRAY);

    DrawRectangleRounded(botaoIniciar, 0.12f, 8, (Color){ 30, 132, 73, 255 });
    DrawRectangleRoundedLines(botaoIniciar, 0.12f, 8, (Color){ 144, 238, 144, 255 });
    DesenharTextoCentralizado("INICIAR", (int)botaoIniciar.y + 15, 22, RAYWHITE);

    DesenharTextoCentralizado("Pressione ENTER ou clique para jogar", 430, 20, YELLOW);
    DesenharTextoCentralizado("Pressione S para ver os scores", 462, 18, SKYBLUE);
    DesenharTextoCentralizado("Use o mouse para mirar e clique para atirar", 495, 18, GRAY);
}

static void DesenharTelaScore(int larguraTela, int alturaTela, int scores[2][2]) {
    const int linhas = 2;
    const int colunas = 2;
    const int larguraCelula = 210;
    const int alturaCelula = 105;
    const int espaco = 18;
    const int larguraGrade = colunas * larguraCelula + (colunas - 1) * espaco;
    const int alturaGrade = linhas * alturaCelula + (linhas - 1) * espaco;
    const int inicioX = larguraTela / 2 - larguraGrade / 2;
    const int inicioY = alturaTela / 2 - alturaGrade / 2 + 20;
    const char* nomes[2][2] = {
        { "SCORE ATUAL", "RECORDE" },
        { "DISPAROS", "VIDA" }
    };
    Color cores[2][2] = {
        { YELLOW, GREEN },
        { SKYBLUE, LIME }
    };

    ClearBackground((Color){ 10, 14, 28, 255 });

    DesenharTextoCentralizado("PAINEL DE SCORE", 65, 40, RAYWHITE);
    DesenharTextoCentralizado("Matriz 2x2 de desempenho", 112, 20, LIGHTGRAY);

    for (int linha = 0; linha < linhas; linha++) {
        for (int coluna = 0; coluna < colunas; coluna++) {
            int x = inicioX + coluna * (larguraCelula + espaco);
            int y = inicioY + linha * (alturaCelula + espaco);
            Rectangle celula = { (float)x, (float)y, (float)larguraCelula, (float)alturaCelula };
            int larguraValor = MeasureText(TextFormat("%d", scores[linha][coluna]), 36);

            DrawRectangleRounded(celula, 0.08f, 6, (Color){ 22, 33, 58, 255 });
            DrawRectangleRoundedLines(celula, 0.08f, 6, (Color){ 86, 180, 255, 255 });
            DrawText(nomes[linha][coluna], x + 18, y + 18, 18, LIGHTGRAY);
            DrawText(TextFormat("[%d][%d]", linha, coluna), x + larguraCelula - 72, y + 18, 16, GRAY);
            DrawText(TextFormat("%d", scores[linha][coluna]), x + larguraCelula / 2 - larguraValor / 2, y + 53, 36, cores[linha][coluna]);
        }
    }

    DesenharTextoCentralizado("[0][0] score | [0][1] recorde | [1][0] disparos | [1][1] vida", 438, 17, LIGHTGRAY);
    DesenharTextoCentralizado("BACKSPACE volta | ENTER inicia/retorna ao jogo", 472, 18, YELLOW);
}

static void DesenharTelaGameOver(int alturaTela, int pontosFinais) {
    ClearBackground((Color){ 36, 11, 11, 255 }); // Fundo vermelho escuro

    DesenharTextoCentralizado("GAME OVER", alturaTela / 2 - 100, 56, RED);
    DrawCircleLines(400, alturaTela / 2 - 75, 120, (Color){ 231, 76, 60, 60 });
    
    DesenharTextoCentralizado("A defesa da nave falhou!", alturaTela / 2 - 30, 20, LIGHTGRAY);
    
    DesenharTextoCentralizado(TextFormat("PONTUACAO FINAL: %d", pontosFinais), alturaTela / 2 + 15, 28, YELLOW);
    
    DesenharTextoCentralizado("Pressione ENTER para tentar novamente", alturaTela / 2 + 80, 20, RAYWHITE);
    DesenharTextoCentralizado("Pressione S para ver o Painel de Scores", alturaTela / 2 + 115, 18, SKYBLUE);
}

int main(void){
    
    const int larguraTela = 800;
    const int alturaTela = 600;

    InitWindow(larguraTela, alturaTela, "Defesa Celestial");

    struct Player nave;
    nave.vida = 100;
    nave.pontos = 0;
    int recorde = 0;
    int tirosDisparados = 0;

    int matrizScores[2][2] = {
        { nave.pontos, recorde },
        { tirosDisparados, nave.vida }
    };

    Tiro* listaTiros = NULL;
    Asteroide* listaAsteroides = NULL;

    Texture2D textAsteroide = LoadTexture("assets/asteroide.png");

    Camera3D camara = { 0 };
    camara.position = (Vector3){ 0.0f, 0.0f, 0.0f }; 
    camara.target = (Vector3){ 0.0f, 0.0f, 10.0f };  
    camara.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camara.fovy = 45.0f;                                             
    camara.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    TelaJogo telaAtual = TELA_INICIO;
    TelaJogo telaAnteriorScore = TELA_INICIO;
    ShowCursor();

    while (!WindowShouldClose()) {
        Vector2 miraMouse = GetMousePosition();
        if (nave.pontos > recorde) recorde = nave.pontos;
        matrizScores[0][0] = nave.pontos;
        matrizScores[0][1] = recorde;
        matrizScores[1][0] = tirosDisparados;
        matrizScores[1][1] = nave.vida;

        // --- TELA INICIAL ---
        if (telaAtual == TELA_INICIO) {
            if (IsKeyPressed(KEY_S)) {
                telaAnteriorScore = TELA_INICIO;
                telaAtual = TELA_SCORE;
            }

            if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                telaAtual = TELA_JOGO;
                HideCursor();
            }

            BeginDrawing();
                DesenharTelaInicio(larguraTela, alturaTela);
            EndDrawing();
            continue;
        }

        // --- TELA DE SCORES ---
        if (telaAtual == TELA_SCORE) {
            if (IsKeyPressed(KEY_BACKSPACE)) {
                telaAtual = telaAnteriorScore;
                if (telaAtual == TELA_JOGO) HideCursor();
                else ShowCursor();
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (telaAnteriorScore == TELA_GAMEOVER) {
                    nave.vida = 100;
                    nave.pontos = 0;
                }
                telaAtual = TELA_JOGO;
                HideCursor();
            }

            BeginDrawing();
                DesenharTelaScore(larguraTela, alturaTela, matrizScores);
            EndDrawing();
            continue;
        }

        // --- TELA DE GAME OVER ---
        if (telaAtual == TELA_GAMEOVER) {
            if (IsKeyPressed(KEY_S)) {
                telaAnteriorScore = TELA_GAMEOVER;
                telaAtual = TELA_SCORE;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                // Limpar listas de entidades antigas da memoria
                Tiro* t = listaTiros;
                while (t != NULL) {
                    Tiro* temp = t;
                    t = t->prox;
                    free(temp);
                }
                listaTiros = NULL;

                Asteroide* a = listaAsteroides;
                while (a != NULL) {
                    Asteroide* temp = a;
                    a = a->prox;
                    free(temp);
                }
                listaAsteroides = NULL;

                // Resetar os atributos do jogador
                nave.vida = 100;
                nave.pontos = 0;
                telaAtual = TELA_JOGO;
                HideCursor();
            }

            BeginDrawing();
                DesenharTelaGameOver(alturaTela, nave.pontos);
            EndDrawing();
            continue;
        }

        // --- LOGICA PRINCIPAL DO JOGO (TELA_JOGO) ---
        if (IsKeyPressed(KEY_S)) {
            telaAnteriorScore = TELA_JOGO;
            telaAtual = TELA_SCORE;
            ShowCursor();
            continue;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 pontaArmaCentro = { 400.0f, 420.0f };
            
            listaTiros = Atirar(listaTiros, pontaArmaCentro, miraMouse);
            tirosDisparados += 1;
        }

        if (GetRandomValue(1, 100) <= 2) {
            listaAsteroides = CriarAsteroide(listaAsteroides, larguraTela);
        }

        // Colisao: Tiro vs Asteroide
        Tiro* tCheck = listaTiros;
        while (tCheck != NULL) {
            Asteroide* aCheck = listaAsteroides;
            while (aCheck != NULL) {
                if (tCheck->ativo && aCheck->ativo && CheckCollisionCircles(tCheck->posicao, tCheck->raio, aCheck->posicao, aCheck->raio)) {
                    tCheck->ativo = false;
                    aCheck->ativo = false;
                    nave.pontos += 10;
                }
                aCheck = aCheck->prox;
            }
            tCheck = tCheck->prox;
        }

        // Atualizacao e Limpeza de Asteroides
        Asteroide* astAtual = listaAsteroides;
        Asteroide* astAnterior = NULL;

        while (astAtual != NULL) {
            astAtual->posicao.y += astAtual->velocidade;

            // Asteroide atingiu a base da nave
            if (astAtual->ativo && (astAtual->posicao.y + astAtual->raio >= 450.0f)) {
                astAtual->ativo = false;
                nave.vida -= 10;
                if (nave.vida <= 0) {
                    nave.vida = 0;
                    telaAtual = TELA_GAMEOVER;
                    ShowCursor();
                }
            }

            if (astAtual->posicao.y > alturaTela || !astAtual->ativo) {
                Asteroide* remover = astAtual;
                if (astAnterior == NULL) listaAsteroides = astAtual->prox;
                else astAnterior->prox = astAtual->prox;
                
                astAtual = astAtual->prox;
                free(remover); 
            } else {
                astAnterior = astAtual;
                astAtual = astAtual->prox;
            }
        }

        // Atualizacao e Limpeza de Tiros
        Tiro* atual = listaTiros;
        Tiro* anterior = NULL;

        while (atual != NULL) {
            atual->posicao.x += atual->velocidade.x;
            atual->posicao.y += atual->velocidade.y;

            if (atual->posicao.y < 0 || atual->posicao.x < 0 || atual->posicao.x > larguraTela || !atual->ativo) {
                Tiro* remover = atual;
                if (anterior == NULL) listaTiros = atual->prox;
                else anterior->prox = atual->prox;
                
                atual = atual->prox;
                free(remover); 
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }

        // Renderizacao do Jogo Ativo
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode3D(camara);
                DrawGrid(20, 1.0f); 
            EndMode3D();

            Tiro* tiroDesenho = listaTiros;
            while (tiroDesenho != NULL) {
                DrawCircle(tiroDesenho->posicao.x, tiroDesenho->posicao.y, tiroDesenho->raio, YELLOW);
                tiroDesenho = tiroDesenho->prox; 
            }

            Asteroide* astDesenho = listaAsteroides;
            while (astDesenho != NULL) {
                if (textAsteroide.width == 0) {
                    DrawCircle(astDesenho->posicao.x, astDesenho->posicao.y, astDesenho->raio, RED);
                } else {
                    Rectangle origemImg = { 0.0f, 0.0f, (float)textAsteroide.width, (float)textAsteroide.height };
                    Rectangle destinoTela = { 
                        astDesenho->posicao.x, 
                        astDesenho->posicao.y, 
                        astDesenho->raio * 2.0f, 
                        astDesenho->raio * 2.0f 
                    };
                    Vector2 centroOrigem = { astDesenho->raio, astDesenho->raio };
                    DrawTexturePro(textAsteroide, origemImg, destinoTela, centroOrigem, 0.0f, WHITE);
                }
                astDesenho = astDesenho->prox;
            }

            DrawRectangle(385, 420, 30, 80, MAROON); 

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
    
    UnloadTexture(textAsteroide);

    CloseWindow();
    return 0;
}