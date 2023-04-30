//Artefato que irá se comunicar com a central/app/sistema/aplicação
    //Falta definir alguns detalhes como hardware e passagem de informações
#include <stdio.h>      //biblioteca padrão
#include <stdlib.h>     //Fornece funções como alocação de memória dinâmica, conversão de strings, geração de números aleatórios, entre outras
#include <string.h>     //Fornece funções para manipulação de strings, como copiar, concatenar, comparar e buscar.
#include <time.h>       //Biblioteca do C que contém funções para manipulação de tempo e data, como a função time(), que retorna o número de segundos desde a "época" (1 de janeiro de 1970).
#include <winsock2.h>   //Biblioteca fornece as definições necessárias para a criação, conexão e comunicação de sockets em rede utilizando o protocolo TCP/IP. Ela é essencial para o código já que é responsável pela comunicação entre o artefato e o servidor na aplicação!
#include <windows.h>    //Não precisaria colocar essa biblioteca, contudo é bom destacar que estarei utilizando o sistema operacional do windowns.
//#include <wiringPi.h>   Biblioteca que contém funções para conversão de endereços IP entre formatos numéricos e de strings. Utilizado para o Hardware que consideramos, o Raspberry Pi. Pode ser alterado posteriormente.

#define SERVER_IP "192.168.0.100" // IP do servidor/app
#define SERVER_PORT 8080 // Porta do servidor/app

#define PINO_SENSOR_USURARIO 0 // Pino do sensor de identificação do usuário
#define CANCELAR_PINO 1 // Pino do botão de cancelamento

#define HIGH 1  //A biblioteca que daria esses valores seria o wiringPi, como estamos assumindo um hardware, pode ser alterado ou removido.
#define LOW 0   //O mesmo do HIGH

struct preceptor {
    int id;
    time_t tempo;
    struct preceptor *next;
};

int main () {
    // Configurando os pinos de entrada, utilizando o GPIO para se comunicar com sensores ou outros dispositivos.
    HANDLE dispositivoGPIO = CreateFile("Endereço do GPIO", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    // parâmetros da função createFile:(endereço, flags que indicam as permissões que serão concedidas ao arquivo. Neste caso, GENERIC_READ permite leitura e GENERIC_WRITE permite escrita. Para o caso específico do acesso aos pinos GPIO, é preciso conceder permissão de leitura e escrita.,parâmetro de segurança que deve ser definido como zero., parâmetro que especifica o modo como o arquivo deve ser aberto. Quando se passa NULL, indica-se que o arquivo deve ser aberto com as permissões especificadas nos parâmetros anteriores.,  parâmetro que especifica como o arquivo deve ser aberto. Neste caso, como o arquivo já existe, ele deve ser aberto no modo existente., parâmetro que especifica os atributos do arquivo. Quando se passa FILE_ATTRIBUTE_NORMAL, indica-se que o arquivo não possui nenhum atributo especial.,  parâmetro de segurança que deve ser definido como zero.)
    if (dispositivoGPIO == INVALID_HANDLE_VALUE) {
        printf("Erro ao acessar GPIO.\n");
        return 1;
    }
    struct preceptor *head;
       // Loop principal infinito
    while (1) {
        // Identificação do usuário
        struct preceptor enviar;
        enviar.id = 0;
        while (digitalRead(PINO_SENSOR_USURARIO) == LOW) { //enquanto o hardware não identificar alguma pessoa irá no loop infinito.
            delay(100);
        }
        //  Quando sai do loop significa que o hardware identificou alguem se aproximando
        //  Então lê o valor do sensor e converte para um ID de usuário
        //  Claro que estamos considerando que todo o processo de identificação será realizado pelo hardware que poderá utilizar os dados do nosso servidor/app/aplicação
        enviar.id = analogRead(PINO_SENSOR_USURARIO); // Muito cuidado nessa conversão, dependendo do hardware que escolhermos, poderá haver erros de tamanho dos bytes por conta do sensor.

        // Tempo de espera para o preceptor realizar o cancelamento
        int tempo_de_cancelamento = 0; //Uma variável apenas parar marcar o tempo que as pessoas cancelam, caso seja próximo dos 5s, podemos aumentar o tempo para não ficar muito corrido para o usuário.
        while (digitalRead(CANCELAR_PINO) == HIGH && tempo_de_cancelamento < 5000) {
            delay(100);
            tempo_de_cancelamento += 100;
        }

        //  Nesta etapa do nosso artefato, nós já recebemos o id do usuário e sua confirmação, 
        //  precisamos criar nosso pacote de dados para ser enviada para a fila
        enviar.tempo=time(NULL);
        //o artefato irá enviar os dados, e o sistema irá identificar se é o tempo inicial ou final apenas verificando pela ordem de envio.

        // Envia as informações para o servidor/app
            // if não enviar
                //salva
                    //já existe?
                        //Não -> Cria uma lista nova criando o HEAD.
                        //Sim -> Salva na última posição da lista.
            // if enviar
                //HEAD existe?
                    //Sim -> manda todos e zera a lista deixando o head apontando pra NULL.
                    //Não -> Envia.
                
    }
    CloseHandle(dispositivoGPIO); //Fechando a lista e liberando espaço de memória (os professores de PIF agradecem!)
    return 0;
}
