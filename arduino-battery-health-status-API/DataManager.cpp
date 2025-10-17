#include "DataManager.h"

static Leitura serieLeituras[NUMERO_MAX_LEITURAS];
static int contadorLeituras = 0;

int leituraAnalogicaEstabilizada(int pino) {
  long soma = 0;
  for (int i = 0; i < NUM_AMOSTRAS_ADC; i++) {
    soma += analogRead(pino);
    delay(10);
  }
  return soma / NUM_AMOSTRAS_ADC;
}

float converterParaTensao(int leituraADC) {
  float tensao_no_pino = (leituraADC / 4095.0) * TENSAO_REFERENCIA_ADC;
  return tensao_no_pino * FATOR_DIVISOR_TENSAO;
}

float converterParaCorrente(int leituraADC) {
  float tensao_no_pino = (leituraADC / 4095.0) * TENSAO_REFERENCIA_ADC;
  return (tensao_no_pino - TENSAO_ZERO_CORRENTE) / SENSibilidade_SENSOR_CORRENTE;
}

void setupDataManager() {
  pinMode(PINO_TENSAO, INPUT);
  pinMode(PINO_CORRENTE, INPUT);
  Serial.println("Gerenciador de Dados inicializado.");
}

bool registrarNovaLeitura() {
  if (contadorLeituras >= NUMERO_MAX_LEITURAS) {
    return false; 
  }

  int leitura_bruta_tensao = leituraAnalogicaEstabilizada(PINO_TENSAO);
  int leitura_bruta_corrente = leituraAnalogicaEstabilizada(PINO_CORRENTE);

  serieDeLeituras[contadorLeituras].tensao = converterParaTensao(leitura_bruta_tensao);
  serieDeLeituras[contadorLeituras].corrente = converterParaCorrente(leitura_bruta_corrente);

  Serial.printf("Leitura %d/%d: Tensao=%.2fV, Corrente=%.2fA\n",
                contadorLeituras + 1, NUMERO_MAX_LEITURAS,
                serieDeLeituras[contadorLeituras].tensao,
                serieDeLeituras[contadorLeituras].corrente);

  contadorLeituras++;
  return true;
}

void resetarLeituras() {
  contadorLeituras = 0;
  Serial.println("Leituras resetadas. Pronto para um novo ciclo.");
}

int getContadorLeituras() {
  return contadorLeituras;
}

void formatarLeiturasParaJson(JsonDocument& doc) {
    JsonArray leiturasJson = doc["leituras"].to<JsonArray>();
    for(int i = 0; i < contadorLeituras; i++) {
        JsonObject leitura = leiturasJson.add<JsonObject>();
        leitura["tensao"] = serieDeLeituras[i].tensao;
        leitura["corrente"] = serieDeLeituras[i].corrente;
    }
}