//* BIBLIOTECAS
#include <Arduino.h>
#include <ArduinoJson.h>

//* ARQUIVOS LOCAIS
#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "secrets.h"

//* ENUM
enum Topicos
{
  PROJETOR,
  TELA,
  TELEVISAO,
  LAMPADAS,
  AR_CONDICIONADO,
  TOPICO_INVALIDO
};

//* PROTÓTIPOS DAS FUNÇÕES
void tratarMensagemRecebida(const char*, const String&);
void tratarJson(const String&, Topicos);
Topicos identificarTopicos(const char* topico);


void setup() 
{
  configurarDebug();
  conectarWiFi();
  configurarMQTT();
  registrarCallbackMensagem(tratarMensagemRecebida);
  conectarMQTT();
}

void loop() 
{
  garantirWiFiConectado();
  garantirMQTTConectado();
  loopMQTT();
}

void tratarMensagemRecebida(const char* topico, const String& mensagem)
{
  debugInfo("================================");
  debugInfo("Mensagem recebida na aplicação");
  debugInfo("================================");
  
  if (topico == nullptr)
  {
    debugErro("Tópico MQTT inválido");
    return;
  }

  debugInfo("Tópico: " + String(topico));
  debugInfo("Mensagem: " + mensagem);

  Topicos topicoRecebido = identificarTopicos(topico);

  if(topicoRecebido == TOPICO_INVALIDO)
  {
    debugErro("Tópico não tratado " + String(topico));
    return;
  }

    tratarJson(mensagem, topicoRecebido);
}

void tratarJson(const String& mensagem, Topicos topico)
{
  JsonDocument doc;

  DeserializationError erro = deserializeJson(doc, mensagem);

  static bool handshake;

  if(erro)
  {
    debugErro("Erro ao interpretar JSON");
    debugErro(erro.c_str());
    return;
  }

  if(doc["handshake"].is<bool>())
  {
    handshake = doc["handshake"].as<bool>();

    if(handshake)
    {

    }
    else
    {
      
    }
  }
}

Topicos identificarTopicos(const char* topico)
{
  for (size_t i = 0; i < obterTotalTopicosRecebimento(); i++)
  {
    if(strcmp(topico, TOPICOS_RECEBER[i]) == 0)
    {
      return (Topicos)i;
    }
  }  

  return TOPICO_INVALIDO;
}