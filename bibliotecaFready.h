#ifndef __Fready__
#define __Fready__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Lista de presença
typedef struct presentes{
    char email[20];
    time_t tempo;
    struct presentes *next;
}presentes;

typedef struct precensa{
    char email[20];
    time_t entrada;
    time_t saida;
    struct precensa *next;
}precensa;

//tipo de senha
typedef struct senhassalvas {
    char email[100];
    char senha[100];
    char papel [10];//residente,preceptor,adm
    struct senhassalvas* next;
}senhassalvas;

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
    char papel[10];//residente,preceptor,adm
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

void trocar_senha(char email[20]){ //utilização de recursão para o loop
    //email será usado para buscar a senha do preceptor.
    char senha_antiga[100],senha_nova[100],senha_Verificador[100];
    printf("\n--- Trocar Senha ---\n");  
    printf("Digite a Senha Antiga:");
    getchar();
    fgets(senha_antiga,sizeof(senha_antiga),stdin);
    printf("Digite a Senha Nova:");
    getchar();
    fgets(senha_nova,sizeof(senha_nova),stdin);
    printf("Repita a senha Nova:");
    getchar();
    fgets(senha_Verificador,sizeof(senha_Verificador),stdin);
    if (strcmp(senha_nova,senha_Verificador)==0){
        //IMPLEMENTAR: trocar senha no senhasBC.txt @@G10@@
        printf("Senha Trocada com Sucesso!\n");
        printf("Aperter qualquer tecla para ir a Pagina Principal!");
        getchar();
        getchar();
    }else {
        printf("Senhas Incorretas!\n");
        trocar_senha(email);
    }
}

int verificadordesenhas(char login[20],char senha [20]){ //ele abre o arquivo "senhasBC.txt"
    senhassalvas* lista_senhas = NULL;
    senhassalvas* aux = NULL;
    //importar as senhas para uma lista
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
    //finalizacao de importacao de senhas
    aux=lista_senhas;
    while (strcmp(login,aux->email)!=0){
        //printf("passando a lista das senhas...\n");
        if (aux->next==NULL){
            return 4; //Login errada
        }
        aux=aux->next;
    }
    if (strcmp(aux->senha,senha)==0){
        if (strcmp(aux->papel,"residente")==0){
            return 1;
        }else if (strcmp(aux->papel,"preceptor")==0){
            return 2;
        }else {
            return 3;
        }
    }else {
        return 0; //Senha errado
    }
}

void lg_residente (char email[20], lista_aluno* lista_de_alunos) {
    //busca nos arquivos o email e nível
    lista_aluno* Residente=lista_de_alunos;
    presentes* lista_presentes=(presentes *)malloc(sizeof(presentes));
    lista_presentes->next=NULL;
    while (strcmp(Residente->aluno->email,email)!=0 || Residente==NULL){
        Residente=Residente->next;
    }
    if (Residente==NULL){
        printf("Erro ao localizar usuario!\n");
        return;
    }

    int paginaPrincipal = 1;
    int opcao,menu_navbar,sair_app;
    while (paginaPrincipal !=0){
        printf("-- Pagina Principal --");
        printf("\n\n");
        presentes* aux=lista_presentes;
        FILE* tempo;
        tempo=fopen("presentes.txt","r");
        while (!feof(tempo)){
            fscanf(tempo,"%s\n",aux->email);
            fscanf(tempo,"%ld\n",(&aux->tempo));
            if (!feof(tempo)){
                aux->next=(presentes *)malloc(sizeof(presentes));
                aux=aux->next;
                aux->next=NULL;
            }
        }
        fclose(tempo);
        //Printar tempo corrido @@G10@@
        aux=lista_presentes;
        while(strcmp(aux->email,email)!=0 || aux==NULL){
            aux=aux->next;
        }
        if(aux==NULL){
            printf("-- Você não esta presente :( --\n");
        }else {
            printf("--Voce entrou em: --\n");
            printf("--%ld       \n",aux->tempo); // depois converter em hora
        }
        printf("Para acessar a NavBar, digite: ( 1) -Pagina Principal/2) - Calendario/3) - Menu)");
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
                printf("Aperter qualquer tecla para ir a Pagina Principal!");
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
                    printf("Aperter qualquer tecla para ir a Pagina Principal!");
                    getchar();
                    getchar();
                }else if (menu_navbar==2) {
                    trocar_senha(email);
                }else {
                    printf("Fechando App...\n");
                    printf("Deseja realmente Sair?\n(1)-Sim\t(2)-Nao\n");
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
    printf("Bem Vindo Preceptor\n");
    lista_medico* Medico=lista_de_medicos; //Lista de médicos cadastrados
    lista_aluno* lista_alunos_do_preceptor=NULL; //Lista que salvará todos os alunos ligados a ele
    //encontrar o medico na lista
    while (strcmp(Medico->preceptor->email,email)!=0 || Medico==NULL){
        Medico=Medico->next;
    }
    if (Medico==NULL){
        printf("Erro ao localizar usuario!\n");
        return;
    }
    //Menu principal
    int paginaprincipal=1;
    int menu_navbar;
    int sair_app;
    while (paginaprincipal!=0){
        int subpagina=0;
        while (subpagina!=1 && subpagina!=2){
        printf("--- Pagina Principal ---");
        printf("\n\nO que deseja fazer?\n(1)-Pesquisar Aluno\t(2)-Navbar\n");
        scanf("%d",&subpagina);
        }
        if (subpagina==1){
            lista_aluno* auxPreceptor;
            lista_aluno* auxAlunos=lista_de_alunos;
            while (auxAlunos!=NULL){
                if (strcmp(auxAlunos->aluno->email_preceptor,Medico->preceptor->email)==0){
                    if (lista_alunos_do_preceptor==NULL){
                        lista_alunos_do_preceptor=(lista_aluno *)malloc(sizeof(lista_aluno));
                        auxPreceptor=lista_alunos_do_preceptor;
                        auxPreceptor->next=NULL;
                        auxPreceptor->aluno=auxAlunos->aluno;
                    }else{
                        auxPreceptor->next=(lista_aluno *)malloc(sizeof(lista_aluno));
                        auxPreceptor=auxPreceptor->next;
                        auxPreceptor->next=NULL;
                        auxPreceptor->aluno=auxAlunos->aluno;
                    }
                }
                auxAlunos=auxAlunos->next;
            }
            auxPreceptor=lista_alunos_do_preceptor;
            int n=1;
            while(auxPreceptor!=NULL){
                printf("%d Aluno: %s\n",n,auxPreceptor->aluno->nome);
                auxPreceptor=auxPreceptor->next;
                n++;
            }
            int alunoescolhido;
            printf("Qual aluno da lista voce deseja olhar?\n");
            scanf("%d",&alunoescolhido);
            int apoio=1;
            auxPreceptor=lista_alunos_do_preceptor;
            while (alunoescolhido>apoio && auxPreceptor!=NULL){
                auxPreceptor=auxPreceptor->next;
                apoio++;
            }
            printf("\n--- Vizualizacao dos Dados do aluno---\n");   
            printf("Nome: %s\n", auxPreceptor->aluno->nome);
            printf("CPF: %s\n", auxPreceptor->aluno->cpf);
            printf("E-mail: %s\n", auxPreceptor->aluno->email);
            //printf("E-mail do Preceptor: %s\n", auxPreceptor->aluno->email_preceptor);
            printf("Especializacao: %s\n", auxPreceptor->aluno->especializacao);
            printf("Aperter qualquer tecla para ir a Pagina Principal!");
                getchar();
                getchar();
        }else if (subpagina==2){
            int navbar=0;
            while (navbar!=1 && navbar!=2){
            printf("--- NavBar ---");
            printf("\n\nO que deseja fazer?\n(1)-Menu\t(2)-Pagina principal\n");
            scanf("%d",&navbar);
            }
            if (navbar==1){
                // Exibe os dados do preceptor
                printf("\n--- MENU ---\n\n");
                printf("\n--- Dados do Preceptor ---\n");
                printf("Logado: %s\n", Medico->preceptor->nome);
                printf("\nO que deseja fazer?\n(1)-Vizualizar Dados \t (2)-Trocar Senha \t (3)Sair\n");
                scanf("%d", &menu_navbar);
                if (menu_navbar==1){
                    printf("\n--- Vizualizar Dados ---\n");   
                    printf("Nome: %s\n", Medico->preceptor->nome);
                    printf("CPF: %s\n", Medico->preceptor->cpf);
                    printf("E-mail: %s\n", Medico->preceptor->email);
                    printf("CRM: %s\n", Medico->preceptor->CRM);
                    printf("Especializacao: %s\n", Medico->preceptor->especializacao);
                    printf("Aperter qualquer tecla para ir ao menu!");
                    getchar();
                    getchar();
                }else if (menu_navbar==2) {
                    trocar_senha(email);
                }else {
                    printf("Fechando App...\n");
                    printf("Deseja realmente Sair?\n(1)-Sim\t(2)-Nao\n");
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

void lg_adm(char email[20], lista_aluno* lista_de_alunos,lista_medico* lista_de_medicos, lista_adm* lista_de_adm){
//busca nos arquivos o email e nível
    lista_adm* auxAdm=lista_de_adm; //Lista de médicos cadastrados
    lista_aluno* auxAlunos; //Lista que salvará todos os alunos
    lista_medico* auxMedicos; //Lista que salvará todos os preceptores
//buscar os dados do adm
    while (strcmp(auxAdm->administrador->email,email)!=0 || auxAdm==NULL){
        auxAdm=auxAdm->next;
    }
    if (auxAdm==NULL){
        printf("Erro ao localizar usuario!\n");
        return;
    }

//Menu Principal
    int paginaprincipal=1;
    //int menu_navbar;
    //int sair_app;
    //char senha_antiga[100],senha_nova[100],senha_verificador[100];
    while(paginaprincipal!=0){
        int subpagina=0;
        while (subpagina!=1 && subpagina!=2){
        printf("--- Pagina Principal ---");
        printf("\n\nO que deseja fazer?\n(1)-Acrescentar Novo Membro\t(2)-Acessar conta de um membro\t(3)Estatística\t(4)Menu\n");
        scanf("%d",&subpagina);
            if(subpagina==1){ //criar residente, preceptor e adm
                int a;
                //Adicionaro no arquivo "senhasBC.txt" e no "banco_de_dados.txt" e opções de pesquisa @@G10@@
                char nome1[100],email1[20], cpf1[12],papel1[10],preceptor1[20],especializacao1[20],CRM1[20];
                printf("Qual o nome:\n");
                getchar();
                fgets(nome1,sizeof(nome1),stdin);
                printf("Qual o email:\n");
                getchar();
                fgets(email1,sizeof(email1),stdin); 
                printf("Qual o CPF:\n");
                getchar();
                fgets(cpf1,sizeof(cpf1),stdin); 
                printf("Qual o papel:\n");
                getchar();
                fgets(papel1,sizeof(papel1),stdin);
                if (strcmp(papel1,"residente\n")==0){ //criar residente
                    printf("Qual o preceptor?\n");
                    getchar();
                    fgets(preceptor1,sizeof(preceptor1),stdin);
                    printf("Qual a especialização?\n");
                    getchar();
                    fgets(especializacao1,sizeof(especializacao1),stdin);
                    printf("Deseja Salva?\n1)Sim\t2)Nao");
                    scanf("%d",&a);
                    if(a==1){
                        auxAlunos=lista_de_alunos;
                        while(auxAlunos->next!=NULL){
                            auxAlunos=auxAlunos->next;
                        }
                        auxAlunos->next=(lista_aluno *)malloc(sizeof(lista_aluno));
                        auxAlunos=auxAlunos->next;
                        auxAlunos->next=NULL;
                        strcpy(auxAlunos->aluno->nome,nome1);
                        strcpy(auxAlunos->aluno->email,email1);
                        strcpy(auxAlunos->aluno->cpf,cpf1);
                        strcpy(auxAlunos->aluno->papel,papel1);
                        strcpy(auxAlunos->aluno->email_preceptor,preceptor1);
                        strcpy(auxAlunos->aluno->especializacao,especializacao1);
                    }else if (a==2){
                        printf("Voltando para Pagina Principal...");
                    }
                }else if (strcmp(papel1,"preceptor")==0){
                    printf("Qual o CRM?\n");
                    getchar();
                    fgets(CRM1,sizeof(CRM1),stdin);
                    printf("Qual a especialização?\n");
                    getchar();
                    fgets(especializacao1,sizeof(especializacao1),stdin);
                    printf("Deseja Salva?\n1)Sim\t2)Nao");
                    scanf("%d",&a);
                    if(a==1){
                        auxMedicos=lista_de_medicos;
                        while(auxMedicos->next!=NULL){
                            auxMedicos=auxMedicos->next;
                        }
                        auxMedicos->next=(lista_medico *)malloc(sizeof(lista_medico));
                        auxMedicos=auxMedicos->next;
                        auxMedicos->next=NULL;
                        strcpy(auxMedicos->preceptor->nome,nome1);
                        strcpy(auxMedicos->preceptor->email,email1);
                        strcpy(auxMedicos->preceptor->cpf,cpf1);
                        strcpy(auxMedicos->preceptor->papel,papel1);
                        strcpy(auxMedicos->preceptor->CRM,CRM1);
                        strcpy(auxMedicos->preceptor->papel,especializacao1);
                    }else if (a==2){
                        printf("Voltando para Pagina Principal...");
                    }
                }else if (strcmp(papel1,"adm")==0){
                    printf("Deseja Salva?\n1)Sim\t2)Nao");
                    scanf("%d",&a);
                    if(a==1){
                        auxAdm=lista_de_adm;
                        while(auxAdm->next!=NULL){
                            auxAdm=auxAdm->next;
                        }
                        auxAdm->next=(lista_adm *)malloc(sizeof(lista_adm));
                        auxAdm=auxAdm->next;
                        auxAdm->next=NULL;
                        strcpy(auxAdm->administrador->nome,nome1);
                        strcpy(auxAdm->administrador->email,email1);
                        strcpy(auxAdm->administrador->cpf,cpf1);
                        strcpy(auxAdm->administrador->papel,papel1);
                    }else if (a==2){
                        printf("Voltando para Pagina Principal...");
                    }
                }else {
                    printf("Papel inexistente!\n");
                }
            }else if (subpagina==2){
                //listas - lista_de_alunos e lista_de_medicos
                int x;
                printf("Deseja buscar um Residente ou um Preceptor?\n1) Residente\t2) Preceptor\n");
                scanf("%d",&x);
                int k;
                printf("Deseja buscar por:\n1) Nome\t2) Email\t3)CPF\n");
                scanf("%d",&k);
                printf("Escreva: \n");
                getchar();
                char incremento[100];
                fgets(incremento,sizeof(incremento),stdin);
                incremento[strcspn(incremento, "\n")] = '\0';
                auxAlunos=lista_de_alunos;
                auxMedicos=lista_de_medicos;
                if (k==1){
                    while (strcmp(auxAlunos->aluno->nome,incremento)!=0){
                        if (auxAlunos->next!=NULL){
                            auxAlunos=auxAlunos->next;
                        }else {
                            auxAlunos=NULL;
                            break;
                        }
                    }
                    while (strcmp(auxMedicos->preceptor->nome,incremento)!=0){
                        if (auxMedicos->next!=NULL){
                            auxMedicos=auxMedicos->next;
                        }else {
                            auxMedicos=NULL;
                            break;
                        }
                    }
                }else if (k==2){
                    while (strcmp(auxAlunos->aluno->email,incremento)!=0){
                        if (auxAlunos->next!=NULL){
                            auxAlunos=auxAlunos->next;
                        }else {
                            auxAlunos=NULL;
                            break;
                        }
                    }
                    while (strcmp(auxMedicos->preceptor->email,incremento)!=0){
                        if (auxMedicos->next!=NULL){
                            auxMedicos=auxMedicos->next;
                        }else {
                            auxMedicos=NULL;
                            break;
                        }
                    }
                }else {
                    while (strcmp(auxAlunos->aluno->cpf,incremento)!=0 && auxAlunos!=NULL){
                        if (auxAlunos->next!=NULL){
                            auxAlunos=auxAlunos->next;
                        }else {
                            auxAlunos=NULL;
                            break;
                        }
                    }
                    while (strcmp(auxMedicos->preceptor->cpf,incremento)!=0 && auxMedicos!=NULL){
                        if (auxMedicos->next!=NULL){
                            auxMedicos=auxMedicos->next;
                        }else {
                            auxMedicos=NULL;
                            break;
                        }
                    }
                }
                if (x==1){
                        if (auxAlunos==NULL){
                            printf("Aluno nao existe\n");
                            printf("Retornando a Pagina Principal\n");
                        }else{
                            printf("\n--- Vizualizar Dados ---\n");   
                            printf("Nome: %s\n", auxAlunos->aluno->nome);
                            printf("CPF: %s\n", auxAlunos->aluno->cpf);
                            printf("E-mail: %s\n", auxAlunos->aluno->email);
                            printf("E-mail do Preceptor: %s\n", auxAlunos->aluno->email_preceptor);
                            printf("Especializacao: %s\n", auxAlunos->aluno->especializacao);
                            printf("Historico de presencas:\n");
                            int n=1;
                            while(auxAlunos->aluno->lista_de_Presenca->next!=NULL){
                                printf("Presenca: %d\n\tEntrada: %ld\n\tSaida: %ld\n", n, auxAlunos->aluno->lista_de_Presenca->entrada, auxAlunos->aluno->lista_de_Presenca->saida);
                                if (auxAlunos->aluno->lista_de_Presenca->next!=NULL){ //problema por criar a lista antes de verificar se tem próximo
                                auxAlunos->aluno->lista_de_Presenca=auxAlunos->aluno->lista_de_Presenca->next;
                                }else {
                                    auxAlunos->aluno->lista_de_Presenca->next=NULL;
                                }
                                n++;
                            }
                            printf("Aperter qualquer tecla para ir a Pagina Principal!");
                            getchar();
                            getchar();
                        }
                    }else {
                        printf("\n--- Vizualizar Dados ---\n");   
                        printf("Nome: %s\n", auxMedicos->preceptor->nome);
                        printf("CPF: %s\n", auxMedicos->preceptor->cpf);
                        printf("E-mail: %s\n", auxMedicos->preceptor->email);
                        printf("CRM: %s\n", auxMedicos->preceptor->CRM);
                        printf("Especializacao: %s\n", auxMedicos->preceptor->especializacao);
                        printf("Aperter qualquer tecla para ir ao menu!\n");
                        getchar();
                        getchar();
                    }
            }else if (subpagina==3){
                //mostrar dados estatísticos
                printf("Aqui poderá ser vizualizado os dados estatísticos das presenças e dos preseceptores!\n");
                printf("Aperter qualquer tecla para ir ao menu!\n");
                        getchar();
                        getchar();
            }else{
                printf("Valor invaido!\n");
            }

        }
    }
}

#endif