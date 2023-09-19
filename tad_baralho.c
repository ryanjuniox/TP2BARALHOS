#include "tad_baralho.h"

int quantidadeCartas(int nBaralho){
    return(52 * nBaralho);
}

void criarPilha(Baralho* pBaralho){
    pBaralho->Topo = 0;
}

int Empilha(Baralho* pBaralho, Carta* carta, int nBaralho){
    if(pBaralho->Topo == quantidadeCartas(nBaralho)){
        return 0;
    }
    else{
        pBaralho->carta[pBaralho->Topo].naipe = carta->naipe;
        pBaralho->carta[pBaralho->Topo].valor = carta->valor;
        pBaralho->Topo++;
        return 1;
    }
}

void verificaTopoPilha(Baralho* pBaralho, Carta* carta){
   if(pBaralho->Topo != 0){
        Carta cartaTopo = pBaralho->carta[pBaralho->Topo-1];
        *carta = cartaTopo; 
   }
}

int verificaPilhaVazia(Baralho* pBaralho){
    return(pBaralho->Topo == 0);
}

int Desempilha(Baralho* pBaralho, Carta* carta){
    if(verificaPilhaVazia(pBaralho)){
        return 0;
    }
    else{
        pBaralho->Topo--;
        *carta = pBaralho->carta[pBaralho->Topo];
        pBaralho->quantidade_cartas--;
        return 1;
    }
}

void criarBaralho(Baralho* pBaralho, int nBaralho, vExcluidos nExcluidos, Carta vBaralho[MAX_ITEM]){
    srand(time(NULL));
    Baralho* pBaralhoAux = malloc(sizeof(Baralho));
    Carta* cartaAux = malloc(sizeof(Carta));
    int vetorValor[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    char vetorNaipe[4] = {'C', 'O', 'P', 'E'};
    int qCartas = quantidadeCartas(nBaralho);

    for(int i=0; i<qCartas; i++){
        int iValor = i % 13;
        int iNaipe = i % 4;
        Carta* carta = malloc(sizeof(Carta));
        carta->naipe = vetorNaipe[iNaipe];
        carta->valor = vetorValor[iValor];
        vBaralho[i].naipe = vetorNaipe[iNaipe];
        vBaralho[i].valor = vetorValor[iValor];
        Empilha(pBaralhoAux, carta, nBaralho);
    }


    int cont=0;
    for(int i=0; i<qCartas; i++){
        cont = 0;
        for(int j=0; j<nExcluidos.qValores; j++){
            if(pBaralhoAux->carta[i].valor == nExcluidos.valores[j]){
                cont++;
            }
        }
        if(cont == 0){
            
            cartaAux->naipe = pBaralhoAux->carta[i].naipe;
            cartaAux->valor = pBaralhoAux->carta[i].valor;
            Empilha(pBaralho, cartaAux, nBaralho);
        }
    }
    
    //Algoritmo de Embaralhamento
    for(int i=(qCartas-1)-(nExcluidos.qValores*4); i>0; i--){
        int j = rand() % (i + 1);
        Carta temp = pBaralho->carta[i];
        pBaralho->carta[i] = pBaralho->carta[j];
        pBaralho->carta[j] = temp;

        Carta temp2 = vBaralho[i];
        vBaralho[i] = vBaralho[j];
        vBaralho[j] = temp2;
    }

    free(pBaralhoAux);
    free(cartaAux);

}

int verificaGanhador(Baralho* pJogador, int mao, Carta cartaCoringa){
    int igual = 0;
    int maoJogador[3];
    for(int i=0; i<mao; i++){
        maoJogador[i] = pJogador->carta[i].valor;
    }
    for(int i=0; i<mao; i++){
        if(maoJogador[0] == maoJogador[i]){
            igual++;
        }
    }
    if(mao == igual){
        int i=1;
        return i;
    }
}

void imprimeCartas(Baralho* pJogador, int mao){
    for(int i=mao; i>=0; i--){
        if(pJogador->carta[i].valor == 11){
            printf("[J %c] ",pJogador->carta[i].naipe);
        }
        else if(pJogador->carta[i].valor == 12){
            printf("[Q %c] ",pJogador->carta[i].naipe);
        }
        else if(pJogador->carta[i].valor == 13){
            printf("[K %c] ",pJogador->carta[i].naipe);
        }
        else if(pJogador->carta[i].valor == 1){
            printf("[A %c] ",pJogador->carta[i].naipe);
        }
        else{
            printf("[%d %c] ",pJogador->carta[i].valor, pJogador->carta[i].naipe);
        }
    }
    printf("\n");
}

void imprimeCarta(Carta cartaAleatoria){
    if(cartaAleatoria.valor == 11){
        printf("[J %c] \n", cartaAleatoria.naipe);
    }
    else if(cartaAleatoria.valor == 12){
        printf("[Q %c] \n", cartaAleatoria.naipe);
    }
    else if(cartaAleatoria.valor == 13){
        printf("[K %c] \n", cartaAleatoria.naipe);
    }
    else if(cartaAleatoria.valor == 1){
        printf("[A %c] \n", cartaAleatoria.naipe);
    }
    else{
        printf("[%d %c] \n", cartaAleatoria.valor, cartaAleatoria.naipe);
    }
}

void descarteCarta(Baralho* pJogador, int mao, int iDescarte, Baralho* pDescarte, int nBaralho){
    Baralho* pAux = malloc(sizeof(Baralho));
    criarPilha(pAux);
    Carta* cartaAux = malloc(sizeof(Carta));
    for(int i=0; i<mao+1; i++){
        Desempilha(pJogador, cartaAux);
        if(iDescarte == i){
            Empilha(pDescarte, cartaAux, nBaralho);
        }
        else{
            Empilha(pAux, cartaAux, nBaralho);
        }
    }
    for(int i=0; i<mao; i++){
        Desempilha(pAux, cartaAux);
        Empilha(pJogador, cartaAux, nBaralho);
    }
}

void tentativaJogo(Baralho* pBaralho, Baralho* pJogador, Baralho* pDescarte, int mao, int nBaralho){
    //IMPRESSÃO DA MÃO DO JOGADOR
    printf("SUA MAO: ");
    imprimeCartas(pJogador, mao-1);

    //IMPRIMIR CARTA DO TOPO E DECISAO DO JOGADOR
    int iDecisao=0;
    int iDescarte;
    printf("CARTA TOPO: ");
    imprimeCarta(pDescarte->carta[pDescarte->Topo-1]);
    printf("CARTA TOPO (0) OU CARTA BARALHO (1): ");
    scanf("%d",&iDecisao);

    if(iDecisao == 0){
        Carta* cartaAux = malloc(sizeof(Carta));
        Desempilha(pDescarte, cartaAux);
        Empilha(pJogador, cartaAux, nBaralho);
        printf("SUA MAO: ");
        imprimeCartas(pJogador, mao);
        printf("POSICAO DE DESCARTE: ");
        scanf("%d",&iDescarte);
        descarteCarta(pJogador, mao, iDescarte, pDescarte, nBaralho);
        printf("MAO ATUALIZADA: ");
        imprimeCartas(pJogador, mao-1);
    }
    else if(iDecisao == 1){
        Carta* cartaDesempilha = malloc(sizeof(Carta));
        Desempilha(pBaralho, cartaDesempilha);
        Empilha(pJogador, cartaDesempilha, nBaralho);
        imprimeCartas(pJogador, mao);
        printf("POSICAO DE DESCARTE: ");
        scanf("%d",&iDescarte);
        descarteCarta(pJogador, mao, iDescarte, pDescarte, nBaralho);
        printf("MAO ATUALIZADA: ");
        imprimeCartas(pJogador, mao-1);
    }

}

void Particao(int Esq, int Dir, int *i, int *j, Carta A[MAX_ITEM_VETOR]){
    Carta pivo, aux;
    *i = Esq; *j = Dir;
    pivo = A[(*i + *j)/2]; /* obtem o pivo x */
    do{
        while (ComparaCartas(pivo, A[*i]) > 0) (*i)++;
        while (ComparaCartas(pivo, A[*j]) < 0) (*j)--;
        if (*i <= *j)
        {
            aux = A[*i]; A[*i] = A[*j]; A[*j] = aux;
            (*i)++; (*j)--;
            printf("Particionando: Esq = %d, Dir = %d, i = %d, j = %d\n", Esq, Dir, *i, *j);
        }
    } while (*i <= *j);
}


void Ordena(int Esq, int Dir, Carta A[MAX_ITEM_VETOR]){
    int i,j;
    Particao(Esq, Dir, &i, &j, A);
    printf("Chamada recursiva: Esq = %d, Dir = %d\n", Esq, j);
    if (Esq < j) Ordena(Esq, j, A);
    printf("Chamada recursiva: Esq = %d, Dir = %d\n", i, Dir);
    if (i < Dir) Ordena(i, Dir, A);
}

void QuickSort(Carta A[MAX_ITEM_VETOR], int n){
    Ordena(0, n-1, A);
}

void BubbleSort(Carta A[MAX_ITEM_VETOR], int n){
    int i, j;
    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if(ComparaCartas(A[j], A[j+1]) > 0){
                Carta temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
            printf("Comparando as cartas %d%c e %d%c\n", A[j].valor,A[j].naipe, A[j+1].valor, A[j+1].naipe);       
        }
    }
}

void SelectionSort(Carta A[MAX_ITEM_VETOR], int n){
    int i, j, Min;
    for(i=0; i<n-1; i++){
        Min = i;
        for(j=i+1; j<n; j++){
            if(ComparaCartas(A[j], A[Min]) < 0){
                Min = j;
                printf("Comparando as cartas %d%c e %d%c\n", A[j].valor, A[j].naipe, A[Min].valor, A[Min].naipe);
            }
        }
        Carta aux = A[Min];
        A[Min] = A[i];
        A[i] = aux;
        printf("Troca realizada: %d%c com %d%c\n", A[Min].valor, A[Min].naipe, A[i].valor, A[i].naipe);
    }
}

int ComparaCartas(Carta carta1, Carta carta2) {
    int mapping[256];
    mapping['C'] = 1;
    mapping['O'] = 2;
    mapping['P'] = 3;
    mapping['E'] = 4;

    // Compara os naipes utilizando o mapeamento
    if(carta1.valor < carta2.valor){
        return -1;
    }else if(carta1.valor > carta2.valor){
        return 1;
    }
    
    // Se os valores forem iguais, compara os naipes
    if(mapping[carta1.naipe] < mapping[carta2.naipe]){
        return -1;
    }else if(mapping[carta1.naipe] > mapping[carta2.naipe]){
        return 1;
    }
    
    // Se os naipes também forem iguais, retorna 0
    return 0;
}


