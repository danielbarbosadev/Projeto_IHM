//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Temperatura.h"


void verificarHandshakeTemperatura(JsonDocument &doc)
{
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

void enviarComandoTemperatura()
{
    bool enviarDados = true;
    JsonDocument doc;
    String mensagem;

    doc["temperatura"]["comando"] = enviarDados;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(PROJETOR, mensagem.c_str());
    enviarDados = false;
}