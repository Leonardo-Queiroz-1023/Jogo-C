#define ARQUIVO_PONTOS "DADOS.txt"
#define linhas 10
#define colunas 2

typedef struct lista{
    int pontos;
    int tempo;
    struct lista* prox;
} Lista;

static Lista* criarNo(int pontos,int tempo){
    Lista* NovoNo = (Lista*)malloc(sizeof(Lista));
    if (NovoNo == NULL){
        printf("Erro ao alocar memória para o nó.\n");
        return NULL;
    }
    NovoNo->pontos = pontos;
    NovoNo->tempo = tempo;
    NovoNo->prox = NULL;
    return NovoNo;
}
static void Add_crecente(Lista **head, int pontos, int tempo){
    
    Lista* novoNo= criarNo(pontos,tempo);
    if(*head == NULL || pontos < (*head)->pontos){
        novoNo->prox = *head;
        *head = novoNo;
        return;
    }
    Lista* atual = *head;
    while(atual->prox != NULL && atual->prox->pontos < pontos){
        atual = atual->prox;
    }
    novoNo->prox = atual->prox;
    atual->prox = novoNo;
}
static void salvarPontos(Lista* head){
    FILE* arquivo = fopen(ARQUIVO_PONTOS, "w");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    Lista* atual = head;
    while (atual != NULL){
        fprintf(arquivo, "%d %d\n", atual->pontos, atual->tempo);
        atual = atual->prox;
    }
    fclose(arquivo);
}
static Lista* LerPontos(){
     Lista*head=NULL;
     FILE* arquivo = fopen(ARQUIVO_PONTOS, "r");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo para leitura.\n");
        return NULL;
    }
    int pontos, tempo;
    while(fscanf(arquivo, "%d %d", &pontos , &tempo)==2){
        Add_crecente(&head, pontos, tempo);
    }
    fclose(arquivo);
    return head;
}