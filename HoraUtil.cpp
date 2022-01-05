

#include "HoraUtil.h"
#include "GrafoTAD.h"
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

double obterTempoViagem(Hora chegada, Hora entrada) {

	Hora diff;

	if (chegada.hora == entrada.hora) { 

		if (chegada.minuto == entrada.minuto) { //a viagem durou exatamente 24 horas

			diff.hora = 24;
			diff.minuto = 0;
		
		}

		if (chegada.minuto < entrada.minuto) { // a viagem durou mais de 24 horas

			diff.hora = 24;
			diff.minuto = entrada.minuto - chegada.minuto;
			
		}

		if (chegada.minuto > entrada.minuto) { //a viagem durou menos de 1 hora

			diff.hora = 0;
			diff.minuto = chegada.minuto - entrada.minuto;
			
		}

	}
	else if (chegada.hora < entrada.hora) { // a viagem nao durou 24 horas, mas terminou de um dia pro outro 

		int horaAux = 1;

		while (chegada.hora != entrada.hora) { //conta as horas de entrada ate chegar na hora de chegada

			if (entrada.hora == 23) //zerar o relogio
				entrada.hora = 0;

			entrada.hora++; //avança no tempo
			horaAux++;
		}

		if (entrada.minuto > chegada.minuto) {
			
			chegada.hora--;
			chegada.minuto += 60;
		}
		
		diff.hora = horaAux;
		diff.minuto = chegada.minuto - entrada.minuto;
		

	}
	else { // a viagem durou mais de uma hora e terminou no mesmo dia


		if (entrada.minuto > chegada.minuto) {

			chegada.hora--;
			chegada.minuto += 60;
		}

		diff.hora = chegada.hora - entrada.hora;
		diff.minuto = chegada.minuto - entrada.minuto;
		
	}
	    	
	double minutoHoras = (double)diff.minuto / 60;

	return (double)diff.hora + minutoHoras;

}

void converterPM(Hora* h) {

	switch (h->hora) {

		case 1:
		{
		    h->hora = 13;
			break;
		}
		case 2:
		{
			h->hora = 14;
			break;
		}
		case 3:
		{
			h->hora = 15;
			break;
		}
		case 4:
		{
			h->hora = 16;
			break;
		}
		case 5:
		{
			h->hora = 17;
			break;
		}
		case 6:
		{
			h->hora = 18;
			break;
		}
		case 7:
		{
			h->hora = 19;
			break;
		}
		case 8:
		{
			h->hora = 20;
			break;
		}
		case 9:
		{
			h->hora = 21;
			break;
		}
		case 10:
		{
			h->hora = 22;
			break;
		}
		case 11:
		{
			h->hora = 23;
			break;
		}

	}

}

void obterHora(Hora* h,std::string charLinha) {
				
	int k = 0, i = 0;

	if (h->entrada) { //a hora a ser obtida sera a hora de entrada

		char hora[3];
		//obtendo o horario de entrada
		
		for (i = 12; i < 14; i++) { //obtem as horas

			if (charLinha[i] != ' ') { //certificando de que so sejam recebidos numeros

				hora[k] = charLinha[i];
				k++;
			}

		}

		h->hora = atoi(hora);

		char minuto[3];
		k = 0;

		for (i = 14; i < 17; i++) { //obtem as horas e o período (am/pm)

			if (charLinha[i] != 'P' && charLinha[i] != 'A') {

				minuto[k] = charLinha[i];
				k++;
			}
		}

		h->minuto = atoi(minuto);
		i--;
		if (charLinha[i] == 'P') { //se a hora de entrada tiver final "P", o periodo sera convertido

			converterPM(h);

		}

	}

	if (h->chegada) { //a hora a ser obtida sera a hora de chegada

		// 22 a 27 - horario de chegada

		char hora[3];
		//obtendo o horario de entrada
		for (i = 23; i < 25; i++) { //obtem as horas

			if (charLinha[i] != ' ') { //certificando de que so sejam recebidos numeros

				hora[k] = charLinha[i];
				k++;
			}

		}

		h->hora = atoi(hora);

		char minuto[3];
		k = 0;

		for (i = 25; i < 28; i++) { //obtem as horas e o período (am/pm)

			if (charLinha[i] != 'P' || charLinha[i] != 'A') {

				minuto[k] = charLinha[i];
				k++;
			}
		}

		h->minuto = atoi(minuto);
		i--;
		if (charLinha[i] == 'P') { //se a hora de entrada tiver final "P", o periodo sera convertido

			converterPM(h);

		}

	}

}