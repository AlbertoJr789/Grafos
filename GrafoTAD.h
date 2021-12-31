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
    int duracaoVoo;
    struct arestaVoo* prox;
};

typedef struct {
    char empresaAero[3];
    char aero[4];
    struct arestaVoo* cab;

} VerticeVoos;

typedef struct {

    int qtdV;
    VerticeVoos* v;

} Voos;



bool lerArquivo(Voos** voos, Rotas** rotas);
void mostrarGrafo(Rotas* rotas, Voos* voos);
void criarGrafos(Voos** voos, Rotas** rotas);
void adicionarRota(Rotas** rotas, int pos, char* Origem, char* Destino);
#endif /* GRAFO_H */

