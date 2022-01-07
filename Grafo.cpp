

#include "GrafoTAD.h"
#include <iostream>
#include <stdio.h>
#include <climits>


int MENU();

using namespace std;

int main() {
               
    // verificar se de um aeroporto para o outro tem um caminho direto
    // se nao, verificar a rota alternativa
    // o grafo nao é hamiltoniano
    // 6 - Algoritmo de Kruskal  
    
    // DFS - Biziu na hora de desempilhar imprimi rota que deu errado
    // Considerações : alguns horarios de chegada/entrada aparentam incorretos ??
    // DL1166  ATL  632A  BNA  625A

    Rotas* rotas = NULL;
    Voos* voos = NULL;
         
    if (lerArquivo(&voos, &rotas)) { //se conseguir ler o arquivo, acionar o MENU

        while (1) {

            int op = MENU();

            if (!op) {

                cout << "\nPrograma finalizado";
                break;

            }

            switch (op) {

            case 1: //mostrar grafos
            {

                mostrarGrafo(rotas, voos);

                break;
            } 
            case 2: //Consultar disponibilidade de rota entre dois aeroportos
            {
                int op1 = 0, op2 = 0;
                                                                
                while (1) {

                    cout << "\n";
                    mostrarAeroportos(rotas);
                    cout << "\nSelecione o primeiro aeroporto desejado: ";
                    cin >> op1;
                    cin.ignore();

                    if (op1 < 1 || op1 > 23)
                        cout << "\nOpcao incorreta !";
                    else {
                        cout << "\n";
                        mostrarAeroportos(rotas);
                        cout << "\nSelecione o segundo aeroporto desejado: ";
                        cin >> op2;
                        cin.ignore();

                        if ((op2 == op1) || (op2 < 1 || op2 > 23))
                            cout << "\nOpcao Incorreta ! O segundo aeroporto deve ser diferente ou a opcao selecionada nao existe !";
                        else {

                            cout << "\nRotas entre " << rotas->vr[op1 - 1].aero << " e " << rotas->vr[op2 - 1].aero << endl;
                            mostrarCaminho(rotas,op1-1, op2-1);
                      
                            break;

                        }
                    
                    }

                }


                break;
            }
            case 3: //Exibir voos diretos a partir de um aeroporto
            {
                int op = 0;
                while (1) {
                    
                    cout << "\n";
                    mostrarAeroportos(rotas);
                    cout << "\nSelecione o aeroporto desejado: ";
                    cin >> op;
                    cin.ignore();

                    if (op < 1 || op > 23)
                        cout << "\nOpcao incorreta !";
                    else {

                        mostrarVoos(op - 1, voos);
                        break;
                    }
                }
                break;
            }
            case 4: //Consultar viagem de menor custo
            {
                break; 
            }
            case 5: //Gerar grafo otimizado
            {
                break;
            }
            case 6: //Verificar tempo de voo minimo de um aeroporto para os outros
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
    cout << "\n2- Consultar disponibilidade de rota entre dois aeroportos";
    cout << "\n3- Exibir voos diretos a partir de um aeroporto";
    cout << "\n4- Consultar viagem de menor custo";
    cout << "\n5- Gerar grafo otimizado";
    cout << "\n6- Verificar tempo de voo minimo de um aeroporto para os outros";
    cout << "\nDigite a opcao desejada: ";
    cin >> op;
    cin.ignore();
    cout << "\n-----------------------------";

    return op;

}
