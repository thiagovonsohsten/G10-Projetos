#ifndef __Fready__
#define __Fready__
#include <time.h>

typedef struct {
    char email[20];
    time_t tempo;
    struct presenca *next;
}presenca;

typedef struct {
    time_t entrada;
    time_t saida;
    struct historico *next;
}historico;
typedef struct {
    char matricula[20];
    char email [20];
    char papel[10]; //residente,preceptor,adm
    char email_preceptor[20]; // id do preceptor que está supervisionando o residente
    char nome [101];
    char curso [20];
    char cpf [12];
    //Acrescentar possível imagem para o sensor
    struct historico *Head;
}residente;

//falta fazer daqui
struct medico {
    char matricula[20];
    char email [20];
    char papel[10]; //residente,preceptor,adm
    char CRM [14]; // CRM/PE 111111
    char nome [101];
    char curso [20];
    char cpf [12];
    //Acrescentar possível imagem para o sensor
};

#endif