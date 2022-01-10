
#include "GrafoTAD.h"
#include "ArvMin.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

// Cria um novo no para a arvore
struct ArvMinNo* adicionarNoMin(int v, int chave)
{
	struct ArvMinNo* noArvMin = (struct ArvMinNo*)malloc(sizeof(struct ArvMinNo));
	noArvMin->v = v;
	noArvMin->peso = chave;
	return noArvMin;
}

// Cria a arvore
struct ArvMin* criarArvore(int cap)
{
	struct ArvMin* arvMin = (struct ArvMin*)malloc(sizeof(struct ArvMin));
	arvMin->pos = (int*)malloc(cap * sizeof(int));
	arvMin->tam = 0;
	arvMin->cap = cap;
	arvMin->array = (struct ArvMinNo**)malloc(cap * sizeof(struct ArvMinNo*));
	return arvMin;
}

// Troca dois nos de lugar na arvore
void trocarNos(struct ArvMinNo** a, struct ArvMinNo** b)
{
	struct ArvMinNo* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct ArvMin* arvMin, int i)
{
	int menor, esq, dir;
	menor = i;
	esq = 2 * i + 1;
	dir = 2 * i + 2;

	if (esq < arvMin->tam && arvMin->array[esq]->peso < arvMin->array[menor]->peso)
		menor = esq;

	if (dir < arvMin->tam && arvMin->array[dir]->peso < arvMin->array[menor]->peso)
		menor = dir;

	if (menor != i) {

		// Os nos precisarao trocar de lugar na arvore
		ArvMinNo* menorNo = arvMin->array[menor];
		ArvMinNo* indexNo = arvMin->array[i];

		// trocar posicoes
		arvMin->pos[menorNo->v] = i;
		arvMin->pos[indexNo->v] = menor;

		// troca os nos de lugar
		trocarNos(&arvMin->array[menor], &arvMin->array[i]);

		minHeapify(arvMin, menor);
	}
}

//checa se a arvore esta vazia
int estaVazio(struct ArvMin* arvMin)
{
	return arvMin->tam == 0;
}


struct ArvMinNo* extrairMin(struct ArvMin* arvMin)
{
	if (estaVazio(arvMin))
		return NULL;

	// guarda o no raiz
	struct ArvMinNo* raiz = arvMin->array[0];

	// Substitui o no raiz com o ultimo
	struct ArvMinNo* ultNo = arvMin->array[arvMin->tam- 1];
	arvMin->array[0] = ultNo;

	// atualiza posicao do ultimo no
	arvMin->pos[raiz->v] = arvMin->tam - 1;
	arvMin->pos[ultNo->v] = 0;

	// reduz tamanho da raiz
	--arvMin->tam;
	minHeapify(arvMin, 0);

	return raiz;
}


void decrementarChave(struct ArvMin* arvMin, int v, int chave)
{
	// Pega a posicao do vertice no array da arvore
	int i = arvMin->pos[v];

	// atualiza o peso do no
	arvMin->array[i]->peso = chave;
	
	while (i && arvMin->array[i]->peso < arvMin->array[(i - 1) / 2]->peso) {
		
		// troca no com o pai
		arvMin->pos[arvMin->array[i]->v] = (i - 1) / 2;
		arvMin->pos[arvMin->array[(i - 1) / 2]->v] = i;
		trocarNos(&arvMin->array[i], &arvMin->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

//chega se um vertice esta na arvore
bool estaNaArvore(struct ArvMin* arvMin, int v)
{
	if (arvMin->pos[v] < arvMin->tam)
		return true;
	return false;
}

// Imprime a AGM
void imprimirAGM(Voos* voos,int arr[],int posVoos[])
{
	int k = 0;

	cout << "\n-----------------------------------------------";
	cout << "\n Resultado da otimizacao dos percursos \n";
		for (int i = 1; i < voos->qtdV; ++i) {
							
			printf("%s -> %s ", voos->v[arr[i]].aero, voos->v[i].aero);

			struct arestaVoo* voosAdj = voos->v[arr[i]].cab;
			k = 0;
			while (voosAdj) { //procurando a menor viagem que esta na 
							// arvore com a posicao guardada da mesma

				if (k == posVoos[i]) {
					
					printf("%s %dkm %.2lf horas",voosAdj->empresaAero, voosAdj->distancia, voosAdj->TempoViagem);
					break;
				}
				
				k++;
				voosAdj = voosAdj->prox;
			}
			cout << "\n";

		}

	cout << "\n-----------------------------------------------";
}
