#include <stdio.h>      //biblioteca padrão
#include <stdlib.h>     //Fornece funções como alocação de memória dinâmica, conversão de strings, geração de números aleatórios, entre outras
#include <string.h>     //Fornece funções para manipulação de strings, como copiar, concatenar, comparar e buscar.
#include <time.h>       //Biblioteca do C que contém funções para manipulação de tempo e data, como a função time(), que retorna o número de segundos desde a "época" (1 de janeiro de 1970).
#include "bibliotecaFready.h"

//vai pegar o "login.txt" e comparar com "senhasBC.txt" e usar o "banco_de_dados.txt" para buscar os dados do usuário no APP
typedef struct senhassalvas {
    char email[100];
    char senha[100];
    char papel [10];
    struct senhassalvas* next;
}senhassalvas;

int main (){
//ABRIR ARQUIVO PARA SIMULAR O BANCO DE DADOS
    char comp_email[100];
    char referencia_usuario[11];
    //estruturas de auxilio
    medico *preceptorM=(medico *)malloc(sizeof(medico));
    adm *administrador=(adm *)malloc(sizeof(adm));
    residente *aluno=(residente *)malloc(sizeof(residente));
    aluno->lista_de_Presenca=NULL;//histórico dos horários
    historico* auxH=NULL;
    //estruturas de listas
    lista_aluno* alunos_cadastrados = NULL;
    lista_aluno* auxLA=NULL;
    lista_medico* medicos_cadastrados = NULL;
    lista_medico* auxM=NULL;
    lista_adm* adms_cadastrados = NULL;
    lista_adm* auxA=NULL;
    FILE* banco_de_dados;
    banco_de_dados = fopen("banco_de_dados.txt", "r");
    while (!feof(banco_de_dados)) {
        fscanf(banco_de_dados, "%s\n", comp_email);
        //printf("Variavel comp_email: %s\n",comp_email);
        fscanf(banco_de_dados, "%s\n", referencia_usuario);
        //printf("variavel referencia_usuario: %s\n",referencia_usuario);
        if(strcmp(referencia_usuario,"residente")==0){
            //printf("Entrou no if de residente\n");
            strcpy(aluno->email,comp_email);
            //printf("%s\n",aluno->email);
            strcpy(aluno->papel,referencia_usuario);
            //printf("%s\n",aluno->papel);
            fgets(aluno->nome, sizeof(aluno->nome), banco_de_dados);
            //fscanf(banco_de_dados, "%s\n", aluno->nome);
            int tamanho = strlen(aluno->nome);
            if (aluno->nome[tamanho-1] == '\n'){
                aluno->nome[tamanho-1] = '\0';
            }
            //printf("%s\n",aluno->nome);
            fscanf(banco_de_dados, "%s\n", aluno->cpf);
            //printf("%s\n",aluno->cpf);
            fscanf(banco_de_dados, "%s\n", aluno->email_preceptor);
            //printf("%s\n",aluno->email_preceptor);
            fscanf(banco_de_dados, "%s\n", aluno->especializacao);
            //printf("%s\n",aluno->especializacao);
            aluno->lista_de_Presenca = (historico *)malloc(sizeof(historico));
            auxH=aluno->lista_de_Presenca;
            while (fscanf(banco_de_dados, "%ld,", (&auxH->entrada)) == 1){
                //printf("Entrada: %ld\n",auxH->entrada);
                fscanf(banco_de_dados, "%ld,\n", (&auxH->saida));
                //printf("Saida: %ld\n",auxH->saida);
                auxH->next=(historico *)malloc(sizeof(historico));
                auxH=auxH->next;
                auxH->next=NULL;
            }
            if (alunos_cadastrados==NULL){
                //printf("Criou a primeira lista de alunos!\n");
                alunos_cadastrados=(lista_aluno *)malloc(sizeof(lista_aluno));
                alunos_cadastrados->next=NULL;
                alunos_cadastrados->aluno=aluno;
                aluno=(residente *)malloc(sizeof(residente));
            }else {
                auxLA=alunos_cadastrados;
                while (auxLA->next!=NULL){
                    auxLA = auxLA->next;
                }
                auxLA->next=(lista_aluno *)malloc(sizeof (lista_aluno));
                auxLA=auxLA->next;
                auxLA->aluno = aluno;
                auxLA->next = NULL;
                aluno=(residente *)malloc(sizeof(residente));
                //printf("Adicionou na lista de alunos!\n");
            }
        }else if (strcmp(referencia_usuario,"preceptor")==0){
            //printf("Entrou no if do preceptor\n");
            strcpy(preceptorM->email,comp_email);
            //printf("%s\n",preceptorM->email);
            strcpy(preceptorM->papel,referencia_usuario);
            //printf("%s\n",preceptorM->papel);
            fgets(preceptorM->nome, sizeof(preceptorM->nome), banco_de_dados);
            int tamanho = strlen(preceptorM->nome);
            if (preceptorM->nome[tamanho-1] == '\n'){
                preceptorM->nome[tamanho-1] = '\0';
            }
            //printf("%s\n",preceptorM->nome);
            fscanf(banco_de_dados, "%s\n", preceptorM->cpf);
            //printf("%s\n",preceptorM->cpf);
            fscanf(banco_de_dados, "%s\n", preceptorM->CRM);
            //printf("%s\n",preceptorM->CRM);
            fscanf(banco_de_dados, "%s\n", preceptorM->especializacao);
            //printf("%s\n",preceptorM->especializacao);
            if (medicos_cadastrados==NULL){
                //printf("Criou primeira lista de Medicos!\n");
                medicos_cadastrados=(lista_medico *)malloc(sizeof(lista_medico));
                medicos_cadastrados->next=NULL;
                medicos_cadastrados->preceptor=preceptorM;
                preceptorM=(medico *)malloc(sizeof(medico));
            }else{
                //printf("Entrou no else\n");
                auxM=medicos_cadastrados;
                while(auxM->next!=NULL){
                    //printf("while\n");
                    auxM=auxM->next;
                }
                auxM->next=(lista_medico* )malloc(sizeof(lista_medico));
                auxM=auxM->next;
                auxM->preceptor=preceptorM;
                auxM->next=NULL;
                preceptorM=(medico* )malloc(sizeof(medico));
                //printf("Adicionou na lista de medicos!\n");
            }
        }else if (strcmp(referencia_usuario,"adm")==0){
            //printf("Entrou no if do adm\n");
            strcpy(administrador->email,comp_email);
            //printf("%s\n",administrador->email);
            strcpy(administrador->papel,referencia_usuario);
            //printf("%s\n",administrador->papel);
            fgets(administrador->nome, sizeof(administrador->nome), banco_de_dados);
            int tamanho = strlen(administrador->nome);
            if (administrador->nome[tamanho-1] == '\n'){
                administrador->nome[tamanho-1] = '\0';
            }
            //printf("%s\n",administrador->nome);
            fscanf(banco_de_dados, "%s\n", administrador->cpf);
            //printf("%s\n",administrador->cpf);
            if (adms_cadastrados==NULL){
                //printf("Criou a primeira lista de ADM!\n");
                adms_cadastrados=(lista_adm *)malloc(sizeof(lista_adm));
                adms_cadastrados->next=NULL;
                adms_cadastrados->administrador=administrador;
                administrador=(adm *)malloc(sizeof(adm));
            }else{
                auxA=adms_cadastrados;
                while(auxA->next!=NULL){
                    auxA=auxA->next;
                }
                auxA->next=(lista_adm * )malloc(sizeof(lista_adm));
                auxA=auxA->next;
                auxA->administrador=administrador;
                auxA->next=NULL;
                administrador=(adm* )malloc(sizeof(adm));
                //printf("Adicionou na lista de ADM!\n");
            }
        }else{
            printf("Banco de dados com erro na identificacao do usuario!\n");
        }
    }
    fclose(banco_de_dados);
    //printf("Saiu do while\n");
    // auxLA=alunos_cadastrados;
    // while (auxLA!=NULL){
    //     printf("Nome:%s\nPapel:%s\nCPF:%s\nE-mail:%s\nE-mail do Preceptor:%s\nEspecialidade:%s\n",auxLA->aluno->nome,auxLA->aluno->papel,auxLA->aluno->cpf,auxLA->aluno->email,auxLA->aluno->email_preceptor,auxLA->aluno->especializacao);
    //     while(auxLA->aluno->lista_de_Presenca->next!=NULL){
    //         printf("Entrada: %ld\nSaida: %ld\n",auxLA->aluno->lista_de_Presenca->entrada,auxLA->aluno->lista_de_Presenca->saida);
    //         if (auxLA->aluno->lista_de_Presenca->next!=NULL){
    //         auxLA->aluno->lista_de_Presenca=auxLA->aluno->lista_de_Presenca->next;
    //         }else {
    //             auxLA->aluno->lista_de_Presenca->next=NULL;
    //         }
    //     }
    //     auxLA=auxLA->next;
    // }
    
//Com o Banco de Dados no sistema, segue o código.

    senhassalvas* lista_senhas = NULL;
    senhassalvas* aux = NULL;
    char conta[100];
    char senha[100];
    FILE* login;
    login = fopen("login.txt", "r");
    fscanf(login, "%s\n", conta);
    //printf("Login:%s\n",conta);
    fscanf(login, "%s\n", senha);
    //printf("Senha:%s\n",senha);
    fclose(login);
    FILE* senhasBC;
    senhasBC = fopen("senhasBC.txt","r");
    while (!feof(senhasBC)){
        //printf("cirulo do while\n");
        if (lista_senhas==NULL){
            lista_senhas=(senhassalvas *)malloc(sizeof(senhassalvas));
            fscanf(senhasBC, "%s\n", lista_senhas->email);
            fscanf(senhasBC, "%s\n", lista_senhas->senha);
            fscanf(senhasBC, "%s\n", lista_senhas->papel);
            lista_senhas->next=NULL;
            //printf("Login: %s\n",lista_senhas->email);
            //printf("Papel: %s\n",lista_senhas->papel);
            //printf("Senha: %s\n",lista_senhas->senha);
        }else{
            aux = lista_senhas;
            while (aux->next!=NULL){
                // printf("Login: %s\n",aux->email);
                // printf("Papel: %s\n",aux->papel);
                // printf("Senha: %s\n",aux->senha);
                aux=aux->next;
            }
            aux->next=(senhassalvas *)malloc(sizeof(senhassalvas));
            aux=aux->next;
            fscanf(senhasBC, "%s\n", aux->email);
            fscanf(senhasBC, "%s\n", aux->senha);
            fscanf(senhasBC, "%s\n", aux->papel);
            aux->next=NULL;
        }
    }
    fclose(senhasBC);
    aux=lista_senhas;
    while (strcmp(conta,aux->email)!=0){
        //printf("passando a lista das senhas...\n");
        if (aux->next==NULL){
            break;
        }
        aux=aux->next;
    }
    if (aux==NULL){
        printf("Login nao existe!\n");
    }else{
        if (strcmp(senha,aux->senha)==0){
            printf("Login efetuado, carregando dados...\n"); //aux -> senha/email/papel
            if (strcmp(aux->papel,"residente")==0){
                lg_residente(aux->email, alunos_cadastrados);
            }else if (strcmp(aux->papel,"preceptor")==0){
                 lg_medico(aux->email,alunos_cadastrados,medicos_cadastrados);
            }else if (strcmp(aux->papel,"lg_adm")==0){
                lg_adm(aux->email,alunos_cadastrados,medicos_cadastrados,adms_cadastrados);
        }else {
            printf("Senha Incorreta!\n");
        }
    }
    }
    return 0;
}

