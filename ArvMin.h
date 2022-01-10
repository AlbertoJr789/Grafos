#pragma once

// Estrutura do menor no da arvore
struct ArvMinNo {
	int v;
	int peso;
};

// Structure para representar a arvore
struct ArvMin {
	int tam; // Quantidade de nos presentes	
	int cap; // Capacidade da Arvore
	int* pos; // Posicao (Necessario para a funcao de decremento)
	struct ArvMinNo** array;
};

struct ArvMinNo* adicionarNoMin(int v, int chave);
struct ArvMin* criarArvore(int cap);
void trocarNos(struct ArvMinNo** a, struct ArvMinNo** b);
void minHeapify(struct ArvMin* arvMin, int i);
int estaVazio(struct ArvMin* arvMin);
struct ArvMinNo* extrairMin(struct ArvMin* arvMin);
void decrementarChave(struct ArvMin* arvMin, int v, int chave);
bool estaNaArvore(struct ArvMin*   arvMin, int v);
void imprimirAGM(Voos* voos, int array[],int posVoos[]);