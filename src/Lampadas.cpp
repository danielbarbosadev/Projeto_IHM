#include <ArduinoJson.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Lampadas.h"
#include "IHM.h"

void verificarMensagemLampadas(const String& mensagem)
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
    
    if (doc["statusComando"]["comando"].is<bool>())
    {
        bool comando = doc["statusComando"]["comando"].as<bool>();

        if (!comando)
        {
            debugErro("Falha no comando, reenvie denovo");
        }
        else
        {
            debugInfo("Comando confirmado");
        }
    }

    if (doc["statusComando"]["situacao"].is<const char*>())
    {
        const char* situacao = doc["statusComando"]["situacao"].as<const char*>();
        if(strstr(situacao, "[ERRO]") != nullptr)
        {
            mostrarErroLampada(situacao);
        }
    }
}

void enviarComandoLampada(const char* lampada, uint32_t comandoLampada)
{
    JsonDocument doc;
    String mensagem;

    doc[lampada] = (bool)comandoLampada;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(TOPICO_LAMPADAS, mensagem.c_str());
}

void mostrarErroLampada(const char* mensagemErro)
{
    popUpErroLampada.visivel(true);
    btnErroLampada.visivel(true);            
    txtErroLampada.texto(mensagemErro).visivel(true);
}