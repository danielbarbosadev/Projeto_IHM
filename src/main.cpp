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

  switch (moduloRecebido)
  {
  case PROJETOR:
    verificarHandshakeProjetor(mensagem);
    break;

  case TELA:
    verificarHandshakeTela(mensagem);
    break;

  case TELEVISAO:
    verificarHandshakeTelevisao(mensagem);
    break;

  case LAMPADAS:
    verificarHandshakeLampadas(mensagem);
    break;

  case AR_CONDICIONADO:
    verificarHandshakeArCondicionado(mensagem);
    break;

  case TEMPERATURA:
    verificarHandshakeTemperatura(mensagem);
    break;

  default:
    debugErro("Tópico não tratado: " + String(topico));
    return;
    break;
  }
}

modulos identificarTopicos(const char *topico)
{
  for (size_t i = 0; i < obterTotalTopicosRecebimento(); i++)
  {
    if (strcmp(topico, obterTopicoRecebimento(i)) == 0)
    {
      return modulos(i);
    }
  }
  return MODULO_INVALIDO;
}