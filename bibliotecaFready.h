#ifndef __Fready__
#define __Fready__
#include <time.h>

//Lista de presença
typedef struct {
    char email[20];
    time_t tempo;
    struct presenca *next;
}presenca;

//lista para o histórico de cada preceptor
typedef struct {
    time_t entrada;
    time_t saida;
    struct historico *next;
}historico;

//Estrutura de dados do aluno
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

//Estrutura de dados do medico
typedef struct {
    char nome [101];
    char email [20];
    char cpf [12];
    char papel[10]; //residente,preceptor,adm
    char CRM [14]; // CRM/PE 111111
    char especializacao [20];
    //Acrescentar possível imagem para o sensor
}medico;

//Estrutura de dados da ADM
typedef struct {
    char nome[101];
    char email[20];
    char cpf[12];
    char papel[10];
}adm;

//Lista que contem os alunos para simulação do armazenamento do banco de dados
typedef struct {
    residente aluno;
    struct lista_aluno* next;
}lista_aluno;

//Lista que contem os preceptores para simulação do armazenamento do banco de dados
typedef struct {
    medico preceptor;
    struct lista_medico *next;
}lista_medico;
#endif