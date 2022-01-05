

#include "GrafoTAD.h"
#include <iostream>
#include <stdio.h>
#include <climits>

void dormir();
int MENU();

using namespace std;

int main() {

   

    // grafo de voos : dirigido 780 VOOS

    // verificar se de um aeroporto para o outro tem um caminho direto
    // se nao, verificar a rota alternativa
    // o grafo nao é hamiltoniano
    // 6 - Algoritmo de Kruskal  
    
    // Considerações : alguns horarios de chegada/entrada aparentam incorretos ??
    // DL1166  ATL  632A  BNA  625A


    Rotas* rotas = NULL;
    Voos* voos = NULL;

    cout << "\nLendo os dados..." << endl;
    //dormir();

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

void dormir() {

    for (int i = 0; i < INT_MAX; i++);

}