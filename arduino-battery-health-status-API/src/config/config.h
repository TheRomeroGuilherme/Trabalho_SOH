#ifndef CONFIG_H
#define CONFIG_H

// --- Configurações de Wi-Fi ---
// Para usar no simulador Wokwi
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

// Para usar com seu ESP32 físico, comente as linhas acima e descomente as abaixo
// const char* WIFI_SSID = "NOME_DA_SUA_REDE_WIFI";
// const char* WIFI_PASSWORD = "SENHA_DA_SUA_REDE_WIFI";


// --- Configurações da API ---
// Para usar no simulador Wokwi
const char* API_SERVER_HOST = "http://host.wokwi.internal:8000";

// Para usar com seu ESP32 físico, use o IP do seu PC na rede local
// const char* API_SERVER_HOST = "http://192.168.1.10:8000"; // Exemplo, troque pelo seu IP


// --- Constantes do Projeto ---
const char* BATTERY_ID = "Bateria-Principal-01";
const int UPDATE_INTERVAL_MS = 5000; // Intervalo entre os envios (5 segundos)

#endif