

#include "GrafoTAD.h"
#include "HoraUtil.h"
#include "ArvMin.h"

#include <cstdlib>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

//Leitura dos Grafos

bool lerArquivo(Voos** voos, Rotas** rotas) {

	ifstream Arquivo;
	string linha;

	Arquivo.open("Flights_USA.txt");

	if (Arquivo.is_open()) {

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

				//atribuindo os dados ao grafo de rotas 
				strncpy((*rotas)->vr[posAero].aero, charLinha, 3);
				(*rotas)->vr[posAero].aero[3] = '\0';

				//atribuindo os dados ao grafo de voos
				strncpy((*voos)->v[posAero].aero, charLinha, 3);
				(*voos)->v[posAero].aero[3] = '\0';

				//obtendo o tamanho do nome do aeroporto
				int tamAeroNome = strlen(charLinha) - 4;

				//alocando string do tamanho do nome do aeroporto
				(*rotas)->vr[posAero].aeroNome = (char*)calloc((tamAeroNome + 1), sizeof(char));
				(*rotas)->vr[posAero].aeroNome[strlen((*rotas)->vr[posAero].aeroNome)] = '\0';
				
				(*voos)->v[posAero].aeroNome = (char*)calloc((tamAeroNome + 1), sizeof(char));
				(*voos)->v[posAero].aeroNome[strlen((*rotas)->vr[posAero].aeroNome)] = '\0';

				for (int i = 4; i < strlen(charLinha); i++) { //copiando o nome do aeroporto

					(*rotas)->vr[posAero].aeroNome[p] = charLinha[i];
					(*voos)->v[posAero].aeroNome[p] = charLinha[i];
					p++;
				}

				posAero++; //proximo aeroporto
			}
			else if (contLinha >= 23 && contLinha < 57) { //leitura das rotas

				char* charLinha = new char[linha.length()];
				strcpy(charLinha, linha.c_str());
				int posOrigem = 0, posDestino = 0 ;

				//obtendo rota de origem 
				char* Origem = strtok(charLinha, " ");
				//obtendo rota de destino
				char* Destino = strtok(NULL, " ");
																
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
				char empresaAero[3];
				empresaAero[0] = charLinha[0];
				empresaAero[1] = charLinha[1];
				empresaAero[2] = '\0';

				int distancia = obterDistancia(charLinha); 
				char* aeroOrigem = obterAeroOrigem(charLinha);
								
				//obtendo hora de entrada e chegada
				Hora horaEntrada,horaChegada;
				horaEntrada.entrada = true; // esta sendo coletado a hora de entrada
				horaChegada.chegada = true; // esta sendo coletado a hora de chegada
				
				obterHora(&horaEntrada,charLinha);
				obterHora(&horaChegada,charLinha);
								
				char* aeroDestino = obterAeroDestino(charLinha);
				double tempo = obterTempoViagem(horaChegada, horaEntrada);

				adicionarVoo(voos, empresaAero,aeroOrigem,aeroDestino, tempo, distancia);
						

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
			struct arestaRota* rotasAdj = rotas->vr[i].cab;

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


		cout << "\n-------------------------------------";
		cout << "\nVOOS DO AEROPORTO";

		for (int i = 0; i < voos->qtdV; i++) { //percorrendo os aeroportos
			cout << "\n-------------------------------------";
			cout << "\n";
			//printf("%s(%s) ", rotas->vr[i].aero, rotas->vr[i].aeroNome);
			printf("AERO ORIGEM: %s ", voos->v[i].aero);
			struct arestaVoo* voosAdj = voos->v[i].cab;

			while (voosAdj) { //percorrendo os voos que um aeroporto tem pra outros

				cout << " -> |";
				printf(" %s", voosAdj->aero);
				printf(" %s", voosAdj->empresaAero);
				printf(" %dkm", voosAdj->distancia);
				printf(" %.2lf horas|", voosAdj->TempoViagem);
				
				voosAdj = voosAdj->prox;
			}
			cout << "\n-------------------------------------";
		}

		cout << "\n-------------------------------------";
					
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

		(*voos)->qtdV = 23; //quantidade de vertices (sao 723 voos)
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

void adicionarVoo(Voos** voos, char* empresaAero, char* aeroOrigem, char* aeroDestino, double tempo, int distancia) {

	//obtem a posicao do aeroporto de origem para realizar a insercao na lista
	int pos = buscarAeroOrigem((*voos),aeroOrigem);

	//criando a aresta, adicionando os dados
	struct arestaVoo* novo = (struct arestaVoo*)malloc(sizeof(struct arestaVoo));
	strcpy(novo->aero, aeroDestino);
	strcpy(novo->empresaAero, empresaAero);
	novo->aeroNome = obterNomeAero((*voos),aeroDestino);
	novo->distancia = distancia;
	novo->TempoViagem = tempo;
	novo->prox = NULL;

	if (!(*voos)->v[pos].cab) { //se o vertice nao possuir nenhuma aresta

		(*voos)->v[pos].cab = novo; //esta aresta sera definida como a primeira
		(*voos)->v[pos].ultimo = novo; //ele tambem sera o ultimo elemento da lista

	}
	else { //se nao, sera inserida no final

		(*voos)->v[pos].ultimo->prox = novo;
		(*voos)->v[pos].ultimo = novo;

	}

}

//Funcoes auxiliares ---------------------------------------------------------

char* obterAeroDestino(std::string charLinha) {

	int k = 0;
	char* aero = (char*)calloc(4,sizeof(char));

	//obtem o aeroporto de destino
	for (int i = 19; i < 22; i++) {

		aero[k] = charLinha[i];
		k++;
	}

	aero[3] = '\0';
		
	return aero;
}

char* obterAeroOrigem(std::string charLinha) {

	int k = 0;
	char* aero = (char*)calloc(4, sizeof(char));

	//obtem o aeroporto de destino
	for (int i = 8; i < 11; i++) {

		aero[k] = charLinha[i];
		k++;
	}

	aero[3] = '\0';

	return aero;
}

char* obterNomeAero(Voos* voos,char* aero) {

	for (int i = 0; i < voos->qtdV; i++) { //procura o nome do aeroporto desejado e retorna

		if (!strcmp(voos->v[i].aero, aero))
			return voos->v[i].aeroNome;
	}

}

int obterDistancia(std::string charLinha) {

	char* charKm = (char*)calloc(6, sizeof(char));
	int k = 0, i = 0;

	for (i = 2; i < 6; i++) {

		//obtendo os dados da distancia
		if (charLinha[i] != ' ') { //caso atender a condicao, signicia achou um numero

			charKm[k] = charLinha[i];
			k++;

		}

	}
	
	return atoi(charKm);

}

int buscarAeroOrigem(Voos* v,char* aeroOrigem) {

	for (int i = 0; i < v->qtdV; i++) {

		if (!strcmp(v->v[i].aero, aeroOrigem))
			return i;

	}

}

//Questao 3-b)

void mostrarAeroportos(Rotas* rotas) {


	for (int i = 0; i < rotas->qtdR; i++) 
		cout << i + 1 << "- " << rotas->vr[i].aero << "(" << rotas->vr[i].aeroNome << ")" << endl;
			
}

void mostrarCaminho(Rotas* rotas, int aero1, int aero2) {
	
	struct arestaRota* rotasAdj = rotas->vr[aero1].cab;

	while (rotasAdj) { //procurando algum caminho direto

		if (posicaoRota(rotas, rotasAdj->aero) == aero2) { //significa que ha um caminho direto
			printf("Origem : %s -> %s (Destino)", rotas->vr[aero1].aero, rotasAdj->aero);
			return;
		}

		rotasAdj = rotasAdj->prox;
	}

	if (!rotasAdj) { //procurar uma rota alternativa 

		//inicializa o vetor de adjacencias visitadas em falso
		bool* visitados = (bool*)calloc(rotas->qtdR, sizeof(bool));
		bool jaAchou = false;

		//Algoritmo de busca em profundidade 
		DFSRotas(rotas, visitados, aero1, aero1, aero2, &jaAchou);
		
	}

	
}

void DFSRotas(Rotas* rotas,bool* visitados,int aeroOriginal,int aero1,int aero2,bool* jaAchou) {

	int i = 0;

	struct arestaRota* rotasAdj = rotas->vr[aero1].cab;

	visitados[aero1] = true;
	
	if(aero1 == aeroOriginal)
		printf("%s(Origem) -> ", rotas->vr[aeroOriginal].aero);

	while (rotasAdj && strcmp(rotasAdj->aero,rotas->vr[aero2].aero)) //percorre as adjacencias em busca do aeroporto de destino
	{
		i = posicaoRota(rotas, rotasAdj->aero); //pesquisa a posicao do vertice a partir do nome
		
		if (!visitados[i] && !*jaAchou) {	//caso o vertice ja nao tenha sido visitado e a rota nao tenha sido encontrada
											
			printf("%s -> ", rotasAdj->aero); //imprimi-lo
			DFSRotas(rotas,visitados,aeroOriginal, i, aero2,jaAchou); //o mesmo sera visitado e suas adjacencias tambem
			
		}
		rotasAdj = rotasAdj->prox;
	}

	if (rotasAdj) { 

		if (!strcmp(rotasAdj->aero, rotas->vr[aero2].aero) && !*jaAchou) { //caso a rota adjacente seja a rota de destino

			cout << rotas->vr[aero2].aero << "(Destino)";
			*jaAchou = true; //marca-la como encontrada
			
		}
	} 
		
}

int posicaoRota(Rotas* rotas, char* aero) {

	for (int i = 0; i < rotas->qtdR; i++) { 

		if (!strcmp(aero, rotas->vr[i].aero)) //devolve o indice do vertice que tem o aeroporto desejado
			return i;

	}

}

//Questao 4

void mostrarVoos(int aero, Voos* voos) {

	struct arestaVoo* voosAdj = voos->v[aero].cab;

	cout << "\nVoos disponiveis em " << voos->v[aero].aeroNome;

	while (voosAdj) {
		
		cout << "\n-------------------------------------------";
		printf("\nEmpresa: %s", voosAdj->empresaAero);
		printf("\nDestino : %s(%s)", voosAdj->aero,voosAdj->aeroNome);
		printf("\nDistancia:  %dkm", voosAdj->distancia);
		printf("\nTempo de viagem:  %.2lf horas", voosAdj->TempoViagem);
		cout << "\n-------------------------------------------";

		voosAdj = voosAdj->prox;
	}


}

//Questao 5 

void mostrarMenorRota(Voos* voos, int aeroOrigem, int aeroDestino, int OpAv) {
		

	if (OpAv == 1) { //avaliar por tempo total de viagem

		double* vetPesos = (double*)malloc(voos->qtdV * sizeof(double));
		int* vetPredecessores = (int*)malloc(voos->qtdV * sizeof(int));
		bool* aberto = (bool*)malloc(voos->qtdV * sizeof(bool));

		//DIJKSTRA 
		for (int i = 0; i < voos->qtdV; i++) {//inicializando o vetor com um valor inteiro grande

			vetPesos[i] = LONG_MAX / 2;
			vetPredecessores[i] = -1; //o vetor de predecessores nao possui nenhum vertice registrado ainda
			aberto[i] = true; //todos os vertices estao abertos para visita 
		}

		vetPesos[aeroOrigem] = 0.0; //inicializando o valor do aeroporto de Origem em zero (seja tempo de viagem ou distancia)

		int posMenor = -1;

		printf("Origem: %s ", voos->v[aeroOrigem].aero);

		while (existeAberto(voos, aberto)) {

			posMenor = menorTempo(voos, aberto, vetPesos);
			aberto[posMenor] = false;
			
			struct arestaVoo* voosAdj = voos->v[posMenor].cab;
			

			while (voosAdj && aberto[aeroDestino] ) { //relaxando as arestas
			
				int posAtual = buscarAeroOrigem(voos, voosAdj->aero);
				atualizaAresta(voos, NULL, vetPesos, vetPredecessores, posMenor, posAtual);
				voosAdj = voosAdj->prox;

			}

		}
		
	}
	else { // avaliar por tempo total de distancia

		int* vetPesos = (int*)malloc(voos->qtdV * sizeof(int));
		int* vetPredecessores = (int*)malloc(voos->qtdV * sizeof(int));
		bool* aberto = (bool*)malloc(voos->qtdV * sizeof(bool));

		//DIJKSTRA 
		for (int i = 0; i < voos->qtdV; i++) {//inicializando o vetor com um valor inteiro grande

			vetPesos[i] = INT_MAX / 2;
			vetPredecessores[i] = -1; //o vetor de predecessores nao possui nenhum vertice registrado ainda
			aberto[i] = true; //todos os vertices estao abertos para visita 
		}
		
		//inicializando o valor do aeroporto de Origem em zero (seja tempo de viagem ou distancia)
		vetPesos[aeroOrigem] = 0; 
		int posMenor = -1;

		printf("\nOrigem: %s ", voos->v[aeroOrigem].aero);

		while (existeAberto(voos, aberto)) {

			posMenor = menorDist(voos, aberto, vetPesos);
			aberto[posMenor] = false;
			
			struct arestaVoo* voosAdj = voos->v[posMenor].cab;
			//printf(" -> %s", voosAdj->aero);

			while (voosAdj && aberto[aeroDestino]) { //relaxando as arestas

				int posAtual = buscarAeroOrigem(voos, voosAdj->aero);
				atualizaAresta(voos, vetPesos, NULL, vetPredecessores, posMenor, posAtual);
				voosAdj = voosAdj->prox;

			}

		}
		


	}
}

bool existeAberto(Voos* voos,bool* aberto) {

	//confirma se tem algum vertice aberto para verificacao
	for (int i = 0; i < voos->qtdV; i++) 
		if (aberto[i]) return true;
		
	return false;

}

int menorTempo(Voos* voos, bool* aberto, double* vetPesos) {

	int i = 0;

	for (i = 0; i < voos->qtdV; i++)
		if (aberto[i]) break;

	if (i == voos->qtdV) return -1;

	int menor = i;

	for (i = menor + 1; i < voos->qtdV; i++)
		if (aberto[i] && (vetPesos[menor] > vetPesos[i]))
			menor = i;

	return menor;

}

int menorDist(Voos* voos,bool* aberto,int* vetPesos) {

	int i = 0;

	for (i = 0; i < voos->qtdV; i++) 
		 if (aberto[i]) break;

	if (i == voos->qtdV) return -1;

	int menor = i;

	for (i = menor + 1; i < voos->qtdV; i++)
		if (aberto[i] && (vetPesos[menor] > vetPesos[i]))
			menor = i;

	return menor;

}

void atualizaAresta(Voos* voos, int* vetPesos, double* vetPesosFloat, int* vetPredecessores,int vMenor,int vAtual) {
	
	struct arestaVoo* voosAdj = voos->v[vMenor].cab;

	if (vetPesos) { //arestas de distancia

		while (voosAdj && (buscarAeroOrigem(voos, voosAdj->aero) != vAtual))
				voosAdj = voosAdj->prox;

		if (voosAdj) {

			if (vetPesos[vAtual] > vetPesos[vMenor] + voosAdj->distancia) {
				
				vetPesos[vAtual] = vetPesos[vMenor] + voosAdj->distancia;
				vetPredecessores[vAtual] = vMenor;
			}

		}

	}

	if (vetPesosFloat) { //arestas de tempo de viagem

		//busca a adjacencia atual para ajuste das arestas
		while (voosAdj && (buscarAeroOrigem(voos, voosAdj->aero) != vAtual))
			voosAdj = voosAdj->prox;

		if (voosAdj) { //caso ela seja encontrada
			
			if (vetPesosFloat[vAtual] > vetPesosFloat[vMenor] + voosAdj->TempoViagem) {

				vetPesosFloat[vAtual] = vetPesosFloat[vMenor] + voosAdj->TempoViagem;
				vetPredecessores[vAtual] = vMenor;
			}

		}

	}

}

// Questao 6

void verificarAero(Rotas* rotas, int opAero) {
		
	struct arestaRota* aero = rotas->vr[opAero].cab;
	bool achou = false;

	for(int i=0; i < rotas->qtdR; i++){
		
		achou = false;
		arestaRota* aero = rotas->vr[opAero].cab;

		if(i!=opAero){ //nao sera verificado a disponibilidade de rota de um aeroporto para ele mesmo 

			cout << "\n";
			cout << "\n-------------------------------------------------\n";
			cout << rotas->vr[opAero].aero << "(" << rotas->vr[opAero].aeroNome << ")" << " para " 
				<< rotas->vr[i].aero << "(" << rotas->vr[i].aeroNome << ")" << "\n\n";

			while (aero) {
				
				if (posicaoRota(rotas, aero->aero) == i) { //procurando um caminho direto
					
					printf("%s possui uma rota direta com %s", rotas->vr[opAero].aero, aero->aero);
					achou = true;
			
				} 
			
				aero = aero->prox;
			}


			if (!achou) {

				cout << "\nNao foi possivel encontrar uma rota direta, eis a rota alternativa\n";

				//inicializa o vetor de adjacencias visitadas em falso
				bool* visitados = (bool*)calloc(rotas->qtdR, sizeof(bool));
				bool jaAchou = false;

				//Algoritmo de busca em profundidade 
				DFSRotas(rotas, visitados, opAero, opAero, i, &jaAchou);
			}
		
		
		cout << "\n-------------------------------------------------";
		}
	}


}

// Questao 7 

void gerarGrafoOtimizado(Voos* voos) {

	//Algoritmo de Prim
	//Utilizado para grafos mais densos (maior quantidade de arestas do que vertices)
	//Utiliza estrutura de dados lista
		
	int* pai = (int*)malloc(voos->qtdV * sizeof(int)); // Array para guardar pai dos vertices da AGM
	int* peso = (int*)malloc(voos->qtdV * sizeof(int)); // Array para guardar os pesos de corte minimo
	int* posVoos = (int*)malloc(voos->qtdV * sizeof(int)); // Array para guardar os pesos de corte minimo
	
	struct ArvMin* AGM = criarArvore(voos->qtdV);

	// inicializando a AGM e os Pesos
	for (int i = 1; i < voos->qtdV; i++) {
		pai[i] = -1;
		peso[i] = INT_MAX/2;
		AGM->array[i] = adicionarNoMin(i, peso[i]);
		AGM->pos[i] = i;
	}

	//o Peso do primeiro vertice sera 0
	peso[0] = 0;
	AGM->array[0] = adicionarNoMin(0, peso[0]);
	AGM->pos[0] = 0;

	// Inicializa o tamanho da AGM baseado na quantidade de vertices do grafo de voos
	AGM->tam = voos->qtdV;
		
	while (!estaVazio(AGM)) {

		// Extraindo o vertice com o menor peso(Distancia)
		struct ArvMinNo* ArvMinNo = extrairMin(AGM);
		int u = ArvMinNo->v; // Guarda a posicao do vertice extraido
		
		//atualizando o valor dos vertices
		struct arestaVoo* voosAdj = voos->v[u].cab;
		
		int posVoo = 0;

		while (voosAdj) {
			
			int v = buscarAeroOrigem(voos,voosAdj->aero);
					
			// se o vertice v nao estiver incluido na arvore e o seu peso for menor
			// entao o valor do seu pai sera atualizado
			if (estaNaArvore(AGM, v) && voosAdj->distancia < peso[v]) {
			
				peso[v] = voosAdj->distancia;
				pai[v] = u;
				posVoos[v] = posVoo;
				decrementarChave(AGM, v, peso[v]);
			}
			voosAdj = voosAdj->prox;
			posVoo++;
		}
	}

	// printa a AGM
	imprimirAGM(voos,pai,posVoos);
	
}

// Questao 8