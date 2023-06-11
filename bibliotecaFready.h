#ifndef __Fready__
#define __Fready__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Lista de presença
typedef struct presenca{
    char email[20];
    time_t tempo;
    struct presenca *next;
}presenca;

//lista para o histórico de cada preceptor
typedef struct historico{
    time_t entrada;
    time_t saida;
    struct historico *next;
}historico;

//Estrutura de dados do aluno
typedef struct {
    char nome [101];
    char email [20];
    char cpf [15];
    char papel[12]; //residente,preceptor,adm
    char email_preceptor[20]; // id do preceptor que está supervisionando o residente
    char especializacao [20];
    //Acrescentar possível imagem para o sensor
    struct historico *lista_de_Presenca;
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
typedef struct lista_aluno{
    residente* aluno;
    struct lista_aluno* next;
}lista_aluno;

//Lista que contem os preceptores para simulação do armazenamento do banco de dados
typedef struct lista_medico {
    medico* preceptor;
    struct lista_medico *next;
}lista_medico;

typedef struct lista_adm {
    adm* administrador;
    struct lista_adm *next;
}lista_adm;

residente encontrar_aluno_por_email(char email);

void lg_residente (char email[20], lista_aluno* lista_de_alunos) {
    //busca nos arquivos o email e nível
    lista_aluno* Residente=lista_de_alunos;
    while (strcmp(Residente->aluno->email,email)!=0 || Residente==NULL){
        Residente=Residente->next;
    }
    if (Residente==NULL){
        printf("Erro ao localizar usuario!\n");
        return;
    }

    //Menu com:
        //Dados do Residente
        //Histórico de presença acessado pela lista de struct
        // Menu do lg_residente
    int opcao = -1;
    while (opcao != 0) {
        printf("\n--- Menu do Residente ---\n");
        printf("1. Visualizar seus dados\n");
        printf("2. Visualizar histórico de presença\n");
        printf("0. Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                // Exibe os residente do lg_residente
                printf("\n--- Dados do Residente ---\n");
                printf("Nome: %s\n", Residente->aluno->nome);
                printf("CPF: %s\n", Residente->aluno->cpf);
                printf("E-mail: %s\n", Residente->aluno->email);
                printf("E-mail do Preceptor: %s\n", Residente->aluno->email_preceptor);
                printf("Especialização: %s\n", Residente->aluno->especializacao);
                printf("ID do Preceptor: %s\n", Residente->aluno->email_preceptor);
                while(Residente->aluno->lista_de_Presenca->next!=NULL){
                    printf("Entrada: %ld\nSaida: %ld\n",Residente->aluno->lista_de_Presenca->entrada,Residente->aluno->lista_de_Presenca->saida);
                    if (Residente->aluno->lista_de_Presenca->next!=NULL){
                    Residente->aluno->lista_de_Presenca=Residente->aluno->lista_de_Presenca->next;
                    }else {
                        Residente->aluno->lista_de_Presenca->next=NULL;
                    }
                }
                break;
            case 2:
                // Exibe o histórico de presença do lg_residente
                printf("\n--- Histórico de Presença ---\n");
                //historico* temporario = Residente->Head;
                // while (temporario != NULL) {
                //     printf("Entrada: %s", asctime(localtime(&(temporario->entrada))));
                //     printf("Saída: %s", asctime(localtime(&(temporario->saida))));
                //     double diferenca = difftime(temporario->saida, temporario->entrada);
                //     printf("Tempo de Trabalho: %lf segundos\n", diferenca);
                //     printf("\n");
                //     temporario = temporario->next;
                // }
                break;
            case 0:
                // Sair do menu
                printf("\nSaindo...\nAté breve! By: Fready!\n");
                break;
            default:
                printf("\nOpção inválida, tente novamente.\n");
        }
    }
}

void lg_medico(char email, char papel);

void lg_adm(char email, char papel);

#endif