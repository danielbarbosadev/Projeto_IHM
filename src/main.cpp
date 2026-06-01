//* ======================
//* BIBLIOTECAS
//*=======================
#include <Arduino.h>

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
Topicos identificarTopicos(const char *topico);
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
  loopNextion();
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

 Topicos topicoRecebido = identificarTopicos(topico);

  switch (topicoRecebido)
  {
  case TOPICO_PROJETOR:
    verificarHandshakeProjetor(mensagem);
    break;

  case TOPICO_TELA:
    verificarHandshakeTela(mensagem);
    break;

  case TOPICO_TELEVISAO:
    verificarHandshakeTelevisao(mensagem);
    break;

  case TOPICO_LAMPADAS:
    verificarHandshakeLampadas(mensagem);
    break;

  case TOPICO_AR_CONDICIONADO:
    verificarHandshakeArCondicionado(mensagem);
    break;

  case TOPICO_TEMPERATURA:
    verificarHandshakeTemperatura(mensagem);
    break;

  default:
    debugErro("Tópico não tratado: " + String(topico));
    return;
    break;
  }
}

Topicos identificarTopicos(const char *topico)
{
  for (size_t i = 0; i < obterTotalTopicosRecebimento(); i++)
  {
    if (strcmp(topico, obterTopicoRecebimento(i)) == 0)
    {
      return Topicos(i);
    }
  }
  return TOPICO_INVALIDO;
}