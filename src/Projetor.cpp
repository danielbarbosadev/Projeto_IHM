//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "MqttManager.h"
#include "DebugManager.h"
#include "Enum.h"
#include "Projetor.h"

const char PINO_BOTAO_BOOT = 0;

void configurarPinoBoot()
{
    pinMode(PINO_BOTAO_BOOT, INPUT_PULLUP);
}

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

void enviarComandoProjetor(const char* comandoProjetor)
{
    JsonDocument doc;
    String mensagem = "";

    doc["projetor"]["comando"] = comandoProjetor;
    serializeJson(doc, mensagem);
    publicarMensagemNoTopico(PROJETOR, mensagem.c_str());
}

void loopComandoProjetor()
{
    bool estadoAtualBotao = !digitalRead(PINO_BOTAO_BOOT);
    static bool estadoAnteriorBotao = 1;
    const char *comandoProjetor = nullptr;

    
    //* ======================
    //* APENAS TESTE
    //*=======================
    if (estadoAtualBotao && !estadoAnteriorBotao)
    {
        comandoProjetor = "power";
    }
    estadoAnteriorBotao = estadoAtualBotao;

    if (estadoAtualBotao && !estadoAnteriorBotao)
    {
        comandoProjetor = "desligar";
    }
    estadoAnteriorBotao = estadoAtualBotao;

    if (estadoAtualBotao && !estadoAnteriorBotao)
    {
        comandoProjetor = "hdmi";
    }
    estadoAnteriorBotao = estadoAtualBotao;

    if (estadoAtualBotao && !estadoAnteriorBotao)
    {
        comandoProjetor = "mudo";
    }
    estadoAnteriorBotao = estadoAtualBotao;

    if (comandoProjetor != nullptr)
    {
        enviarComandoProjetor(comandoProjetor);
        comandoProjetor = nullptr;
    }
}