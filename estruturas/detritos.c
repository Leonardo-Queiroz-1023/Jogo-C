#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

typedef struct Asteroides{
     
    float tamanho;
    float velocidade;
    float distancia;
    float massa;
    bool perigoso;
    char *elementos;

}Asteroides;

const char* verificar_Asteroides_ou_cometas(Asteroides *elementos ){
    if(elementos==Gelo){
        return "Cometa";
    }else{
        return "Asteroides";
    }
}