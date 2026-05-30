//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Tela.h"

char telaAtual[] = "";

void verificarHandshakeTela(JsonDocument &doc)
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

void enviarComandoTela(uint8_t comandoTela)
{
    JsonDocument doc;
    String mensagem = "";
    
    doc[telaAtual]["comando"] = comandoTela;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(PROJETOR, mensagem.c_str());
}