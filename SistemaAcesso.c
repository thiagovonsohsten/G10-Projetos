#include <stdio.h>      //biblioteca padrão
#include <stdlib.h>     //Fornece funções como alocação de memória dinâmica, conversão de strings, geração de números aleatórios, entre outras
#include <string.h>     //Fornece funções para manipulação de strings, como copiar, concatenar, comparar e buscar.
#include <time.h>       //Biblioteca do C que contém funções para manipulação de tempo e data, como a função time(), que retorna o número de segundos desde a "época" (1 de janeiro de 1970).
#include "bibliotecaFready.h"

//vai pegar o "lista_aluno.txt" e o "banco_de_dados.txt" para o usuário navegar no APP

int main (){
    char email,papel;
    //ARBIR ARQUIVO PARA SIMULAR O BANCO DE DADOS
    scanf("%d",&email);
    scanf("%d",&papel);
    if (strcmp(papel,"lg_residente")==1){
        lg_residente(email, papel);
    }else if (strcmp(papel,"preceptor")==1){
        lg_medico(email, papel);
    }else if (strcmp(papel,"lg_adm")==1){
        lg_adm(email, papel);
    }else{
        printf("Nível ou código Incorretos!");
    }
    return 0;
}

