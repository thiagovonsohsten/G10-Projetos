#include <stdio.h>      //biblioteca padrão
#include <stdlib.h>     //Fornece funções como alocação de memória dinâmica, conversão de strings, geração de números aleatórios, entre outras
#include <string.h>     //Fornece funções para manipulação de strings, como copiar, concatenar, comparar e buscar.
#include <time.h>       //Biblioteca do C que contém funções para manipulação de tempo e data, como a função time(), que retorna o número de segundos desde a "época" (1 de janeiro de 1970).
#include "bibliotecaFready.h"

//Responsável por contar as horas de cada estudando
//recebe o arquivo "ata.txt", salva um arquivo "presentes.txt" para todos os presentes e gera um arquivo "presenca.txt" para dar baixa nas presencas.

void enviarpresentes(presentes* cabeca);
void baixapresentes(char email[20], time_t entrada,time_t saida);

int main () {
    presentes *Head=NULL;
    FILE* ata;
    ata = fopen("ata.txt", "r");
    while (!feof(ata)){
        if (Head==NULL){ //criando para o Head vazio
            Head=(presentes *)malloc(sizeof(presentes));
            fscanf(ata, "%s\n", Head->email);
            fscanf(ata, "%ld\n", &(Head->tempo));
            Head->next=NULL;
        }else{//Vamos primeiro Verificar se o email existe na lista, se não existe crio no último.
            presentes *verificador=(presentes *)malloc(sizeof(presentes));
            verificador->next=NULL;
            presentes *anterior=NULL;
            presentes *cabeca=Head;
            fscanf(ata, "%s\n", verificador->email);
            fscanf(ata, "%ld\n", &(verificador->tempo));
            //condição para passar o primeiro elemento d alista sem bugar.
            if ( strcmp(verificador->email,cabeca->email) != 0){ 
                while ( strcmp(verificador->email,cabeca->email) !=0 && cabeca->next!=NULL){ //Aqui encontra o email do usuário ou chega no último elemento da lista
                    anterior=cabeca;
                    cabeca=cabeca->next;
                }
            }
            //condição para econtrar dentro da lista de presentes
            if (cabeca->next==NULL && strcmp(verificador->email,cabeca->email)!=0){ //Após o while, aqui verificamos se ele está no último elemento, e acrescentamos no fim.
                cabeca->next=(presentes *)malloc(sizeof(presentes));
                cabeca=cabeca->next;
                strcpy(cabeca->email,verificador->email);
                cabeca->tempo=verificador->tempo;
                cabeca->next=NULL;
            }else{ //Aqui identificamos que ele está na lista, pois não é o último. Queremos adicionar ele no banco de dados e eliminá-lo
                if(anterior==NULL && cabeca->next==NULL){ //Se só houver um item na lista, ele irá limpar a lista
                    baixapresentes(verificador->email,cabeca->tempo,verificador->tempo);
                    free(verificador);
                }else if (anterior==NULL && cabeca->next!=NULL){
                    baixapresentes(verificador->email,cabeca->tempo,verificador->tempo);
                    free(verificador);
                    Head=cabeca->next;
                    free(cabeca);

                }else{ //Se não, apenas trocará a sequência e limpara o valor. Os valores de seus horários serão exportados em txt.
                    baixapresentes(verificador->email,cabeca->tempo,verificador->tempo);
                    free(verificador);
                        verificador=cabeca;
                        anterior->next=cabeca->next;
                        free(verificador);
                }
            }  
        }
        enviarpresentes(Head);
    }
    fclose(ata);
    return 0;
}

void enviarpresentes(presentes* cabeca){
    presentes* aux=cabeca;
    FILE* presente;
    presente = fopen("presentes.txt","w");
    while(aux!=NULL){
        fprintf(presente, "%s\n", aux->email);
        fprintf(presente, "%ld\n", aux->tempo);
        aux=aux->next;
    }
    fclose(presente);
}

void baixapresentes(char email[20], time_t entrada,time_t saida){
    FILE* presentes; //lista que define a conclusão do turno de trabalho
    presentes=fopen("presentes.txt","w");
    fprintf(presentes, "%s\n", email);
    fprintf(presentes, "%ld\n", entrada);
    fclose(presentes);
}