//* BIBLIOTECAS
#include <Arduino.h>
#include <ArduinoJson.h>

//* ARQUIVOS LOCAIS
#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"

//* PROTÓTIPOS DAS FUNÇÕES
void tratarMensagemRecebida(const char*, const String&);
void tratarJsonComando(const String&);
void publicarRequisicao();

//* CONSTANTES
const char TOPICO_COMANDO[] = "topico/receber/1";

bool pedidoRequisicao = true;

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
  publicarRequisicao();
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

  if (strcmp(topico, TOPICO_COMANDO) == 0)
  {
    tratarJsonComando(mensagem);
    return;
  }

  debugErro("Tópico não tratado " + String(topico));

}

void tratarJsonComando(const String& mensagem)
{
  JsonDocument doc;

  DeserializationError erro = deserializeJson(doc, mensagem);

  static bool requisicaoAceita = true;


  if(erro)
  {
    debugErro("Erro ao interpretar JSON");
    debugErro(erro.c_str());
    return;
  }

  if (!doc["requisicaoAceita"].is<bool>())
  {
    debugErro("JSON inválido, utilize requisicaoAceita ");
  }
  else
  {
    requisicaoAceita = doc["requisicaoAceita"].as<bool>();

    if(!requisicaoAceita)
    {
      pedidoRequisicao = true;
    }
    else
    {
      pedidoRequisicao = false;
    }
  }
}

void publicarRequisicao()
{
  JsonDocument doc;
  String mensagem = "";
  static bool ligarProjetor;

  if(pedidoRequisicao)
  {
    uint32_t agora = millis();
    uint32_t tempoInicial = 0;

    if(agora - tempoInicial >= 2000)
    {
      tempoInicial = agora;
      ligarProjetor = true;
      doc["projetor"]["ligar"] = ligarProjetor;
      serializeJson(doc, mensagem);
      publicarMensagemNoTopico(0, mensagem.c_str());
      pedidoRequisicao = false;
    }

  }
  else
  {
    return;
  }
}