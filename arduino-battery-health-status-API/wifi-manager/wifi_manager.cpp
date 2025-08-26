#include "wifi_manager.h"
#include "../config/config.h"
#include <WiFi.h>

void conectar_wifi() {
  Serial.print("Conectando ao WiFi: ");
  Serial.println(Wifi_SSID);

  WiFi.begin(Wifi_SSID, Wifi_Senha);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado com sucesso!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}