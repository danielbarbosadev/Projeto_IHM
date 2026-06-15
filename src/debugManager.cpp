//* ======================
//* BIBLIOTECAS
//*=======================
#include <Arduino.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "DebugManager.h"
#include "secrets.h"

uint32_t nivelDebugAtual = DEBUG_NIVEL_INICIAL;

void debugErro(const String& mensagem)
{
    if (nivelDebugAtual >= DEBUG_ERRO)
    {
        Serial.print("[ERRO] ");
        Serial.println(mensagem);
    }
}

void debugInfo(const String& mensagem)
{
    if (nivelDebugAtual >= DEBUG_TUDO)
    {
        Serial.print("[INFO] ");
        Serial.println(mensagem);
    }
}

void debugErroSemLinha(const String& mensagem)
{
    if (nivelDebugAtual >= DEBUG_ERRO)
    {
        Serial.print(mensagem);
    }
}

void debugInfoSemLinha(const String& mensagem)
{
    if (nivelDebugAtual >= DEBUG_TUDO)
    {
        Serial.print(mensagem);
    }
}

uint32_t obterNivelDebugAtual()
{
    return nivelDebugAtual;
}

void configurarDebug()
{
    Serial.begin(115200);
    delay(200);

    pinMode(PINO_HABILITA_DEBUG_COMPLETO, INPUT_PULLUP);

    if (digitalRead(PINO_HABILITA_DEBUG_COMPLETO) == LOW)
    {
        nivelDebugAtual = DEBUG_TUDO;
    }
    else
    {
        nivelDebugAtual = DEBUG_NIVEL_INICIAL;
    }

    debugInfoSemLinha("\n\n\n\n\n\r");
    debugInfo("===============================================");
    debugInfo("ESP32 INICIADO");
    debugInfo("SISTEMA DE DEBUG ATIVO");

    if (nivelDebugAtual == DEBUG_TUDO)
    {
        Serial.println("[INFO] DEBUG INICIADO EM MODO COMPLETO");
    }
    
    else if (nivelDebugAtual == DEBUG_ERRO)
    {
        Serial.println("[INFO] DEBUG INICIADO EM APENAS ERROS");
    }
    debugInfo("===============================================");
}