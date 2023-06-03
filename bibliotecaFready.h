#ifndef __Fready__
#define __Fready__
#include <time.h>

typedef struct {
    char email[50];
    time_t tempo;
    struct presenca *next;
}presenca;

typedef struct {
    time_t entrada;
    time_t saida;
    struct historico *next;
}historico;

typedef struct {
    int id; //id do residente
    int id_preceptor; // id do preceptor que está supervisionando o residente
    char nome [101];
    char email [20];
    char cpf [12];
    char CRM [14]; // CRM/PE 111111
    //Acrescentar possível imagem para o sensor
    struct historico *Head;
}residente;


struct medico {
    struct dados alunos;
    struct medico *next;
};

#endif