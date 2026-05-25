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
    Serial.begin(9600);
    delay(1000);

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
    debugInfo("===================");
    debugInfo(" ESP32 Iniciado");
    debugInfo(" Sistema de debug ativo");

    if (nivelDebugAtual == DEBUG_TUDO)
    {
        Serial.print("[INFO] Debug iniciado em modo completo");
    }
    
    else if (nivelDebugAtual == DEBUG_ERRO)
    {
         Serial.print("[INFO] Debug iniciado em apenas erros");
    }
    debugInfo("===================");
}