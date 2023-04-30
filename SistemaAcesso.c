//Sitema para acessar o banco de dados.
#include <stdio.h>      //biblioteca padrão
#include <stdlib.h>     //Fornece funções como alocação de memória dinâmica, conversão de strings, geração de números aleatórios, entre outras
#include <string.h>     //Fornece funções para manipulação de strings, como copiar, concatenar, comparar e buscar.
#include <time.h>       //Biblioteca do C que contém funções para manipulação de tempo e data, como a função time(), que retorna o número de segundos desde a "época" (1 de janeiro de 1970).
#include <windows.h>    //Não precisaria colocar essa biblioteca, contudo é bom destacar que estarei utilizando o sistema operacional do windowns.

struct dados {
    int id; //id do usuário Médico ou residente
    int id_preceptor; // id do preceptor que está supervisionando o residente
    char nome [101];
    char cpf [12];
    //Acrescentar possível imagem para o sensor
    struct historico *Head;
};

struct historico {
    time_t entrada;
    time_t saida;
    struct historico *next;
};

struct medico {
    struct dados alunos;
    struct medico *next;
};

int residente(int id, int nivel);
int medico(int id, int nivel);
int gestor(int id, int nivel);
struct dados encontra_aluno_por_id(int id_aluno);

int main (){
    int id,nivel;
    scanf("Insira seu Código: %d",&id);
    scanf("Aluno(1), Professor (2) ou Gestor (3)? %d",&nivel);
    if (nivel==1){
        residente(id, nivel);
    }else if (nivel ==2){
        medico(id, nivel);
    }else if (nivel == 3){
        gestor(id, nivel);
    }else{
        printf("Nível ou código Incorretos!");
    }
    return 0;
}

int residente (id, nivel) {
    //busca nos arquivos o id e nível
    struct dados Residente;
    struct historico *ata_de_presenca;
        //A título de desenvolvimento irei acrescentar os dados manualmente, mas deverá ser recolhido pelo banco de dados em uma busca pelo id e nivel
    strcpy(Residente.cpf,"000.000.000-02");
    Residente.id=21452;
    strcpy(Residente.nome,"Jacinto Paulo Muse");
    Residente.id_preceptor = 698;
    Residente.Head=ata_de_presenca;
    //Menu com:
        //Dados do Residente
        //Histórico de presença acessado pela lista de struct
        // Menu do residente
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
                // Exibe os dados do residente
                printf("\n--- Dados do Residente ---\n");
                printf("Nome: %s\n", Residente.nome);
                printf("CPF: %s\n", Residente.cpf);
                printf("ID: %d\n", Residente.id);
                printf("ID do Preceptor: %d\n", Residente.id_preceptor);
                break;
            case 2:
                // Exibe o histórico de presença do residente
                printf("\n--- Histórico de Presença ---\n");
                struct historico* temporario = Residente.Head;
                while (temporario != NULL) {
                    printf("Entrada: %s", asctime(localtime(&(temporario->entrada))));
                    printf("Saída: %s", asctime(localtime(&(temporario->saida))));
                    double diferenca = difftime(temporario->saida, temporario->entrada);
                    printf("Tempo de Trabalho: %lf segundos\n", diferenca);
                    printf("\n");
                    temporario = temporario->next;
                }
                break;
            case 0:
                // Sair do menu
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida, tente novamente.\n");
        }
    }
    return 0;
}

int medico (id, nivel) {
    // Busca nos arquivos o id e nível do médico
    struct medico *alunos = NULL;
    // Busca no BD os alunos que estão sobre sua supervisão
    
    int opcao; //Entra no Menu do Médico
    do {
        printf("\nMenu do Médico\n");
        printf("1. Visualizar lista de alunos sob sua supervisão\n");
        printf("2. Visualizar frequência de um aluno\n");
        printf("0. Sair\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: //Nesse caso, como busquei nos dados a lista de alunos que são supervisionados pelo médico,é apenas processo de impressão
                printf("\nLista de alunos sob sua supervisão:\n");
                struct medico *aluno_atual = alunos;
                while (aluno_atual != NULL) {  
                    printf("ID: %d\nNome: %s\n", aluno_atual->alunos.id, aluno_atual->alunos.nome);
                    aluno_atual = aluno_atual->next;
                }
                break;
            case 2: //Escolhe o ID do aluno através da função 'encontra_aluno_por_id() e retorna um struct dados com a estrutura do aluno.
                printf("\nDigite o ID do aluno para visualizar a frequência: ");
                int id_aluno;
                scanf("%d", &id_aluno);
                struct dados aluno_frequencia = encontra_aluno_por_id(id_aluno);
                struct dados *ponteiro=&aluno_frequencia;
                if (ponteiro == NULL) { //Condição para não encontrar o aluno
                    printf("Aluno não encontrado!\n");
                    break;
                }
                printf("\nFrequência de %s:\n", ponteiro->nome); //Mostra o nome do aluno e abaixo segue o histórico pela função while.
                struct historico *presenca_atual = ponteiro->Head;// No While ele irá rodar todas as presenças que o aluno tem.
                while (presenca_atual != NULL) {
                    printf("Entrada: %sSaida: %sDuração: %ld segundos\n", ctime(&(presenca_atual->entrada)), ctime(&(presenca_atual->saida)), presenca_atual->saida - presenca_atual->entrada);
                    presenca_atual = presenca_atual->next;
                }
                break;
            case 0:
                printf("\nSaindo do Menu do Médico.\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    // Libera a memória alocada
    liberar_lista_alunos(alunos);

    return 0;
}

int gestor (id, nivel) {
    // Importar todos os dados do banco de dados para conseguir trabalhar neles
    int opcao;
    while (1) {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Visualizar lista de residentes e seus preceptores\n");
        printf("2 - Visualizar faltas dos residentes\n");
        printf("3 - Visualizar hierarquias e dados estatisticos\n");
        printf("4 - Visualizar hierarquias e dados estatisticos\n");
        printf("5 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Lista de residentes e seus preceptores:\n");
                // Visualizar lista de residentes e seus preceptores através de uma varredura de todos os dados do arquivo que ainda estão ativos.
                break;
            case 2:
                printf("Faltas dos residentes:\n");
                // Visualizar faltas dos residentes, buscar e exibir as faltas dos residentes
                break;
            case 3:
                printf("Hierarquias e dados estatisticos:\n");
                // Visualizar hierarquias e dados estatisticos, busca e exibi as hierarquias e dados estatisticos
                break;
            case 4:
                printf("Cancele ou retome a inscrição do residente ou aluno\n");
                //Nessa seção será possível vizualizar os status de todas as pessoas inscritas no programa de residência do Hospital das Clínicas, podendo ser encerrada ou acrescentada.
                //Após realizar as alterações, iremos atualizar o banco de dados.
                break;
            case 5:
                // Sair
                printf("Encerrando sessao do gestor...\n");
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}

struct dados encontra_aluno_por_id(int id_aluno){
    //aqui o sistema irá realizar uma busca e retornar os dados do aluno
    struct dados aluno;
    //iguala os dados a struct aluno e a retorna.
    return (aluno);
}
