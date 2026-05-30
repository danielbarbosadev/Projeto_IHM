#include <ArduinoJson.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Televisao.h"

void verificarHandshakeTelevisao(const String& mensagem)
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