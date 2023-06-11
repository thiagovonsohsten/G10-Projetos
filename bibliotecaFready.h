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

    int paginaPrincipal = 1;
    char senha_antiga[100],senha_nova[100],senha_Verificador[100];
    int opcao,menu_navbar,sair_app;
    while (paginaPrincipal !=0){
        printf("-- Pagina Principal --");
        printf("\n\n");
        //Printar tempo corrido @@G10@@
        printf("Tempo decorrido:\n");
        printf("\n\n");
        printf("Acessar NavBar - (1 -Pagina Principal/2 - Calendario/3 - Menu)");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                break;
            case 2:
                // Exibe o histórico de presença do lg_residente
                printf("Historico de presencas:\n");
                int n=1;
                while(Residente->aluno->lista_de_Presenca->next!=NULL){
                    printf("Presenca: %d\n\tEntrada: %ld\n\tSaida: %ld\n", n, Residente->aluno->lista_de_Presenca->entrada, Residente->aluno->lista_de_Presenca->saida);
                    if (Residente->aluno->lista_de_Presenca->next!=NULL){ //problema por criar a lista antes de verificar se tem próximo
                    Residente->aluno->lista_de_Presenca=Residente->aluno->lista_de_Presenca->next;
                    }else {
                        Residente->aluno->lista_de_Presenca->next=NULL;
                    }
                    n++;
                }
                printf("Aperter qualquer tecla para ir ao menu!");
                getchar();
                getchar();
                break;
            case 3:
                // Exibe os residente do lg_residente
                printf("\n--- MENU ---\n\n");
                printf("\n--- Dados do Residente ---\n");
                printf("Logado: %s\n", Residente->aluno->nome);
                printf("\nO que deseja fazer?\n(1)-Vizualizar Dados \t (2)-Trocar Senha \t (3)Sair\n");
                scanf("%d", &menu_navbar);
                if (menu_navbar==1){
                    printf("\n--- Vizualizar Dados ---\n");   
                    printf("Nome: %s\n", Residente->aluno->nome);
                    printf("CPF: %s\n", Residente->aluno->cpf);
                    printf("E-mail: %s\n", Residente->aluno->email);
                    printf("E-mail do Preceptor: %s\n", Residente->aluno->email_preceptor);
                    printf("Especializacao: %s\n", Residente->aluno->especializacao);
                    printf("Aperter qualquer tecla para ir ao menu!");
                    getchar();
                    getchar();
                }else if (menu_navbar==2) {
                    printf("\n--- Trocar Senha ---\n");  
                    printf("Digite a Senha Antiga:");
                    fgets(senha_antiga,sizeof(senha_antiga),stdin); //Nao espera! ERRO!
                    //condiçao se é verdadeira @@G10@@
                    printf("Digite a Senha Nova:");
                    fgets(senha_nova,sizeof(senha_nova),stdin);
                    printf("Repita a senha Nova:");
                    fgets(senha_Verificador,sizeof(senha_Verificador),stdin);
                    //condição se as senhas novas batem
                    if (strcmp(senha_nova,senha_Verificador)==0){
                        //trocar senha no senhasBC.txt @@G10@@
                        printf("Senha Trocada com Sucesso!\n");
                        printf("Aperter qualquer tecla para ir ao menu!");
                        getchar();
                        getchar();
                    }
                }else {
                    printf("Fechando App...\n");
                    printf("Deseja realmente Sair?\n(1)-Sim\t(2)-Não\n");
                    scanf("%d", &sair_app);
                    if (sair_app==1){
                        paginaPrincipal=0;
                    }
                    //vai pro menu
                }
                break;
            default:
                printf("\nOpcao invalida, tente novamente.\n");
        }
    }
}

void lg_medico(char email[20], lista_aluno* lista_de_alunos,lista_medico* lista_de_medicos){
    //busca nos arquivos o email e nível
    lista_medico* Medico=lista_de_medicos; //Lista de médicos cadastrados
    lista_aluno* lista_alunos_do_preceptor=NULL; //Lista que salvará todos os alunos ligados a ele
    while (strcmp(Medico->preceptor->email,email)!=0 || Medico==NULL){
        Medico=Medico->next;
    }
    if (Medico==NULL){
        printf("Erro ao localizar usuario!\n");
        return;
    }

    int paginaprincipal=1;
    int menu_navbar;
    int sair_app;
    char senha_antiga[100],senha_nova[100],senha_verificador[100];
    while (paginaprincipal!=0){
        int subpagina=0;
        while (subpagina!=1 && subpagina!=2){
        printf("--- Pagina Principal ---");
        printf("\n\nO que deseja fazer?\n(1)-Pesquisar Aluno\t(2)-Navbar\n");
        scanf("%d",&subpagina);
        }
        if (subpagina==1){
            lista_aluno* auxPreceptor=lista_alunos_do_preceptor;
            lista_aluno* aux=lista_de_alunos;
            while (aux!=NULL){
                if (strcmp(aux->aluno->email_preceptor,Medico->preceptor->email)==0){
                    if (auxPreceptor==NULL){
                        auxPreceptor=(lista_aluno *)malloc(sizeof(lista_aluno));
                        auxPreceptor->next=NULL;
                        auxPreceptor->aluno=auxPreceptor->aluno;
                    }else{
                        while(auxPreceptor->next!=NULL){
                            auxPreceptor=auxPreceptor->next;
                        }
                        auxPreceptor=(lista_aluno *)malloc(sizeof(lista_aluno));
                        auxPreceptor->next=NULL;
                        auxPreceptor->aluno=auxPreceptor->aluno;
                    }
                }
                aux=aux->next;
            }
            //printar todos da lista - Falta Implementar a pesquisa - @@G10@@
            auxPreceptor=lista_alunos_do_preceptor;
            while(auxPreceptor!=NULL){
                printf("Aluno: %s\n",auxPreceptor->aluno->nome);
                auxPreceptor=auxPreceptor->next;
            }
            printf("Aperter qualquer tecla para ir ao menu!");
                getchar();
                getchar();
        }else if (subpagina==2){
            int navbar=0;
            while (navbar!=1 && navbar!=2){
            printf("--- NavBar ---");
            printf("\n\nO que deseja fazer?\n(1)-Menu\t(2)-Página principal\n");
            scanf("%d",&navbar);
            }
            if (navbar==1){
                // Exibe os residente do lg_residente
                printf("\n--- Pagina Principal ---\n\n");
                printf("\n--- Dados do Preceptor ---\n");
                printf("Logado: %s\n", Medico->preceptor->nome);
                printf("\nO que deseja fazer?\n(1)-Vizualizar Dados \t (2)-Trocar Senha \t (3)Sair\n");
                scanf("%d", &menu_navbar);
                if (menu_navbar==1){
                    printf("\n--- Vizualizar Dados ---\n");   
                    printf("Nome: %s\n", Medico->preceptor->nome);
                    printf("CPF: %s\n", Medico->preceptor->cpf);
                    printf("E-mail: %s\n", Medico->preceptor->email);
                    printf("E-mail do Preceptor: %s\n", Medico->preceptor->CRM);
                    printf("Especializacao: %s\n", Medico->preceptor->especializacao);
                    printf("Aperter qualquer tecla para ir ao menu!");
                    getchar();
                    getchar();
                }else if (menu_navbar==2) {
                    printf("\n--- Trocar Senha ---\n");  
                    printf("Digite a Senha Antiga:");
                    fgets(senha_antiga,sizeof(senha_antiga),stdin); //Nao espera! ERRO!
                    //condiçao se é verdadeira @@G10@@
                    printf("Digite a Senha Nova:");
                    fgets(senha_nova,sizeof(senha_nova),stdin);
                    printf("Repita a senha Nova:");
                    fgets(senha_verificador,sizeof(senha_verificador),stdin);
                    //condição se as senhas novas batem
                    if (strcmp(senha_nova,senha_verificador)==0){
                        //trocar senha no senhasBC.txt @@G10@@
                        printf("Senha Trocada com Sucesso!\n");
                        printf("Aperter qualquer tecla para ir ao menu!");
                        getchar();
                        getchar();
                    }
                }else {
                    printf("Fechando App...\n");
                    printf("Deseja realmente Sair?\n(1)-Sim\t(2)-Não\n");
                    scanf("%d", &sair_app);
                    if (sair_app==1){
                        paginaprincipal=0;
                    }
                    //fecha tudo
                }
            }
        }
    }

}

void lg_adm(char email, char papel);

#endif