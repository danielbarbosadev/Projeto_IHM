//* ======================
//* BIBLIOTECAS
//*=======================
#include <Arduino.h>
#include <ArduinoJson.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "secrets.h"
#include "Enum.h"
#include "Projetor.h"
#include "Tela.h"
#include "Televisao.h"
#include "Lampadas.h"
#include "ArCondicionado.h"
#include "Temperatura.h"
#include "IHM.h"

//* ======================
//* PROTÓTIPOS DAS FUNÇÕES
//*=======================
modulos identificarTopicos(const char *topico);
void tratarMensagemRecebida(const char *, const String &);
void tratarJsonHandshake(const String &, modulos);

void setup()
{
  configurarInicializacaoNextion();
  configurarEventosNextion();
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
  nexLoop();
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
    verificarHandshakeTela(doc);
    break;

  case TELEVISAO:
    verificarHandshakeTelevisao(doc);
    break;

  case LAMPADAS:
    verificarHandshakeLampadas(doc);
    break;

  case AR_CONDICIONADO:
    verificarHandshakeArCondicionado(doc);
    break;

  case TEMPERATURA:
    verificarHandshakeTemperatura(doc);
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