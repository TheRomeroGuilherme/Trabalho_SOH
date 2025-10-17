#include "CommunicationManager.h"
#include "config.h"
#include "DataManager.h" 

static char apiKey[50];
static String deviceId;

void setupCommunicationManager() {
  deviceId = WiFi.macAddress();
  Serial.print("ID do Dispositivo: ");
  Serial.println(deviceId);

  WiFiManager wm;
  wm.setDebugOutput(true);
  WiFiManagerParameter custom_api_key("api_key", "Chave da API", "", 50);
  wm.addParameter(&custom_api_key);

  if (!wm.autoConnect("BateriaMonitor-Setup")) {
    Serial.println("Falha ao conectar. Reiniciando...");
    ESP.restart();
  }

  strcpy(apiKey, custom_api_key.getValue());
  Serial.println("WiFi conectado e chave da API configurada!");
}

void enviarDadosParaApi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Não é possível enviar.");
    return;
  }
  
  if (getContadorLeituras() == 0) {
      Serial.println("Nenhuma leitura para enviar.");
      return;
  }

  JsonDocument doc;
  doc["device_id"] = deviceId;
  formatarLeiturasParaJson(doc);

  String payload;
  serializeJson(doc, payload);

  HTTPClient http;
  String serverUrl = "http://" + String(API_HOST) + ":" + String(API_PORT) + String(API_ENDPOINT);
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", apiKey);

  Serial.println("Enviando dados para a API...");
  Serial.println(payload);

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    Serial.printf("Resposta da API: %d\n", httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.printf("Erro no envio. Código: %d\n", httpResponseCode);
  }

  http.end();
}