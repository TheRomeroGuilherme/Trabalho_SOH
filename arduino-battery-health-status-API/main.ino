//=== Importacoes e bibliotecas ===//
#include <Arduino.h>


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

  Serial.print("tensao: ");
  Serial.println(Leitura_Bruta_Tensao);

  Serial.print("corrente: ");
  Serial.println(Leitura_Bruta_Corrente);

  Serial.println("---");
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