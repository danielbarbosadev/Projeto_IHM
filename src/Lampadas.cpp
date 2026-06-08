#include <ArduinoJson.h>
#include <Preferences.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Lampadas.h"

char lampadaEscolhida[32] = "";

void guardarEstadoLampada(uint8_t numLampadaSalvar, bool estado)
{
    Preferences memoria;
    char lampadas[24] = "";
    snprintf(lampadas, sizeof(lampadas), "lampada_%d", numLampadaSalvar);

    memoria.begin("lampadas", false);
    memoria.putBool(lampadas, estado);
    memoria.end();
}

bool carregarEstadoLampada(uint8_t numLampadaCarregar)
{
    Preferences memoria;
    char lampadas[24] = "";
    snprintf(lampadas, sizeof(lampadas), "lampada_%d", numLampadaCarregar);

    memoria.begin("lampadas", true);
    bool estado = memoria.getBool(lampadas, false);
    memoria.end();
    return estado;
}

void verificarHandshakeLampadas(const String& mensagem)
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

void enviarComandoLampada(bool comandoLampada)
{
    JsonDocument doc;
    String mensagem;

    doc[lampadaEscolhida] = comandoLampada;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(TOPICO_LAMPADAS, mensagem.c_str());
}