//* ======================
//* BIBLIOTECAS
//*=======================
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "WiFiManager.h"
#include "secrets.h"
#include "debugManager.h"

void conectarWiFi()
{
  debugInfo("===========================");
  debugInfo("Iniciando conexão Wi-Fi...");
  debugInfo("===========================");

  //*Configura o ESP32 com station, ou seja
  //*Ele vai se conectar a um roteador existente
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_SENHA);

  debugInfoSemLinha("[INFO] Conectando");

  uint32_t tentativas = 0;
  const uint32_t maxTentativas = 30;

  while(WiFi.status() != WL_CONNECTED && tentativas < maxTentativas)
  {
    debugInfoSemLinha(".");
    delay(500);
    tentativas++;
  }

  Serial.println();

  if(WiFi.status() == WL_CONNECTED)
  {
    debugInfo("Wi-Fi conectado com sucesso!");
    debugInfoSemLinha("[INFO] Endereço IP: ");
    debugInfoSemLinha(WiFi.localIP().toString());
    debugInfoSemLinha("\n\r");
  }
  else
  {
    debugErro("Falha ao conectar o Wi-Fi.");
    debugErro("Verifique o SSID, senha e sinal de rede.");
    //Alocar um buffer para poder mostrar na tela Nextion que o Wi-Fi deu erro
  }
}

void garantirWiFiConectado()
{
  if(WiFi.status() != WL_CONNECTED)
  {
    debugInfo("Wi-Fi desconectado. Tentando reconectar....");
    conectarWiFi();
  }

  if(WiFi.status() != WL_CONNECTED)
  {
    debugErro("Não foi possível reconectar ao Wi-Fi.");
  }
}

bool WiFiEstaConectado()
{
  return WiFi.status() == WL_CONNECTED;
}