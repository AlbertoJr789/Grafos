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
    int distancia;
    double TempoViagem;
    struct arestaVoo* prox;
};

typedef struct {
   
    char aero[4];
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
int obterDistancia(std::string charLinha);
int buscarAeroOrigem(Voos* v, char* aeroOrigem);

#endif /* GRAFO_H */

