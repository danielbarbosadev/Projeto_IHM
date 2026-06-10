#include <ArduinoJson.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Projetor.h"

char projetorEscolhido[32] = "";

void verificarMensagemProjetor(const String& mensagem)
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

void enviarComandoProjetor(uint32_t comandoProjetor)
{
    if(strlen(projetorEscolhido) == 0)
    {
        debugErro("Nenhum projetor foi escolhido");
        return;
    }

    JsonDocument doc;
    String mensagem = "";

    doc[projetorEscolhido]["comando"] = comandoProjetor;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(TOPICO_PROJETOR, mensagem.c_str());
}