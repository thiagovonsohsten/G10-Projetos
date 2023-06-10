#include <stdio.h>      //biblioteca padrão
#include <stdlib.h>     //Fornece funções como alocação de memória dinâmica, conversão de strings, geração de números aleatórios, entre outras
#include <string.h>     //Fornece funções para manipulação de strings, como copiar, concatenar, comparar e buscar.
#include <time.h>       //Biblioteca do C que contém funções para manipulação de tempo e data, como a função time(), que retorna o número de segundos desde a "época" (1 de janeiro de 1970).
#include "bibliotecaFready.h"

//Responsável por contar as horas de cada estudando
//recebe o arquivo "ata.txt" e envia "presenca_aluno.txt"

int main () {
    presenca *Head=NULL;
    FILE* ata,* presenca_aluno;
    ata = fopen("ata.txt", "r");
    while (!feof(ata)){
        if (Head==NULL){ //criando para o Head vazio
            Head=(presenca *)malloc(sizeof(presenca));
            fscanf(ata, "%s\n", Head->email);
            fscanf(ata, "%ld\n", &(Head->tempo));
            Head->next=NULL;
        }else{//Vamos primeiro Verificar se o email existe na lista, se não existe crio no último.
            presenca *verificador=NULL,*anterior=NULL, *cabeca=Head;
            fscanf(ata, "%s\n", verificador->email);
            fscanf(ata, "%ld\n", &(verificador->tempo));
            if (strcmp(verificador->email,cabeca->email)!=0){ //condição para passar o primeiro elemento d alista sem bugar.
                while (strcmp(verificador->email,cabeca->email)!=0 && cabeca->next!=NULL){ //Aqui encontra o email do usuário ou chega no último elemento da lista
                    anterior=cabeca;
                    cabeca=cabeca->next;
                }
            }
            if (cabeca->next==NULL && strcmp(verificador->email,cabeca->email)!=0){ //Após o while, aqui verificamos se ele está no último elemento, e acrescentamos no fim.
                cabeca->next=(presenca *)malloc(sizeof(presenca));
                cabeca=cabeca->next;
                strcpy(cabeca->email,verificador->email);
                cabeca->tempo=verificador->tempo;
                cabeca->next=NULL;
            }else{ //Aqui identificamos que ele está na lista, pois não é o último. Queremos adicionar ele no banco de dados e eliminá-lo
                presenca_aluno = fopen("presenca.txt", "a");
                fprintf(presenca_aluno, "%s\n", cabeca->email);
                fprintf(presenca_aluno, "%ld\n", cabeca->tempo);
                fprintf(presenca_aluno, "%ld\n", verificador->tempo);
                fclose(presenca_aluno);
                if(anterior==NULL){ //Se só houver um item na lista, ele irá limpar a lista
                    free(verificador);
                }else{ //Se não, apenas trocará a sequência e limpara o valor
                    free(verificador);
                    verificador=cabeca;
                    anterior->next=cabeca->next;
                    free(verificador);
                }
            }
        }
    }
    fclose(ata);
    return 0;
}
