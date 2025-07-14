// Inclui os headers dos nossos módulos
#include "config.h"
#include "wifi-manager/wifi_manager.h"
#include "api-client/api_client.h"

// A função setup() é executada uma vez quando o dispositivo liga
void setup() {
  Serial.begin(115200);
  delay(1000); // Uma pequena pausa para o monitor serial iniciar

  setupWiFi(); // Chama a função do nosso módulo de Wi-Fi
}

// A função loop() é executada repetidamente
void loop() {
  // 1. Simula a leitura dos sensores (aqui você colocaria o código real dos seus sensores)
  float voltage = 3.8 + random(-3, 3) / 10.0;
  float current = (voltage > 4.0) ? 0.8 : -0.5; // Simula carga/descarga
  float temperature = 38.0 + random(-5, 5);

  Serial.println("\n--- Nova Leitura ---");
  Serial.println("Voltagem Lida: " + String(voltage) + "V");

  // 2. Chama a função do nosso módulo de API para enviar os dados
  sendBatteryData(voltage, current, temperature);

  // 3. Aguarda o intervalo definido no config.h antes da próxima leitura
  Serial.println("Aguardando próximo ciclo...");
  delay(UPDATE_INTERVAL_MS);
}