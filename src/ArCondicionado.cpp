#include <ArduinoJson.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "ArCondicionado.h"
#include "IHM.h"

char AC_Escolhido[32] = "";

void verificarMensagemArCondicionado(const String& mensagem)
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
            mostrarErroAc(situacao);
        }
    }
}

void enviarComandoAC(uint32_t comandoAC)
{
    if(strlen(AC_Escolhido) == 0)
    {
        debugErro("Nenhum Ar-Condicionado foi escolhido");
        return;
    }

    JsonDocument doc;
    String mensagem = "";

    doc[AC_Escolhido]["comando"] = comandoAC;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(TOPICO_AR_CONDICIONADO, mensagem.c_str());
}

void mostrarErroAc(const char* mensagemErro)
{
    popUpErroAc.visivel(true);
    btnOkAc.visivel(true);            
    txtErroAc.texto(mensagemErro).visivel(true);
}