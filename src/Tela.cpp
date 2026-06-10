#include <ArduinoJson.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Tela.h"

char telaEscolhida[32] = "";

void verificarMensagemTela(const String& mensagem)
{
    JsonDocument doc;

    DeserializationError erro = deserializeJson(doc, mensagem);

    if (erro)
    {
        debugErro("Erro ao interpretar JSON");
        debugErro(erro.c_str());
        return;
    }

    if (doc["statusComando"]["comando"].isNull())
    {
        debugErro("Resposta do comando não foi enviada no JSON");
        return;
    }

    if (doc["statusComando"]["situacao"].isNull())
    {
        debugErro("Resposta da situação não foi enviada no JSON");
        return;
    }
    
    if (doc["statusComando"]["situacao"].is<const char*>())
    {
       const char* situacao =  doc["statusComando"]["situacao"].as<const char*>();
    }
}

void enviarComandoTela(uint32_t comandoTela)
{
    JsonDocument doc;
    String mensagem = "";
    
    doc[telaEscolhida]["comando"] = comandoTela;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(TOPICO_TELA, mensagem.c_str());
}