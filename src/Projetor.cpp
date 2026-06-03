#include <ArduinoJson.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Projetor.h"

char projetorEscolhido[32] = "";

void verificarHandshakeProjetor(const String& mensagem)
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

void enviarComandoProjetor(uint32_t comandoProjetor)
{
    JsonDocument doc;
    String mensagem = "";

    doc[projetorEscolhido]["comando"] = comandoProjetor;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(TOPICO_PROJETOR, mensagem.c_str());
}