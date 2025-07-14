#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h" // Inclui nossas configurações para pegar a URL do servidor

void sendBatteryData(float voltage, float current, float temperature) {
  // Só tenta enviar se o WiFi estiver conectado
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Não é possível enviar dados.");
    return;
  }

  HTTPClient http;
  
  // Monta a URL completa do endpoint: http://servidor/battery/id_da_bateria/status
  String serverPath = String(API_SERVER_HOST) + "/battery/" + String(BATTERY_ID) + "/status";
  
  http.begin(serverPath);
  http.addHeader("Content-Type", "application/json");

  // Monta o corpo JSON da requisição
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["voltage"] = voltage;
  jsonDoc["current"] = current;
  jsonDoc["temperature"] = temperature;

  String requestBody;
  serializeJson(jsonDoc, requestBody);
  
  Serial.println("\nEnviando dados para a API: " + requestBody);

  // Envia a requisição POST
  int httpResponseCode = http.POST(requestBody);

  // Verifica a resposta da API
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Código de resposta da API: " + String(httpResponseCode));
    Serial.println("Resposta: " + response);
  } else {
    Serial.println("Erro no envio para a API. Código de erro: " + String(httpResponseCode));
  }

  http.end();
}