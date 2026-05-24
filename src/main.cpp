//* BIBLIOTECAS
#include <Arduino.h>
#include <ArduinoJson.h>

//* ARQUIVOS LOCAIS
#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "secrets.h"
#include "moduloProjetor.h"

//* CONSTANTES


//* PROTÓTIPOS DAS FUNÇÕES
modulos identificarTopicos(const char *topico);
void tratarMensagemRecebida(const char *, const String &);
void tratarJsonRequisicoes(const String &, modulos);



void setup()
{
  configurarPinoBoot();
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
  definirComandoProjetor();
}

void tratarMensagemRecebida(const char *topico, const String &mensagem)
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

  modulos moduloRecebido = identificarTopicos(topico);

  if (moduloRecebido == TOPICO_INVALIDO)
  {
    debugErro("Tópico não tratado: " + String(topico));
    return;
  }

  tratarJsonRequisicoes(mensagem, moduloRecebido);
}

void tratarJsonRequisicoes(const String &mensagem, modulos moduloRecebido)
{
  JsonDocument doc;

  DeserializationError erro = deserializeJson(doc, mensagem);

  static bool handshake;

  if (erro)
  {
    debugErro("Erro ao interpretar JSON");
    debugErro(erro.c_str());
    return;
  }

  switch (moduloRecebido)
  {
  case PROJETOR:
    if (doc["handshake"]["situacao"].is<bool>())
    {
      handshake = doc["handshake"]["situacao"].as<bool>();

      if (!handshake)
      {
        debugErro("Falha no comando reenvie denovo");
      }
      else
      {
        debugInfo("Comando confirmado");
      }
    }
    break;
  }
}



modulos identificarTopicos(const char *topico)
{
  for (size_t i = 0; i < obterTotalTopicosRecebimento(); i++)
  {
    if (strcmp(topico, TOPICOS_RECEBER[i]) == 0)
    {
      return modulos(i);
    }
  }

  return TOPICO_INVALIDO;
}

