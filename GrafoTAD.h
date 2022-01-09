#pragma once

#ifndef GRAFO_H
#define GRAFO_H


//grafo rotas

#include <string>

struct arestaRota {
    char aero[4];
    struct arestaRota* prox;

};

typedef struct {
    char aero[4];
    char* aeroNome;
    struct arestaRota* cab,*ultimo;

} VerticeRotas;

typedef struct {
    int qtdR;
    VerticeRotas* vr;

} Rotas;

//grafo Voos

struct arestaVoo {
    char empresaAero[3];
    char aero[4];
    char* aeroNome;
    int distancia;
    double TempoViagem;
    struct arestaVoo* prox;
};

typedef struct {
   
    char aero[4];
    char* aeroNome;
    struct arestaVoo* cab, *ultimo;

} VerticeVoos;

typedef struct {

    int qtdV;
    VerticeVoos* v;

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
void mostrarVoos(int aero, Voos* voos);

//Questao 5
void mostrarMenorRota(Voos* voos, int aeroOrigem, int aeroDestino, int OpAv);
void atualizaAresta(Voos* voos, int* vetPesos, double* vetPesosFloat, int* vetPredecessores, int vMenor, int vAtual);
int menorDist(Voos* voos, bool* aberto, int* vetPesos);
int menorTempo(Voos* voos, bool* aberto, double* vetPesos);
bool existeAberto(Voos* voos, bool* aberto);

//Questao 6
void verificarAero(Rotas* rotas, int opAero);

//Questao 7
void gerarGrafoOtimizado(Voos* voos);

#endif /* GRAFO_H */

