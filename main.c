#include "tad_baralho.h"

int main(){

    Carta* vBaralho = malloc(sizeof(Carta)*46800);
    Baralho* pBaralho = malloc(sizeof(Baralho)*800);

    //Variavel
    int nBaralho=0, nCartas=0, mao=0;
    char cartaCoringaLinha[2];

    char metodo[] = "quicksort";
    char nome_arquivo[50];

    //ARQUIVO DE ENTRADA
    FILE *arquivo_entrada = fopen("entrada_truco.txt","r");
	if (arquivo_entrada == NULL) {
      printf("Não foi possível abrir o arquivo.\n");
      return 1;
	}

    //ARQUIVO DE SAIDA
	FILE* arquivo_saida;
    sprintf(nome_arquivo, "ordenacao_entrada_%s.txt", metodo);

    arquivo_saida = fopen(nome_arquivo,"w");
	if(arquivo_saida == NULL){
		printf("Erro ao criar o arquivo.\n");
        return 1;
	}


    // LEITURA DO ARQUIVO
    char linha[100];

    //Numero de Baralhos
    fgets(linha, sizeof(linha), arquivo_entrada);
    sscanf(linha, "%d", &nBaralho);
    nCartas = quantidadeCartas(nBaralho);

    //Cartas Excluídas
    fgets(linha, sizeof(linha), arquivo_entrada);
    vExcluidos nExcluidos;
    nExcluidos.qValores = 0;
    char *token = strtok(linha, ",");
    while(token != NULL){
        nExcluidos.valores[nExcluidos.qValores] = atoi(token);
        nExcluidos.qValores++;
        token = strtok(NULL,",");
    }

    //Carta Coringa
    fgets(linha, sizeof(linha), arquivo_entrada);
    sscanf(linha, "%s", &cartaCoringaLinha);
    Carta cartaCoringa;
    int existeCoringa = False;
    if(cartaCoringaLinha[0] != 0 && cartaCoringaLinha[1] != 0){
        if(cartaCoringaLinha[0] != 'A' && cartaCoringaLinha[0] != 'J' && cartaCoringaLinha[0] != 'Q' && cartaCoringaLinha[0] != 'K'){
            int aux = atoi(&cartaCoringaLinha[0]);
            cartaCoringa.valor = aux;
        }
        else{
            if(cartaCoringaLinha[0] == 'A'){
                cartaCoringa.valor = 1;
            }
            else if(cartaCoringaLinha[0] == 'J'){
                cartaCoringa.valor = 11;
            }
            else if(cartaCoringaLinha[0] == 'Q'){
                cartaCoringa.valor = 12;
            }
            else if(cartaCoringaLinha[0] == 'K'){
                cartaCoringa.valor = 13;
            }
        }
        cartaCoringa.naipe = cartaCoringaLinha[1];
        existeCoringa = True;
    }

    //Quantidade de Cartas na Mão
    fgets(linha, sizeof(linha),arquivo_entrada);
    sscanf(linha, "%d", &mao);

    fclose(arquivo_entrada);

    //Criação do Baralho
    criarPilha(pBaralho);
    criarBaralho(pBaralho, nBaralho, nExcluidos, vBaralho);

    //Criação da Pilha de Descartes
    Baralho* pDescarte = malloc(nCartas * sizeof(Baralho));
    criarPilha(pDescarte);

    if(strcmp(metodo, "quicksort") == 0){
        printf("--- QUICK SORT --- \n");
        clock_t inicio = clock();
        QuickSort(vBaralho, quantidadeCartas(nBaralho));
        clock_t fim = clock();
        char cartaImprimida[2];
        for(int i=0; i<quantidadeCartas(nBaralho); i++){
            if(vBaralho[i].valor == 1){
                sprintf(cartaImprimida, "A%c", vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else if(vBaralho[i].valor == 11){
                sprintf(cartaImprimida, "J%c", vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else if(vBaralho[i].valor == 12){
                sprintf(cartaImprimida, "Q%c", vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else if(vBaralho[i].valor == 13){
                sprintf(cartaImprimida, "K%c",vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else{
                sprintf(cartaImprimida, "%d%c", vBaralho[i].valor, vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
        }
        double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tempo total de execucao: %.2f \n", tempo_segundos );
        fclose(arquivo_saida);
    }
    else if(strcmp(metodo, "bubblesort") == 0){
        printf("--- BUBBLE SORT --- \n");
        clock_t inicio = clock();
        BubbleSort(vBaralho, quantidadeCartas(nBaralho));
        clock_t fim = clock();
        char cartaImprimida[2];
        for(int i=0; i<quantidadeCartas(nBaralho); i++){
            if(vBaralho[i].valor == 1){
                sprintf(cartaImprimida, "A%c", vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else if(vBaralho[i].valor == 11){
                sprintf(cartaImprimida, "J%c", vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else if(vBaralho[i].valor == 12){
                sprintf(cartaImprimida, "Q%c", vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else if(vBaralho[i].valor == 13){
                sprintf(cartaImprimida, "K%c",vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else{
                sprintf(cartaImprimida, "%d%c", vBaralho[i].valor, vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
        }
        double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tempo total de execucao: %.2f \n", tempo_segundos );
        fclose(arquivo_saida);
    }
    else if(strcmp(metodo, "selectionsort") == 0){
        printf("--- SELECTION SORT --- \n");
        clock_t inicio = clock();
        SelectionSort(vBaralho, quantidadeCartas(nBaralho));
        clock_t fim = clock();
        char cartaImprimida[2];
        for(int i=0; i<quantidadeCartas(nBaralho); i++){
            if(vBaralho[i].valor == 1){
                sprintf(cartaImprimida, "A%c", vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else if(vBaralho[i].valor == 11){
                sprintf(cartaImprimida, "J%c", vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else if(vBaralho[i].valor == 12){
                sprintf(cartaImprimida, "Q%c", vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else if(vBaralho[i].valor == 13){
                sprintf(cartaImprimida, "K%c",vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
            else{
                sprintf(cartaImprimida, "%d%c", vBaralho[i].valor, vBaralho[i].naipe);
                fprintf(arquivo_saida, "%s ",cartaImprimida);
            }
        }
        double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tempo total de execucao: %.2f \n", tempo_segundos );
        fclose(arquivo_saida);
    }

    int inicioJogo = 0;
    printf("INICIAR JOGO (1): ");
    scanf("%d",&inicioJogo);

    if(inicioJogo == 1){

        printf("\n--- INICIO DO JOGO ---\n");
        printf("Cada jogador devera fazer uma sequencia de %d cartas. \n\n",mao);

        if(existeCoringa == True){
            printf("CARTA CORINGA: ");
            imprimeCarta(cartaCoringa);
        }

        //Primeiro Jogador e Segundo Jogador
        Baralho* pJogadorUm = malloc(sizeof(Baralho));
        criarPilha(pJogadorUm);
        Baralho* pJogadorDois = malloc(sizeof(Baralho));
        criarPilha(pJogadorDois);

        //CRIAÇÃO DAS MÃOS DOS DOIS JOGADORES
        Carta* cartaDesempilha = malloc(sizeof(Carta));
        for(int i=0; i<mao; i++){ //Empilha Jogador Um
            Desempilha(pBaralho, cartaDesempilha);
            Empilha(pJogadorUm, cartaDesempilha, nBaralho);
        }
        for(int i=0; i<mao; i++){ //Empilha Jogador Dois
            Desempilha(pBaralho, cartaDesempilha);
            Empilha(pJogadorDois, cartaDesempilha, nBaralho);
        }

        int iDescarte;
        int Ganhador = 0;
        int primeiraJogada = True;
        while(1){

            if(primeiraJogada == True){
                printf("--- JOGADOR UM ---\n");
                Desempilha(pBaralho, cartaDesempilha);
                Empilha(pJogadorUm, cartaDesempilha, nBaralho);
                printf("SUA MAO: ");
                imprimeCartas(pJogadorUm, mao);
                printf("POSICAO DE DESCARTE: ");
                scanf("%d",&iDescarte);
                descarteCarta(pJogadorUm, mao, iDescarte, pDescarte, nBaralho);
                printf("MAO ATUALIZADA: ");
                imprimeCartas(pJogadorUm, mao-1);
                Ganhador = verificaGanhador(pJogadorUm, mao, cartaCoringa);
                if(Ganhador == 1){
                    printf("JOGADOR UM GANHOU!");
                    printf("\nJOGADOR UM GANHOU!\n");
                    printf("MAO VENCEDORA: ");
                    imprimeCartas(pJogadorUm, mao-1);
                    break;
                }
                primeiraJogada = False;
            }
            else{
                printf("--- JOGADOR DOIS ---\n");
                tentativaJogo(pBaralho, pJogadorDois, pDescarte, mao, nBaralho);
                Ganhador = verificaGanhador(pJogadorDois, mao, cartaCoringa);
                if(Ganhador == 1){
                    printf("\nJOGADOR DOIS GANHOU!\n");
                    printf("MAO VENCEDORA: ");
                    imprimeCartas(pJogadorDois, mao-1);
                    break;
                }
                printf("\n");
                printf("--- JOGADOR UM ---\n");
                tentativaJogo(pBaralho, pJogadorUm, pDescarte, mao, nBaralho);
                Ganhador = verificaGanhador(pJogadorUm, mao, cartaCoringa);
                if(Ganhador == 1){
                    printf("\nJOGADOR UM GANHOU!\n");
                    printf("MAO VENCEDORA: ");
                    imprimeCartas(pJogadorUm, mao-1);
                    break;
                }
                printf("\n");
            }
        }//FIM DO WHILE
    }//FIM DO IF DO JOGO
    else{
        return 1;
    }


    return 0;
} // FIM DO MAIN