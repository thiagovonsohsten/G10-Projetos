#include <stdio.h>      //biblioteca padrão
#include <stdlib.h>     //Fornece funções como alocação de memória dinâmica, conversão de strings, geração de números aleatórios, entre outras
#include <string.h>     //Fornece funções para manipulação de strings, como copiar, concatenar, comparar e buscar.
#include <time.h>       //Biblioteca do C que contém funções para manipulação de tempo e data, como a função time(), que retorna o número de segundos desde a "época" (1 de janeiro de 1970).
#include "bibliotecaFready.h"

//O código ártefato é responsável por receber do arduino as presenças dos preceptores e enviar para o SistemaPrincipal
//Recebe "artefato.txt" e envia "ata.txt"

int main () {
    presentes* head=NULL;
    presentes* lista=NULL;
    FILE* artefato;
    artefato = fopen("artefato.txt", "r");
    if (artefato == NULL) {
        printf("Arquivo Nulo!");
        fclose(artefato);
    } else {
            //printf("Entrou no else\n");
        while (!feof(artefato)) {
            //printf("Entrou no while\n");
            if (head == NULL) {
            //printf("Entrou no if\n");
                head = (presentes*)malloc(sizeof(presentes));
                fscanf(artefato, "%s\n", head->email);
                lista=head;
                head->next=NULL;
                //printf(head->email);
            } else {
                lista=head;
                while (lista->next != NULL) {
                    lista=lista->next;
                }
                lista->next = (presentes*)malloc(sizeof(presentes));
                lista = lista->next;
                fscanf(artefato, "%s\n", lista->email);
                //printf(lista->email);
                lista->next=NULL;
            }
            fscanf(artefato, "%ld\n", &(lista->tempo));
            //printf("%ld",lista->tempo);
        }
        fclose(artefato);
    }
    //printf("saiu do else\n");
    // lista=head;
    // while (lista->next != NULL) {
    //     printf("%s\n",lista->email);
    //     printf("%ld\n",lista->tempo);
    //     lista = lista->next;
    //     printf("Printando muito loko!\n");
    // }
    // printf("Saiu do print loko\n");
    FILE* ata;
    if (head == NULL) {
        printf("Lista vazia!");
    } else {
        ata = fopen("ata.txt", "w");
        while (head!=NULL){
            lista = head;
            fprintf(ata, "%s\n", lista->email);
            fprintf(ata, "%ld\n", lista->tempo);
            head=head->next;
            free(lista);
        }
        fclose(ata);
    }
    return 0;
}