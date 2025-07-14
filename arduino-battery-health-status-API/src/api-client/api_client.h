#ifndef API_CLIENT_H
#define API_CLIENT_H

// Declara a função que envia os dados para a API
// Ela recebe os valores dos sensores como parâmetros
void sendBatteryData(float voltage, float current, float temperature);

#endif