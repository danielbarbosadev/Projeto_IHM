#include <ArduinoJson.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Televisao.h"
#include "IHM.h"

void verificarMensagemTelevisao(const String& mensagem)
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
       if(strstr(situacao, "[ERRO]") != nullptr)
        {
            mostrarErroTelevisao(situacao);
        }
    }
}
void enviarComandotelevisao(uint32_t comandoTelevisao)
{
    JsonDocument doc;
    String mensagem = "";

    doc["tv"]["comando"] = comandoTelevisao;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(TOPICO_TELEVISAO, mensagem.c_str());
}

void mostrarErroTelevisao(const char* mensagemErro)
{
    popUpErroTv.visivel(true);
    btnOkTv.visivel(true);            
    txtErroTv.texto(mensagemErro).visivel(true);
}