#include <ArduinoJson.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Lampadas.h"


void verificarHandshakeLampadas(const String& mensagem)
{
    JsonDocument doc;

    DeserializationError erro = deserializeJson(doc, mensagem);

    if (erro)
    {
        debugErro("Erro ao interpretar JSON");
        debugErro(erro.c_str());
        return;
    }

    if (doc["handshake"]["situacao"].isNull())
    {
        debugErro("Resposta da situação não foi enviada no JSON");
        return;
    }
    
    if (doc["handshake"]["situacao"].is<bool>())
    {
        bool handshake = doc["handshake"]["situacao"].as<bool>();

        if (!handshake)
        {
            debugErro("Falha no comando, reenvie denovo");
        }
        else
        {
            debugInfo("Comando confirmado");
        }
    }
}

void processarComandoLampada(uint32_t estadoPowerLampada)
{
    int8_t comandoLampada = -1;
    if(estadoPowerLampada)
    {
        comandoLampada = 0; //DESLIGAR
    }
    else
    {
        comandoLampada = 1; //LIGAR
    }

    if (comandoLampada != -1)
    {
        enviarComandoLampada(comandoLampada);
        comandoLampada = -1;
    }
}

void enviarComandoLampada(int8_t comandoLampada)
{
    JsonDocument doc;
    String mensagem;

    doc["lampada"]["comando"] = comandoLampada;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(PROJETOR, mensagem.c_str());
}