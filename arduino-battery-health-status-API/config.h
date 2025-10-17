#ifdef CONFIG_H
#define CONFIG_H

const int Pino_Tensao = 35;
const int Pino_Corrente = 34;

const int Numero_leituras = 10;
const int Intervalo_entre_leituras = 5000;

const char* API_Host = "192.168.1.10"; // <---> alter para o IP do servidor onde a API está hospedada
const int API_Porta = 8000; // <---> alter para a porta do servidor onde a API está hospedada
const char* API_Endpoint = "/bateria/dados"; 

const float Tensao_referencia = 3.3;
const float Fator_divisor_tensao = 5.7;
const float Sensor_sensibilidade_corrente = 0.185;
const float Tensao_zero_corrente = 1.65;

#endif
