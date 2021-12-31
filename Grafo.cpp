

#include "GrafoTAD.h"
#include <iostream>
#include <stdio.h>
#include <climits>

void sleep();
int MENU();

using namespace std;

int main() {

    // 23 aeroportos
    // grafo de rotas : nao dirigido 57 ROTAS
    // grafo de voos : dirigido 780 VOOS
    //arquivo : tirar comida
    // verificar se de um aeroporto para o outro tem um caminho direto
    // se nao, verificar a rota alternativa
    // o grafo nao é hamiltoniano
    // 6 - Algoritmo de Kruskal  


    Rotas* rotas = NULL;
    Voos* voos = NULL;

    cout << "\nLendo os dados..." << endl;
    //sleep();

    if (lerArquivo(&voos, &rotas)) { //se conseguir ler o arquivo, acionar o MENU

        while (1) {

            int op = MENU();

            if (!op) {

                cout << "\nPrograma finalizado";
                break;

            }

            switch (op) {

            case 1:
            {

                mostrarGrafo(rotas, voos);

                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            case 4:
            {
                break;
            }
            case 5:
            {
                break;
            }
            case 6:
            {
                break;
            }
            default:
            {
                cout << "\nOpcao incorreta !";
                break;
            }

            }

        }

    }
    else
        exit(EXIT_FAILURE);



    exit(EXIT_SUCCESS);
}

int MENU() {

    int op;

    cout << "\n-----------------------------";
    cout << "\nMENU";
    cout << "\n0- SAIR";
    cout << "\n1- Visualizar grafos de rotas e voos";
    cout << "\n2- Exibir voos a partir de um aeroporto";
    cout << "\n3- Consultar viagem de menor custo";
    cout << "\n4- Consultar disponibilidade de rota entre dois aeroportos";
    cout << "\n5- Gerar grafo otimizado";
    cout << "\n6- Verificar tempo de voo minimo de um aeroporto para os outros";
    cout << "\nDigite a opcao desejada: ";
    cin >> op;
    cin.ignore();
    cout << "\n-----------------------------";

    return op;

}

void sleep() {

    for (int i = 0; i < INT_MAX; i++);

}