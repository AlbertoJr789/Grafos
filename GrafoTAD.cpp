

#include "GrafoTAD.h"
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

bool lerArquivo(Voos** voos, Rotas** rotas) {


	ifstream Arquivo;
	string linha;

	Arquivo.open("Flights_USA.txt");

	if (Arquivo.is_open()) {

		cout << "\nLeitura realizada com sucesso !";
		criarGrafos(voos, rotas);

		int contLinha = 0;
		//controla o vertice das rotas
		int posAero = 0;
		//controla o vertice dos voos
		int posVoos = 0;

		while (getline(Arquivo, linha)) { //lendo os dados

			int p = 0;

			if (contLinha < 23) { //as primeiras 23 linhas possuem os aeroportos

				char* charLinha = new char[linha.length()];

				strcpy(charLinha, linha.c_str());

				//atribuindo os dados ao grafo
				strncpy((*rotas)->vr[posAero].aero, charLinha, 3);
				(*rotas)->vr[posAero].aero[3] = '\0';

				int tamAeroNome = strlen(charLinha) - 4;

				(*rotas)->vr[posAero].aeroNome = (char*)calloc((tamAeroNome + 1), sizeof(char));
				(*rotas)->vr[posAero].aeroNome[strlen((*rotas)->vr[posAero].aeroNome)] = '\0';

				for (int i = 4; i < strlen(charLinha); i++) {

					(*rotas)->vr[posAero].aeroNome[p] = charLinha[i];
					p++;
				}

				posAero++; //proximo aeroporto
			}
			else if (contLinha >= 23 && contLinha < 57) { //leitura das rotas

				char* charLinha = new char[linha.length()];
				strcpy(charLinha, linha.c_str());
				int posOrigem = 0, posDestino = 0 ;

				char* Origem = NULL;
				char* Destino = NULL;

				//obtendo rota de origem 
				Origem = strtok(charLinha, " ");
				//obtendo rota de destino
				Destino = strtok(NULL, " ");
												
				for (int i = 0; i < (*rotas)->qtdR; i++) {

					//procurando a posição do vértice de origem
					if (!strcmp((*rotas)->vr[i].aero, Origem))
						posOrigem = i;
					//procurando a posição do vértice de destino
					if (!strcmp((*rotas)->vr[i].aero, Destino))
						posDestino = i;

				}

				//adicionando a rota (de forma não direcionada)
				adicionarRota(rotas,posOrigem,Origem,Destino);
				adicionarRota(rotas,posDestino,Destino,Origem);

			}
			else { //leitura dos voos

				char* charLinha = new char[linha.length()];
				strcpy(charLinha, linha.c_str());

				//obtendo o nome da Companhia Aerea
				strncpy((*voos)->v[posVoos].empresaAero, charLinha, 2);
				(*voos)->v[posVoos].empresaAero[3] = '\0';

				char* charKm = (char*)calloc(6,sizeof(char));
				int k = 0,i=0;

				for (i = 2; i < 6; i++) {

					//obtendo os dados da distancia
					if (charLinha[i] != ' ') { //achou um numero

					charKm[k] = charLinha[i];
					k++;

					}

				}

				int Km = atoi(charKm);
				
				k = 0;

				for(i = 8;i < 11;i++) //obtendo o aeroporto de origem
					(*voos)->v[posVoos].aero[k] = charLinha[i];
					
				(*voos)->v[posVoos].aero[3] = '\0';
				
				// 12 a 16 - horario de entrada
				// 18 a 21 - aeroporto destino
				// 22 a 27 - horario de chegada

				
				
				posVoos++;
			}

			contLinha++; //proxima linha
			
		}

	}
	else {

		cout << "\nErro ao ler os voos,verifique o arquivo";
		return false;
	}

	return true;

}

void mostrarGrafo(Rotas* rotas, Voos* voos) {

	if (rotas) {

		cout << "\n-------------------------------------";
		cout << "\nROTAS DO AEROPORTO";

		for (int i = 0; i < rotas->qtdR; i++) { //percorrendo os aeroportos

			cout << "\n";
			//printf("%s(%s) ", rotas->vr[i].aero, rotas->vr[i].aeroNome);
			printf("%s ", rotas->vr[i].aero);
			arestaRota* rotasAdj = rotas->vr[i].cab;

			while (rotasAdj) { //percorrendo as rotas que um aeroporto tem pra outros

				cout << "-> ";
				printf("%s", rotasAdj->aero);
				rotasAdj = rotasAdj->prox;
			}

		}

		cout << "\n-------------------------------------";
	}
	else
		cout << "\nGrafo de rotas inexistente !";

	if (voos) {




	}
	else
		cout << "\nGrafo de voos inexistente !";

}

void criarGrafos(Voos** voos, Rotas** rotas) {

	(*rotas) = (Rotas*)malloc(sizeof(Rotas));

	if ((*rotas)) {

		(*rotas)->qtdR = 23; //quantidade de vertices (sao 23 aeroportos)
		(*rotas)->vr = (VerticeRotas*)malloc((*rotas)->qtdR * sizeof(VerticeRotas));

		for (int i = 0; i < (*rotas)->qtdR; i++) { //inicializando os valores

			(*rotas)->vr[i].cab = NULL;
			(*rotas)->vr[i].aeroNome = NULL;

		}
	}
	else
		cout << "\nErro ao alocar rotas";

	(*voos) = (Voos*)malloc(sizeof(Voos));

	if ((*voos)) {

		(*voos)->qtdV = 780; //quantidade de vertices (sao 780 voos)
		(*voos)->v = (VerticeVoos*)malloc((*voos)->qtdV * sizeof(VerticeVoos));
		for (int i = 0; i < (*voos)->qtdV; i++) { //inicializando os valores

			(*voos)->v[i].cab = NULL;

		}

	}
	else
		cout << "\nErro ao alocar voos";


}

void adicionarRota(Rotas** rotas, int pos, char* Origem,char* Destino) {

	//criando a aresta
	struct arestaRota* novo = (struct arestaRota*)malloc(sizeof(struct arestaRota));
	strcpy(novo->aero,Destino);
	novo->prox = NULL;

	if (!(*rotas)->vr[pos].cab) { //se o vertice nao possuir nenhuma aresta

		(*rotas)->vr[pos].cab = novo; //esta aresta sera definida como a primeira
		(*rotas)->vr[pos].ultimo = novo; //ele tambem sera o ultimo elemento da lista

	} 
	else { //se nao, sera inserida no final

	(*rotas)->vr[pos].ultimo->prox = novo;
	(*rotas)->vr[pos].ultimo = novo;

	}
				


}

