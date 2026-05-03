#define ARQIVO_PONTOS "DADOS.txt"
#include "main.c"
#define linhas 10
#define colunas 2

typedef struct lista{
    int pontos;
    int tempo;
    struct lista* prox;
} Lista;

static Lista* criarNo(int pontos,int tempo){
    Lista* novoNo = (Lista*)malloc(sizeof(Lista));
    if (novoNo == NULL){
        printf("Erro ao alocar memória para o nó.\n");
        return NULL;
    }
    NovoNo->pontos = pontos;
    NovoNo->tempo = tempo;
    NovoNo->prox = NULL;
    return NovoNo
}