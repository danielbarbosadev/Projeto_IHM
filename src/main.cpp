//* BIBLIOTECAS
#include <Arduino.h>
#include <ArduinoJson.h>

//* ARQUIVOS LOCAIS
#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "secrets.h"
#include "Enum.h"
#include "Projetor.h"

//* PROTÓTIPOS DAS FUNÇÕES
modulos identificarTopicos(const char *topico);
void tratarMensagemRecebida(const char *, const String &);
void tratarJsonHandshake(const String &, modulos);

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
  loopComandoProjetor();
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

  if (moduloRecebido == MODULO_INVALIDO)
  {
    debugErro("Tópico não tratado: " + String(topico));
    return;
  }

  tratarJsonHandshake(mensagem, moduloRecebido);
}

void tratarJsonHandshake(const String &mensagem, modulos moduloRecebido)
{
  JsonDocument doc;

  DeserializationError erro = deserializeJson(doc, mensagem);

  if (erro)
  {
    debugErro("Erro ao interpretar JSON");
    debugErro(erro.c_str());
    return;
  }

  switch (moduloRecebido)
  {
  case PROJETOR:
    verificarHandshakeProjetor(doc);
    break;

  case TELA:
  //TODO Implementar arquivo Tela.cpp
    static bool handshakeTela;
    if (doc["handshake"]["situacao"].is<bool>())
    {
      handshakeTela = doc["handshake"]["situacao"].as<bool>();

      if (!handshakeTela)
      {
        debugErro("Falha ao encontrar comando, reenvie novamente");
      }
      else
      {
        debugInfo("Comando confirmado");
      }
    }
    break;

  case TELEVISAO:
  //TODO Implementar arquivo Televisao.cpp
    static bool handshakeTelevisao;
    if (doc["handshake"]["situacao"].is<bool>())
    {
      handshakeTelevisao = doc["handshake"]["situacao"].as<bool>();

      if (!handshakeTelevisao)
      {
        debugErro("Falha no comando, reenvie denovo");
      }
      else
      {
        debugInfo("Comando confirmado");
      }
    }
    break;

  case LAMPADAS:
  //TODO Implementar arquivo Lampadas.cpp
    static bool handshakeLampadas;
    if (doc["handshake"]["situacao"].is<bool>())
    {
      handshakeLampadas = doc["handshake"]["situacao"].as<bool>();

      if (!handshakeLampadas)
      {
        debugErro("Falha no comando, reenvie denovo");
      }
      else
      {
        debugInfo("Comando confirmado");
      }
    }
    break;

  case AR_CONDICIONADO:
  //TODO Implementar arquivo Ar_Condicionado.cpp
    static bool handshakeArCondicionado;
    if (doc["handshake"]["situacao"].is<bool>())
    {
      handshakeArCondicionado = doc["handshake"]["situacao"].as<bool>();

      if (!handshakeArCondicionado)
      {
        debugErro("Falha no comando, reenvie denovo");
      }
      else
      {
        debugInfo("Comando confirmado");
      }
    }
    break;

  case TEMPERATURA:
  //TODO Implementar arquivo Temperatura.cpp
    static bool handshakeTemperatura;
    if (doc["handshake"]["situacao"].is<bool>())
    {
      handshakeTemperatura = doc["handshake"]["situacao"].as<bool>();

      if (!handshakeTemperatura)
      {
        debugErro("Falha no comando, reenvie denovo");
      }
      else
      {
        debugInfo("Comando confirmado");
      }
    }
    break;

    default:
      debugErro("Módulo inexistente");
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
  return MODULO_INVALIDO;
}