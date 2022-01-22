#pragma once

#ifndef GRAFO_H
#define GRAFO_H



#include <string>

//grafo rotas
struct arestaRota { // arestas/ligacoes do grafo
    char aero[4]; //abreviatura do aeroporto
    struct arestaRota* prox; //proxima rota

};

typedef struct { //vertices do grafo
    char aero[4]; //abreviatura do aeroporto
    char* aeroNome; //nome do aeroporto
    struct arestaRota* cab,*ultimo; //ponteiros da lista ligada de arestas 

} VerticeRotas;

typedef struct { //estrutura geral do grafo
    int qtdR; //quantidade de Rotas
    VerticeRotas* vr; // contem os vertices, que contem as arestas

} Rotas;

//grafo Voos
struct arestaVoo {
    char empresaAero[3]; //Guarda a empresa do voo
    char aero[4]; //abreviatura do aeroporto de destino
    char* aeroNome; //nome do aeroporto de destino
    int distancia; //distancia em kilometros
    double TempoViagem; //tempo de viagem em horas decimais
    struct arestaVoo* prox; //proximo voo pertencente ao vertice de origem
};

typedef struct {
   
    char aero[4]; //abreviatura do aeroporto de origem
    char* aeroNome;//nome do aeroporto de origem
    struct arestaVoo* cab, *ultimo; //ponteiros da lista ligada de arestas (Voos)

} VerticeVoos;

typedef struct {

    int qtdV; //quantidade de Voos
    VerticeVoos* v; // contem os vertices, que contem as arestas

} Voos;

//leitura do arquivo
bool lerArquivo(Voos** voos, Rotas** rotas);

//Operações com grafos
void mostrarGrafo(Rotas* rotas, Voos* voos);
void criarGrafos(Voos** voos, Rotas** rotas);
void adicionarRota(Rotas** rotas, int pos, char* Origem, char* Destino);
void adicionarVoo(Voos** voos, char* empresaAero, char* aeroOrigem, char* aeroDestino, double tempo, int distancia);

//Funções auxiliares
char* obterAeroDestino(std::string charLinha);
char* obterAeroOrigem(std::string charLinha);
char* obterNomeAero(Voos* voos,char* aero);
int obterDistancia(std::string charLinha);
int buscarAeroOrigem(Voos* v, char* aeroOrigem);

//Questao 3-b)
void mostrarAeroportos(Rotas* rotas);
void mostrarCaminho(Rotas* rotas, int aero1, int aero2);
void DFSRotas(Rotas* rotas, bool* visitados, int aeroOriginal, int aero1, int aero2, bool* jaAchou);
int posicaoRota(Rotas* rotas, char* aero);

//Questao 4
void mostrarVoos(int aero, Voos* voos,Rotas* rotas);

//Questao 5
void imprimirMenorRota(Voos* voos, double* tempo,int* posVoos, int* pai, int aeroOrigem, int aeroDestino);
void mostrarMenorRota(Voos* voos, int aeroOrigem, int aeroDestino);
int menorTempo(Voos* voos, double* tempo, bool* visitados);
bool temAberto(Voos* voos, bool* visitados);

//Questao 6
void verificarAero(Rotas* rotas, int opAero);

//Questao 7
void gerarGrafoOtimizado(Voos* voos);

#endif /* GRAFO_H */

