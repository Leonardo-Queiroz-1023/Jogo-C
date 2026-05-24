#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "Salvar.c"

#define MAXIMO FLT_MAX
#define MAX_ESTRELAS 80

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

typedef struct Estrela {
    Vector2 posicao;
    float velocidade;
    float tamanho;
    Color cor;
} Estrela;

typedef enum TelaJogo {
    TELA_INICIO,
    TELA_SCORE,
    TELA_JOGO,
    TELA_GAMEOVER
} TelaJogo;

Tiro* Atirar(Tiro* lista, Vector2 origem, Vector2 alvo) {
    Tiro* novoTiro = (Tiro*)malloc(sizeof(Tiro)); 
    
    novoTiro->posicao = origem;
    novoTiro->raio = 5.0f;
    novoTiro->ativo = true;
    
    float dx = alvo.x - origem.x;
    float dy = alvo.y - origem.y;
    float distancia = sqrt(dx*dx + dy*dy);
    float velocidadeBase = 16.0f; 
    
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
    
    novo->velocidade = (float)GetRandomValue(3, 6); 
    novo->raio = (float)GetRandomValue(25, 45); 
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

    ClearBackground((Color){ 6, 8, 18, 255 });

    for (int i = 0; i < 70; i++) {
        float x = (float)((i * 113) % larguraTela);
        float y = fmodf((float)((i * 79) % alturaTela) + tempo * (12.0f + (float)(i % 4)), (float)alturaTela);
        Color cor = (i % 3 == 0) ? SKYBLUE : LIGHTGRAY;
        DrawPixel((int)x, (int)y, cor);
    }

    DrawCircleGradient(larguraTela / 2, 215, 165, (Color){ 14, 34, 74, 180 }, (Color){ 6, 8, 18, 0 });
    DrawCircleLines(larguraTela / 2, 215, 118, (Color){ 0, 150, 255, 140 });
    DrawCircleLines(larguraTela / 2, 215, 82, (Color){ 0, 230, 200, 120 });

    DrawTextPro(GetFontDefault(), "DEFESA CELESTIAL", (Vector2){ (float)(larguraTela/2 - MeasureText("DEFESA CELESTIAL", 46)/2), 165 }, (Vector2){0,0}, 0.0f, 46, 3.0f, WHITE);
    DesenharTextoCentralizado("Proteja a base orbital dos perigos do espaco", 225, 18, LIGHTGRAY);

    DrawRectangleRounded(botaoIniciar, 0.2f, 8, (Color){ 16, 120, 60, 255 });
    DrawRectangleRoundedLines(botaoIniciar, 0.2f, 8, (Color){ 0, 255, 120, 255 });
    DesenharTextoCentralizado("INICIAR SISTEMAS", (int)botaoIniciar.y + 15, 20, RAYWHITE);

    DesenharTextoCentralizado("Pressione ENTER ou clique para jogar", 440, 18, YELLOW);
    DesenharTextoCentralizado("Pressione S para ver os registros de score", 470, 16, SKYBLUE);
}

static void DesenharTelaScore(int larguraTela, int alturaTela, int scores[2][2]) {
    const int linhas = 2;
    const int colunas = 2;
    const int larguraCelula = 220;
    const int alturaCelula = 110;
    const int espaco = 20;
    const int larguraGrade = colunas * larguraCelula + (colunas - 1) * espaco;
    const int alturaGrade = linhas * alturaCelula + (linhas - 1) * espaco;
    const int inicioX = larguraTela / 2 - larguraGrade / 2;
    const int inicioY = alturaTela / 2 - alturaGrade / 2 + 20;
    
    const char* nomes[2][2] = {
        { "SCORE DA MISSÃO", "RECORDE GLOBAL" },
        { "DISPAROS EFETUADOS", "INTEGRIDADE FINAL" }
    };
    Color cores[2][2] = {
        { YELLOW, SKYBLUE }, // Trocado de CYAN para SKYBLUE
        { MAGENTA, LIME }
    };

    ClearBackground((Color){ 5, 8, 16, 255 });

    DesenharTextoCentralizado("BANCO DE DADOS TÁTICOS", 65, 36, RAYWHITE);
    DesenharTextoCentralizado("Estatísticas de desempenho em tempo real", 112, 18, GRAY);

    for (int linha = 0; linha < linhas; linha++) {
        for (int coluna = 0; coluna < colunas; coluna++) {
            int x = inicioX + coluna * (larguraCelula + espaco);
            int y = inicioY + linha * (alturaCelula + espaco);
            Rectangle celula = { (float)x, (float)y, (float)larguraCelula, (float)alturaCelula };
            int larguraValor = MeasureText(TextFormat("%d", scores[linha][coluna]), 38);

            DrawRectangleRounded(celula, 0.1f, 6, (Color){ 12, 19, 36, 255 });
            DrawRectangleRoundedLines(celula, 0.1f, 6, (Color){ 0, 180, 255, 150 });
            DrawText(nomes[linha][coluna], x + 15, y + 15, 14, LIGHTGRAY);
            DrawText(TextFormat("[%d][%d]", linha, coluna), x + larguraCelula - 55, y + 15, 12, DARKGRAY);
            DrawText(TextFormat("%d", scores[linha][coluna]), x + larguraCelula / 2 - larguraValor / 2, y + 50, 38, cores[linha][coluna]);
        }
    }

    DesenharTextoCentralizado("BACKSPACE retorna | ENTER inicia nova simulação", 475, 18, YELLOW);
}

static void DesenharTelaGameOver(int alturaTela, int pontosFinais) {
    ClearBackground((Color){ 20, 5, 5, 255 }); 

    DrawCircleGradient(400, alturaTela / 2 - 60, 200, (Color){ 180, 0, 0, 40 }, (Color){ 20, 5, 5, 0 });
    
    DesenharTextoCentralizado("SISTEMA DESTRUÍDO", alturaTela / 2 - 110, 50, RED);
    DesenharTextoCentralizado("A integridade do casco chegou a 0%", alturaTela / 2 - 40, 18, LIGHTGRAY);
    
    DrawRectangle(250, alturaTela / 2, 300, 50, (Color){ 40, 10, 10, 255 });
    DrawRectangleLines(250, alturaTela / 2, 300, 50, RED);
    
    int largPontos = MeasureText(TextFormat("PONTOS: %d", pontosFinais), 24);
    DrawText(TextFormat("PONTOS OBTIDOS: %d", pontosFinais), 400 - largPontos/2, alturaTela / 2 + 12, 24, GOLD);
    
    DesenharTextoCentralizado("Pressione ENTER para reinicializar os motores", alturaTela / 2 + 85, 18, RAYWHITE);
    DesenharTextoCentralizado("Pressione S para ver o registro de falhas", alturaTela / 2 + 120, 16, SKYBLUE);
}

int main(void){
    
    const int larguraTela = 800;
    const int alturaTela = 600;

    InitWindow(larguraTela, alturaTela, "Defesa Celestial - Core Upgrade");

    struct Player nave;
    nave.vida = 100;
    nave.pontos = 0;
    Lista* historicoPontos = lerPontos();
    int recorde = 0;
    if (historicoPontos != NULL) {
        recorde = historicoPontos->pontos;
    }
    int tirosDisparados = 0;

    int matrizScores[2][2] = {
        { nave.pontos, recorde },
        { tirosDisparados, nave.vida }
    };

    Tiro* listaTiros = NULL;
    Asteroide* listaAsteroides = NULL;

    Estrela estrelas[MAX_ESTRELAS];
    for(int i = 0; i < MAX_ESTRELAS; i++) {
        estrelas[i].posicao.x = (float)GetRandomValue(0, larguraTela);
        estrelas[i].posicao.y = (float)GetRandomValue(0, alturaTela - 150);
        estrelas[i].velocidade = (float)GetRandomValue(1, 4);
        estrelas[i].tamanho = estrelas[i].velocidade * 0.7f;
        estrelas[i].cor = (GetRandomValue(0, 1) == 0) ? SKYBLUE : WHITE;
    }

    // Configurado exatamente com o nome que aparece na sua pasta assets
    Texture2D textAsteroide = LoadTexture("assets/asteroide.png.png");
    Texture2D textNave = LoadTexture("assets/nave.png"); 

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

        if (telaAtual == TELA_GAMEOVER) {
            if (IsKeyPressed(KEY_S)) {
                telaAnteriorScore = TELA_GAMEOVER;
                telaAtual = TELA_SCORE;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                Tiro* t = listaTiros;
                while (t != NULL) { Tiro* temp = t; t = t->prox; free(temp); }
                listaTiros = NULL;

                Asteroide* a = listaAsteroides;
                while (a != NULL) { Asteroide* temp = a; a = a->prox; free(temp); }
                listaAsteroides = NULL;

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

        if (IsKeyPressed(KEY_S)) {
            telaAnteriorScore = TELA_JOGO;
            telaAtual = TELA_SCORE;
            ShowCursor();
            continue;
        }

        for(int i = 0; i < MAX_ESTRELAS; i++) {
            estrelas[i].posicao.y += estrelas[i].velocidade;
            if(estrelas[i].posicao.y > 450) {
                estrelas[i].posicao.y = 0;
                estrelas[i].posicao.x = (float)GetRandomValue(0, larguraTela);
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && miraMouse.y < 450) {
            Vector2 pontaArmaCentro = { 400.0f, 410.0f };
            listaTiros = Atirar(listaTiros, pontaArmaCentro, miraMouse);
            tirosDisparados += 1;
        }

        if (GetRandomValue(1, 100) <= 3) {
            listaAsteroides = CriarAsteroide(listaAsteroides, larguraTela);
        }

        Tiro* tCheck = listaTiros;
        while (tCheck != NULL) {
            Asteroide* aCheck = listaAsteroides;
            while (aCheck != NULL) {
                if (tCheck->ativo && aCheck->ativo && CheckCollisionCircles(tCheck->posicao, tCheck->raio, aCheck->posicao, aCheck->raio)) {
                    tCheck->ativo = false;
                    aCheck->ativo = false;
                    nave.pontos += 15; 
                }
                aCheck = aCheck->prox;
            }
            tCheck = tCheck->prox;
        }

        Asteroide* astAtual = listaAsteroides;
        Asteroide* astAnterior = NULL;
        while (astAtual != NULL) {
            astAtual->posicao.y += astAtual->velocidade;

            if (astAtual->ativo && (astAtual->posicao.y + astAtual->raio >= 430.0f)) {
                astAtual->ativo = false;
                nave.vida -= 15;
                if (nave.vida <= 0) {
                    nave.vida = 0;

                    // --- SALVA O ARQUIVO AQUI ---
                    Add_crecente(&historicoScores, nave.pontos, (int)GetTime());
                    salvarPontos(historicoScores);
                    // ----------------------------

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

        BeginDrawing();
            ClearBackground((Color){ 4, 5, 12, 255 }); 

            for(int i = 0; i < MAX_ESTRELAS; i++) {
                DrawCircle(estrelas[i].posicao.x, estrelas[i].posicao.y, estrelas[i].tamanho, estrelas[i].cor);
            }

            Tiro* tiroDesenho = listaTiros;
            while (tiroDesenho != NULL) {
                DrawCircle(tiroDesenho->posicao.x, tiroDesenho->posicao.y, tiroDesenho->raio + 2.0f, (Color){ 255, 230, 0, 100 });
                DrawCircle(tiroDesenho->posicao.x, tiroDesenho->posicao.y, tiroDesenho->raio, ORANGE);
                tiroDesenho = tiroDesenho->prox; 
            }

            Asteroide* astDesenho = listaAsteroides;
            while (astDesenho != NULL) {
                if (textAsteroide.width == 0) {
                    DrawCircleGradient(astDesenho->posicao.x, astDesenho->posicao.y, astDesenho->raio, DARKGRAY, MAROON);
                    DrawCircleLines(astDesenho->posicao.x, astDesenho->posicao.y, astDesenho->raio, GRAY);
                } else {
                    Rectangle origemImg = { 0.0f, 0.0f, (float)textAsteroide.width, (float)textAsteroide.height };
                    Rectangle destinoTela = { 
                        astDesenho->posicao.x, 
                        astDesenho->posicao.y, 
                        astDesenho->raio * 2.1f, 
                        astDesenho->raio * 2.1f 
                    };
                    Vector2 centroOrigem = { astDesenho->raio * 1.05f, astDesenho->raio * 1.05f };
                    DrawTexturePro(textAsteroide, origemImg, destinoTela, centroOrigem, astDesenho->posicao.y * 0.5f, WHITE); 
                }
                astDesenho = astDesenho->prox;
            }

            if (textNave.width == 0) {
                Vector2 p1 = { 400, 390 };
                Vector2 p2 = { 365, 445 };
                Vector2 p3 = { 435, 445 };
                DrawTriangle(p1, p2, p3, DARKBLUE);
                DrawTriangleLines(p1, p2, p3, SKYBLUE); // Mudado de CYAN para SKYBLUE
                DrawRectangle(393, 410, 14, 30, SKYBLUE); 
                DrawCircleGradient(400, 445, 12, ORANGE, (Color){255,0,0,0}); 
            } else {
                Rectangle origNave = { 0.0f, 0.0f, (float)textNave.width, (float)textNave.height };
                Rectangle destNave = { 400.0f, 420.0f, 70.0f, 70.0f };
                Vector2 centroNave = { 35.0f, 35.0f };
                DrawTexturePro(textNave, origNave, destNave, centroNave, 0.0f, WHITE);
            }

            DrawRectangle(0, 450, larguraTela, 150, (Color){ 10, 14, 26, 255 }); 
            DrawRectangle(0, 450, larguraTela, 4, SKYBLUE); // Mudado de CYAN para SKYBLUE
            
            for(int gi = 0; gi < larguraTela; gi += 40) {
                DrawLine(gi, 454, gi, 600, (Color){ 0, 150, 255, 25 });
            }

            if (miraMouse.y < 450) {
                DrawCircleLines(miraMouse.x, miraMouse.y, 14, (Color){ 0, 255, 100, 180 });
                DrawLine(miraMouse.x - 20, miraMouse.y, miraMouse.x + 20, miraMouse.y, LIME);
                DrawLine(miraMouse.x, miraMouse.y - 20, miraMouse.x, miraMouse.y + 20, LIME);
            }

            Color corVida = GREEN;
            if (nave.vida <= 30) corVida = RED;
            else if (nave.vida <= 60) corVida = ORANGE;

            DrawText("ESCUDO DA NAVE:", 35, 480, 14, LIGHTGRAY);
            DrawRectangle(35, 505, 200, 22, (Color){ 30, 30, 45, 255 }); 
            DrawRectangle(35, 505, (int)(nave.vida * 2), 22, corVida);     
            DrawRectangleLines(35, 505, 200, 22, WHITE);
            DrawText(TextFormat("%d%%", nave.vida), 115, 509, 15, BLACK);

            DrawRectangleLines(300, 475, 200, 80, (Color){ 0, 150, 255, 100 });
            DrawText("STATUS DE COMBATE", 325, 485, 14, SKYBLUE);
            if(nave.vida <= 30 && (int)(GetTime() * 3) % 2 == 0) {
                DrawText("PERIGO CRÍTICO", 335, 518, 16, RED);
            } else {
                DrawText("SISTEMAS OK", 348, 518, 16, GREEN);
            }

            DrawText(TextFormat("PONTUAÇÃO: %05d", nave.pontos), larguraTela - 210, 490, 18, YELLOW);
            DrawText(TextFormat("RECORDE: %05d", recorde), larguraTela - 210, 520, 14, GOLD);
            
        EndDrawing();
    }
    
    UnloadTexture(textAsteroide);
    UnloadTexture(textNave);

    CloseWindow();
    return 0;
}