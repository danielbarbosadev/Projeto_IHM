#include <ArduinoJson.h>

//* ARQUIVOS LOCAIS
#include "secrets.h"
#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "moduloProjetor.h"

const char* comandoProjetor = nullptr;

void configurarPinoBoot()
{
    pinMode(PINO_BOTAO_BOOT, INPUT_PULLUP);
}

void enviarComandoProjetor()
{
  JsonDocument doc;
  String mensagem = "";

  doc["projetor"]["comando"] = comandoProjetor;
  serializeJson(doc, mensagem);
  publicarMensagemNoTopico(PROJETOR, mensagem.c_str());
}

void definirComandoProjetor()
{
  bool estadoAtualBotao = !digitalRead(PINO_BOTAO_BOOT);
  static bool estadoAnteriorBotao = 1;

  if (estadoAtualBotao && !estadoAnteriorBotao)
  {
    comandoProjetor = "desligar";
  }
  estadoAnteriorBotao = estadoAtualBotao;


  if(comandoProjetor != nullptr)
  {
    enviarComandoProjetor();
    comandoProjetor = nullptr;
  }
}