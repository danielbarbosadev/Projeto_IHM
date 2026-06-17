#include <ArduinoJson.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "IHM.h"
#include "Sensor.h"


#define SENSOR_ERRO -999

static bool leituraComErro(float valor)
{
    return valor <= SENSOR_ERRO;
}

void verificarMensagemSensor(const String &mensagem)
{
    JsonDocument doc;

    DeserializationError erro = deserializeJson(doc, mensagem);

    if (erro)
    {
        mostrarMensagemErro();
        debugErro("Erro ao interpretar JSON");
        debugErro(erro.c_str());
        return;
    }

    if (doc["sensores"].isNull())
    {
        mostrarMensagemErro();
        return;
    }

    JsonObject sensores = doc["sensores"];

    if (!sensores["temperatura"].isNull())
 	{
        float temperatura = sensores["temperatura"].as<float>();

        if (leituraComErro(temperatura))
            txtTemperatura.texto("Erro").visivel(true);
        else
            txtTemperatura.texto(char(temperatura) + " C").visivel(true);
    }

    if (!sensores["umidade"].isNull())
    {
        float umidade = sensores["umidade"].as<float>();

        if (leituraComErro(umidade))
            txtUmidade.texto("Erro").visivel(true);
        else
            txtUmidade.texto(char(umidade) + "%").visivel(true);
    }

    if (!sensores["som"].isNull())
    {
        float som = sensores["som"].as<float>();

        if (leituraComErro(som))
            txtSom.texto("Erro").visivel(true);
        else
            txtSom.texto(char(som) + " dB").visivel(true);
    }
}

void enviarComandoSensor()
{
    JsonDocument doc;
    String mensagem;

    doc["sensores"]["comando"] = true;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(TOPICO_SENSOR, mensagem.c_str());
}

void mostrarMensagemErro()
{
    txtTemperatura.texto("Erro").visivel(true);
    txtUmidade.texto("Erro").visivel(true);
    txtSom.texto("Erro").visivel(true);
}
