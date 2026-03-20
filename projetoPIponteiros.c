#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char arquivo[20] = "teste.txt";


//cadastro de jogadores no time

//utilizando typedef para facilitar a organizcao e entendimento
typedef struct {
    char nome[100];
    int idade;
    char posicao[15];      //colocar os parametros
    char time[25];
} Jogador;




//adicionar as informacoes do jogador
void adicionarjogador(Jogador *novojogador){ // o ponetiro vai evitar uma copia desnecessaria, agilizando o codigo e melhorando a sua eficiencia
    FILE *f = fopen(arquivo,"a"); //a de adicionar
    if(f == NULL){
        printf("Erro ao abrir o arquivo");
    }
    fprintf(f,"%s|%i|%s|%s\n",novojogador->nome,novojogador->idade,novojogador->posicao,novojogador->time);
  fclose(f);
}









//le os dados dos jogadores do arquivo, cointa quantosa tem
void jogadoresinscritos(){
    FILE *f = fopen(arquivo,"r"); //r de leitura
    if(f==NULL){
        printf("Erro ao abrir o arquivo\n");
    }
    Jogador *novojogador = (Jogador *)malloc(sizeof(Jogador));
    if (novojogador == NULL) { //verificacao
        printf("Erro ao alocar memoria\n");
        fclose(f);
        return;
    }
    char linha[200]; // Buffer para ler a linha inteira
    int total = 0; //fgets le a string intteria,a scanf aas palavras sesparando as ex nomes compostos


    while (fgets(linha, sizeof(linha), f)) {
        // Lê a linha e extrai os dados corretamente usando "|"
        if (sscanf(linha, "%99[^|]|%d|%49[^|]|%49[^\n]",  //le a string de onde os dados searao lidos,o formato dos dados, e os dados     novojogador.nome,
                   novojogador->nome,
                   &novojogador->idade,
                   novojogador->posicao,
                   novojogador->time) == 4) { //vai ver se os dados estao sendo lidos corretamente
            total++;
        }
    }


    printf("Numero de jogadores inscritos: %i\n",total);
    free(novojogador);
    fclose(f);
}


void imprimir_opcoes(){
    printf("+---------------------------------------+\n");
    printf("|1 - Adicionar Jogador                  |\n");
    printf("|2 - Exibir Jogadores                   |\n");
    printf("|3 - Editar Jogador                     |\n");
    printf("|4 - Excluir Jogador                    |\n");
    printf("|5 - Sair                               |\n");
    printf("+---------------------------------------+\n");
}

















//funcao exibir jogadores
void exibirjogadores(){
    FILE *f = fopen(arquivo,"r");
    if(f==NULL){
        printf("Erro ao abrir o arquivo\n");
    }
    Jogador *novojogador = (Jogador *)malloc(sizeof(Jogador)); // Aloca memoria para o jogador, a funcao malloc trata disso
     char linha[200];
    printf("Lista de jogadores:\n");
    printf("+-----------------+-------+-----------------+--------------------+\n");
    printf("| Nome                | Idade | Posicao         | Time               |\n");
    printf("+-----------------+-------+-----------------+--------------------+\n");

    //le e exibe
    while (fgets(linha, sizeof(linha), f) != NULL) { //checar a linha, le uma linha, continue ate quando houver linhas
        sscanf(linha, "%99[^|]|%d|%14[^|]|%24[^\n]", novojogador->nome, &novojogador->idade, novojogador->posicao, novojogador->time); //agora ta certo, le e armazena, os numeros sao ate quantos caracteres se podem ler e os caractyeres den tro quando ver para e vai pro proximo
        printf("| %-19s | %-5d | %-16s | %-18s |\n", novojogador->nome, novojogador->idade, novojogador->posicao, novojogador->time); // , /09 limita o nome ate 19 letras,lembrar de dar mais espaco para os printfs
    }
    printf("+-----------------+-------+-----------------+--------------------+\n");
    free(novojogador); //libera a memoria
    fclose(f);
    }

















//funcao editar jogadores, se der algum espaco no final na hora de escrever o nome, na hora de editar tambem tem que colocar o espaco se nao nao vai encontrar o jogador
void editarjogadores() {
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w"); //criar arquivo temporario par a mudanca/edicao
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(f);
        return;
    } Jogador *novojogador = (Jogador *)malloc(sizeof(Jogador)); //aloco a memoria

    char nomeBusca[100]; //buscar nome para editar o jogador especifico
    printf("Digite o nome do jogador que deseja editar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove o '\n'

    //Buscar pela idade
    int idadeBusca;
    printf("Digite a idade do jogador que deseja editar: ");
    scanf("%d", &idadeBusca);
    while (getchar() != '\n');


    char posicaoBusca[100];
    printf("Digite a posicao do jogador que deseja editar: ");
    fgets(posicaoBusca, sizeof(posicaoBusca), stdin);
    posicaoBusca[strcspn(posicaoBusca, "\n")] = 0;

    //pedir tambem o time no caso de nomes iguais, como PEDRO E PEDRO
    char timeBusca[100];
    printf("Digite o time do jogador que deseja editar: ");
    fgets(timeBusca, sizeof(timeBusca), stdin);
    timeBusca[strcspn(timeBusca, "\n")] = 0;




    char linha[200];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), f)) { //le a linha dos arquivos e extrai os dados formatados, le a linha inteira e armazena na variavel linha
        sscanf(linha, "%99[^|]|%d|%14[^|]|%24[^\n]", novojogador->nome, &novojogador->idade, novojogador->posicao, novojogador->time);


        // Depuração: Verifique se os dados estão sendo lidos corretamente
            if (strcmp(novojogador->nome, nomeBusca) == 0 && strcmp(novojogador->time,timeBusca)==0 && novojogador->idade==idadeBusca && strcmp(novojogador->posicao,posicaoBusca)==0) { //strcmp compara cada caractere das duas strings, se forem iguais retorna 0, por isso se da zero o encoantrado sera igual a 1
            encontrado = 1;
            printf("Jogador encontrado! Digite as novas informacoes: \n");

            printf("Novo nome: ");
            fgets(novojogador->nome, sizeof(novojogador->nome), stdin);
            novojogador->nome[strcspn(novojogador->nome, "\n")] = 0; //remove a quebra de linha

            printf("Nova idade: ");
            scanf("%d", &novojogador->idade);
            while (getchar() != '\n'); // Limpar buffer

            printf("Nova posicao: ");
            fgets(novojogador->posicao, sizeof(novojogador->posicao), stdin);
            novojogador->posicao[strcspn(novojogador->posicao, "\n")] = 0;

            printf("Novo time: ");
            fgets(novojogador->time, sizeof(novojogador->time), stdin);
            novojogador->time[strcspn(novojogador->time, "\n")] = 0;
        }

        fprintf(temp, "%s|%d|%s|%s\n", novojogador->nome, novojogador->idade, novojogador->posicao, novojogador->time);
    }
     free(novojogador); //libero a memoria alocada
    fclose(f);
    fclose(temp);

    if (!encontrado) {
        printf("Jogador nao encontrado. \n");
        remove("temp.txt"); // Exclui o arquivo temporário se não houve mudanças
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("Jogador atualizado com sucesso!\n");
    }
}




























void excluirJogador() {
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(f);
        return;
    }
//pedir todas as informacoes, caso tenham jogadores com mesmo nome, para nao acabar excluindo incorretamente
    char nomeBusca[100];
    printf("Digite o nome do jogador que deseja excluir: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove o '\n'

    //Buscar pela idade
    int idadeBusca;
    printf("Digite a idade do jogador que deseja excluir: ");
    scanf("%d",&idadeBusca);
    while (getchar()!= '\n');


    char posicaoBusca[100];
    printf("Digite a posicao do jogador que deseja excluir: ");
    fgets(posicaoBusca, sizeof(posicaoBusca), stdin);
    posicaoBusca[strcspn(posicaoBusca, "\n")] = 0;


    //pedir tambem o time no caso de nomes iguais, como PEDRO E PEDRO
    char timebusca[100];
    printf("Digite o time do jogador que deseja editar: ");
    fgets(timebusca, sizeof(timebusca), stdin);
    timebusca[strcspn(timebusca, "\n")] = 0;


    Jogador *novojogador= (Jogador *)malloc(sizeof(Jogador)); //aloco a memoria
    if (novojogador == NULL) { //verificando
        printf("Erro ao alocar memória!\n");
        fclose(f);
        fclose(temp);
        return;
    }
    char linha[200];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), f)) {
        sscanf(linha, "%99[^|]|%d|%14[^|]|%24[^\n]",
               novojogador->nome, &novojogador->idade, novojogador->posicao, novojogador->time);

        if (strcmp(novojogador->nome, nomeBusca) == 0 && strcmp(novojogador->time,timebusca)==0 && novojogador->idade == idadeBusca && strcmp(novojogador->posicao,posicaoBusca)==0) {
            encontrado = 1;
            printf("Jogador '%s' excluido com sucesso!\n", nomeBusca);
            continue; // Pula a escrita no novo arquivo, essse continue pula o jogaodr encontrado da escrita do arquivo o resto printa }
        }
        fprintf(temp, "%s|%d|%s|%s\n", novojogador->nome, novojogador->idade, novojogador->posicao, novojogador->time);
    }
    free(novojogador); //libero a memoria alocada
    fclose(f);
    fclose(temp);

    if (!encontrado) {
        printf("Jogador nao encontrado.\n");
        remove("temp.txt"); // Exclui o temporário se nada mudou
    } else {
        remove(arquivo);
        rename("temp.txt", arquivo);
    }
}





























//criando a central de controle
//funcao principal
int main(){
    int opcao;
    do{ //vai perguntar qual o numero a partir das opcoes dadas
        imprimir_opcoes();
        printf("Digite sua opcao: ");
        scanf("%i",&opcao);
        getchar();//limpar o buffer

        Jogador novojogador;

    switch(opcao){
        //casos: 1 adicionar,2 exibir, 3 edit ar, 4 excluir, 5 sair
        case 1:
        do{
            printf("Qual o nome do jogador: ");
            fgets(novojogador.nome, sizeof(novojogador.nome), stdin);
             novojogador.nome[strcspn(novojogador.nome, "\n")] = 0; // Remove o '\n'
           if (strlen(novojogador.nome) ==0) {
               printf("Nome do jogador nao pode ser vazio! Tente novamente!\n");
           }
        } while (strlen(novojogador.nome) ==0); // WHILE PARA SE O COMPRIMENTO DO NOME = 0 OU SEJA, SE EU NNAO ESCREVER NADA ELE REPETIR



        do {
            printf("Digite a idade do jogador: ");
            scanf("%d", &novojogador.idade);
            while (getchar() != '\n'); // Limpa buffer após `scanf()`
            if (novojogador.idade <= 0) {
                printf("Idade do jogador nao pode ser zero! Tente novamente!\n");
            }
        } while (novojogador.idade <= 0);



       do {
           printf("Qual a posicao do jogador: ");
           fgets(novojogador.posicao, sizeof(novojogador.posicao), stdin);
           novojogador.posicao[strcspn(novojogador.posicao, "\n")] = 0;
           if (strlen(novojogador.posicao) ==0) {
               printf("Posicao do jogador nao pode ser vazia! Tente novamente\n");
           }
       } while (strlen(novojogador.posicao) ==0);



       do {
           printf("Digite o time do jogador: ");
           fgets(novojogador.time, sizeof(novojogador.time), stdin);
           novojogador.time[strcspn(novojogador.time, "\n")] = 0;
           if (strlen(novojogador.time) ==0) {
               printf("Time do jogador nao pode ser vazio! Tente novamente!\n");
           }
       }while (strlen(novojogador.time) ==0);



       adicionarjogador(&novojogador); //pelo ponteiro, o endereco da estrdutura
       break;

        case 2:
        exibirjogadores(); //como essas funcoes nao recvebem parametros, nao preciso enderecar a memoria para elas como fiz acima
        break;

        case 3:
        editarjogadores();
        break;

        case 4:
        excluirJogador();
        break;
        //fazer o excluir

        case 5: //saindo
        printf("Saindo do programa...\n");
        break;

        default:
        printf("Opcao invalida\n");
    }

    }while(opcao!=5);

}
