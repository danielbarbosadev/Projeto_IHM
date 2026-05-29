//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Projetor.h"

const char PINO_BOTAO_BOOT = 0;

void verificarHandshakeProjetor(JsonDocument &doc)
{
    if (doc["handshake"]["situacao"].isNull())
    {
        debugErro("Resposta da situação não foi enviada no JSON");
        return;
    }
    
    if (doc["handshake"]["situacao"].is<bool>())
    {
        bool handshakeProjetor = doc["handshake"]["situacao"].as<bool>();

        if (!handshakeProjetor)
        {
            debugErro("Falha no comando do módulo Projetor, reenvie denovo");
        }
        else
        {
            debugInfo("Comando do módulo Projetor confirmado");
        }
    }
}

void enviarComandoProjetor(uint8_t comandoProjetor)
{
    JsonDocument doc;
    String mensagem = "";

    doc["projetor"]["comando"] = comandoProjetor;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(PROJETOR, mensagem.c_str());
}

void processarComandoProjetor(uint32_t estadoPowerProjetor)
{
    int8_t comandoProjetor = -1;
    if(estadoPowerProjetor)
    {
        comandoProjetor = 0; //DESLIGAR
    }
    else
    {
        comandoProjetor = 1; //LIGAR
    }

    if (comandoProjetor != -1)
    {
        enviarComandoProjetor(comandoProjetor);
        comandoProjetor = -1;
    }
}