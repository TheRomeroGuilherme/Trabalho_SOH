#include "includes.h"
#include "config.h"
#include "DataManager.h"
#include "CommunicationManager.h"

unsigned long tempoUltimaLeitura = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nIniciando o sistema de monitoramento de bateria...");

  setupDataManager();
  setupCommunicationManager();

  Serial.println("Setup concluído. Aguardando para iniciar o ciclo de leituras.");
}

void loop() {
  if (getContadorLeituras() >= NUMERO_MAX_LEITURAS) {
    enviarDadosParaApi();
    
    resetarLeituras();
  }
  if (millis() - tempoUltimaLeitura >= INTERVALO_LEITURAS_MS) {
    registrarNovaLeitura();
    
    tempoUltimaLeitura = millis();
  }
}