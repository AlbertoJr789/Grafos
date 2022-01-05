#pragma once

#include <string>

typedef struct Hora {

	unsigned int hora = 0 , minuto = 0, segundos = 0;
	bool entrada = false, chegada = false;

};

double obterTempoViagem(Hora start, Hora stop);

void obterHora(Hora* h,std::string charLinha);
void calcularDiferenca(Hora h1, Hora h2);
void converterPM(Hora h);


