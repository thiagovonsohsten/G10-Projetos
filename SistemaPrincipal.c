//Central/APP/Sistema/Aplicação que irá receber a mensagem do artefato e irá gerenciar os dados, lembrando que serão acessados pelos residentes, preceptores e gestão do hospital.
    //Recebe os dados e altera quando reccbe a segunda informação de data
#include <stdio.h>      //biblioteca padrão
#include <stdlib.h>     //Fornece funções como alocação de memória dinâmica, conversão de strings, geração de números aleatórios, entre outras
#include <string.h>     //Fornece funções para manipulação de strings, como copiar, concatenar, comparar e buscar.
#include <time.h>       //Biblioteca do C que contém funções para manipulação de tempo e data, como a função time(), que retorna o número de segundos desde a "época" (1 de janeiro de 1970).
#include <windows.h>    //Não precisaria colocar essa biblioteca, contudo é bom destacar que estarei utilizando o sistema operacional do windowns.

//struct da mensagem
struct mensagem {
    int id;
    time_t tempo;
};
//struct da lista que irá rodar no sistema
struct ata {
    int id;
    time_t tempo;
    struct ata *next;
};

struct ata *Head=NULL;

int main () {
    struct mensagem Request;
    while (1){
    //Recebe os dados do Artefato (para efeito da lógica, iremos considerar uma variávelde struct mensagem)
    Request.id = 20485;
    Request.tempo=time(NULL); //Estamos considerando apenas a data de hoje, sem maiores objetivos. Lembrando que o time_t retoran o valor em segundos, e teremos que realizar a função localtime() para converter esses segundos para converter a data, pois a bilbiotca time referencia os segundos a partir de uma data que acredito ser 1/1/70
        if (Request.id!=0){//Ciclo Principal do programa
            if (Head==NULL){ //criando para o Head vazio
                Head->id=Request.id;
                Head->tempo=Request.tempo;
                Head->next=(struct ata *)malloc(sizeof(struct ata));
                Request.id=0; //Condição para sair do if principal
            }else{//Vamos primeiro Verificar se o id existe na lista, se não existe crio no último.
                struct ata *contador=Head,*anterior=NULL;
                if (contador->id!=Request.id){ //condição para passar o primeiro elemento d alista sem bugar.
                    while (contador->id!=Request.id && contador->next!=NULL){ //Aqui encontra o id do usuário ou chega no último elemento da lista
                        anterior=contador;
                        contador=contador->next;
                    }
                }
                if (contador->next==NULL && contador->id!=Request.id){ //Após o while, aqui verificamos se ele está no último elemento, e acrescentamos no fim.
                    contador->next=(struct ata *)malloc(sizeof(struct ata));
                    contador =contador->next;
                    contador->id=Request.id;
                    contador->tempo=Request.tempo;
                    contador->next=NULL;
                    Request.id=0; //Condição para sair do if principal
                }else{ //Aqui identificamos que ele está na lista, pois não é o último. Queremos adicionar ele no banco de dados e eliminar
                    //*****salvar no arquivo "contador->id/contador->tempo/request.tempo"
                    if(anterior==NULL){ //Se só houver um item na lista, ele irá limpar a lista
                        free(contador);
                    }else{ //Se não, apenas trocará a sequência e limpara o valor
                        anterior->next=contador->next;
                        free(contador);
                        Request.id=0; //Condição para sair do if principal
                    }
                }
            }
        }
    }
    return 0;
}
