#ifndef TAD_BARALHO_H
#define TAD_BARALHO_H
#define MAX_ITEM 1040
#define MAX_ITEM_VETOR 46800
#define True 1
#define False 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    char naipe;
    int valor;
}Carta;

typedef int Apontador;

typedef struct{
    Carta carta[MAX_ITEM_VETOR];
    Apontador Topo;
    int quantidade_cartas;
}Baralho;

typedef struct{
    int valores[MAX_ITEM];
    int qValores;
}vExcluidos;

void criarBaralho(Baralho* pBaralho, int nBaralho, vExcluidos nExcluidos, Carta vBaralho[MAX_ITEM_VETOR]);
int Empilha(Baralho* pBaralho, Carta* carta, int nBaralho);
int Desempilha(Baralho* pBaralho, Carta* carta);
int quantidadeCartas(int nBaralho);
void criarPilha(Baralho* pBaralho);
void verificaTopoPilha(Baralho* pBaralho, Carta* carta);
int verificaPilhaVazia(Baralho* pBaralho);
int verificaGanhador(Baralho* pJogador, int mao, Carta cartaCoringa);
void imprimeCartas(Baralho* pJogador, int mao);
void descarteCarta(Baralho* pJogador, int mao, int iDescarte, Baralho* pDescarte, int nBaralho);
void imprimeCarta(Carta cartaAleatoria);
void tentativaJogo(Baralho* pBaralho, Baralho* pJogador, Baralho* pDescarte, int mao, int nBaralho);

//QUICKSORT
int ComparaCartas(Carta carta1, Carta carta2);
void Particao(int Esq, int Dir, int *i, int *j, Carta A[MAX_ITEM_VETOR]);
void Ordena(int Esq, int Dir, Carta A[MAX_ITEM_VETOR]);
void QuickSort(Carta A[MAX_ITEM_VETOR], int n);

//BUBBLESORT
void BubbleSort(Carta A[MAX_ITEM_VETOR], int n);
void SelectionSort(Carta A[MAX_ITEM_VETOR], int n);

#endif 