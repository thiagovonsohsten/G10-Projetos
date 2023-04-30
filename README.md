# G10-Projetos
Repositório - grupo Agilis - Projetos 2 - César School

RESUMO _____________
    PLANEJAMENTO:

    1. Artefato no hospital. 
    2. Esse artefato realizará as seguintes tarefas: 
    2.1 Identificação do usuário 
    2.2 Tempo de espera para cancelamento caso o usuário deseje
    2.3 Após os 5s, enviará as informações para a fila de envios
        2.3.1 Caso cancele, recomeça.
    2.4 Na fila de envios ele irá tentar enviar as informações para o servidor/app e caso não consiga, as informação ficaram armazenadas em uma lista e o sistema poderá receber novos id's, deixando enfileirado até que o problema seja resolvido e a conexão tenha retornado. 
    3. O artefato terá medidas de segurança para proteger os dados, ou seja, o artefato só terá o necessário para identificar a pessoa, fazendo assim com que diminua os dados contidos no artefato.

    CONSIDERAÇÕES:

    Era ideal usar Java, mas vamos usar a linguagem C.
    Para a comunicação de internet (TCP/IP) vamos usar provavelmente a biblioteca do socket.
    O hardware responsável por identificar o usuário será o Raspberry Pi, pois ele possui o GPIO, recurso esse que conversa com o sensor.

Fluxograma de Arquitetura dos códigos _______

        A linha de raciocínio fico a seguinte, vamos ter dois “servidores” separados, um para receber as presenças, gerenciar e salvar nos bancos de dados ou arquivo, e a outra é para visualizar o banco de dados.

    SistemaPrincipal.projetos10.c

        Nesse sistema vamos ter dois tipos de struct, um para ser o struct da mensagem recebida, que, não por coincidência, nomeamos como struct mensagem Request, e o outro é para a criação da lista encadeada struct ata *Head (ata de presença).
    O programa irá receber esse Request, e através de diversas verificações, irá salvar o valor na lista do Head ou salva no arquivo externo excluindo o valor na memória, consequentemente na lista sem preder as referências.
    Falta implementar a chegada dos dados e a saída.

    SistemaAcesso.projetos10.c

        Nesse sistema será de forma simplificada, terá 3 funções para cada usuário, residente, médico e gestor, cada função será alterada para diversas opções, sempre buscando os dados de um arquivo externo e trabalhando em cima dele, e salvando após as alterações. Apenas o ‘Sistema Principal.projetos10.c’ e o nível 3 (Gestor) terão como alterar o banco de dados, o restante terá apenas uma visualização do banco de dados.
