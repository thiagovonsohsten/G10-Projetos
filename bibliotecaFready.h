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
    char nome [101];
    char email [20];
    char cpf [12];
    char papel[10]; //residente,preceptor,adm
    char email_preceptor[20]; // id do preceptor que está supervisionando o residente
    char especializacao [20];
    //Acrescentar possível imagem para o sensor
    struct historico *Head;
}residente;
typedef struct {
    char nome [101];
    char email [20];
    char cpf [12];
    char papel[10]; //residente,preceptor,adm
    char CRM [14]; // CRM/PE 111111
    char especializacao [20];
    //Acrescentar possível imagem para o sensor
}medico;

typedef struct {
    char nome[101];
    char email[20];
    char cpf[12];
    char papel[10];
}adm;
typedef struct {
    residente aluno;
    lista_aluno* next;
}lista_aluno;

typedef struct {
    medico preceptor;
    lista_medico *next;
}lista_medico;
#endif