//=== Importacoes e bibliotecas ===//
#include <HTTPClient.h>
#include "config/config.h"
#include "wifi-manager/wifi_manager.h"


//=== Instâncias, variáveis globais e funções ===//
const int Pino_Tensao = A1;
const int Pino_Corrente = A0;

int Leitura_Bruta_Tensao;
int Leitura_Bruta_Corrente;

void coletar_e_enviar_dados() {
  int Leitura_Bruta_Tensao;
  int Leitura_Bruta_Corrente;

  Leitura_Bruta_Tensao = analogRead(Pino_Tensao);
  Leitura_Bruta_Corrente = analogRead(Pino_Corrente);

  const char* serverUrl = "https://c2f0-189-12-11-2.ngrok-free.app/bateria/relatorios/json";
  //para usar o arduino descomente o código de baixo e comente a linha de cima
  //const char* serverUrl = "http://192.168.1.100:8000/bateria/dados";

  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Cria o payload JSON com os dados coletados
    String payload = "{\"tensao\": " + String(Leitura_Bruta_Tensao) + ", \"corrente\": " + String(Leitura_Bruta_Corrente) + "}";

    // Envia a requisição POST
    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

//=== Função principais setup() e loop() ===//
void setup() {
  
  Serial.begin(115200);
  delay(100);

  Serial.println("Iniciando a coleta de dados de tensao e corrente...");
}

void loop() {
  coletar_e_enviar_dados();
  
  delay(2000);
}