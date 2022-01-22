
#include "GrafoTAD.h"
#include <iostream>
#include <stdio.h>
#include <climits>

int MENU();

using namespace std;

int main() {
       
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

                            cout << "\nRota de " << rotas->vr[op1 - 1].aero << " pra " << rotas->vr[op2 - 1].aero << endl << endl;
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

                        mostrarVoos(op - 1, voos,rotas);
                        break;
                    }
                }
                break;
            }
            case 4: //Consultar viagem de menor custo
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
                                                        
                               mostrarMenorRota(voos, op1 - 1, op2 - 1);
                                            

                            break;

                        }

                    }

                }


                break; 
            }
            case 5: //checar se a partir de um aeroporto é possivel alcançar outro
            {
                int opAero;

                cout << "\n";
                mostrarAeroportos(rotas);
                cout << "\nSelecione o aeroporto a ser verificado : ";
                cin >> opAero;
                cin.ignore();

                if (opAero < 1 || opAero > 23)
                    cout << "\nOpcao incorreta !";
                else 
                     verificarAero(rotas,opAero - 1);
                                
                break;
            }
            case 6: //Gerar grafo otimizado
            {
                
                gerarGrafoOtimizado(voos);

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
        
    cout << "\nMENU";
    cout << "\n0- SAIR";
    cout << "\n1- Visualizar grafos de rotas e voos";
    cout << "\n2- Consultar disponibilidade de rota entre dois aeroportos";
    cout << "\n3- Exibir voos diretos a partir de um aeroporto";
    cout << "\n4- Consultar viagem de menor custo";
    cout << "\n5- Checar possibilidade de chegada de um aeroporto para todos os outros";
    cout << "\n6- Gerar grafo otimizado";
    cout << "\nDigite a opcao desejada: ";
    cin >> op;
    cin.ignore();

    return op;

}
