#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "includes.h"
#include "config.h"

struct Leitura {
  float tensao;
  float corrente;
};

void setupDataManager();
bool registrarNovaLeitura();
void resetarLeituras();
int getContadorLeituras();
void formatarLeiturasParaJson(JsonDocument& doc);

#endif