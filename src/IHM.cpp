#include <Arduino.h>
#include <NextionUI.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "IHM.h"
#include "DebugManager.h"
#include "Projetor.h"
#include "Tela.h"
#include "Televisao.h"
#include "Lampadas.h"
#include "ArCondicionado.h"
#include "Sensor.h"

const uint32_t NEXTION_BAUD_RATE = 9600;
const uint8_t NEXTION_PIN_TX = 17;
const uint8_t NEXTION_PIN_RX = 18;

//* ======================
//* INSTÂNCIAS
//*=======================

NexDisplay display;

//* BOTÕES MENU PRINCIPAL
NexBotao BTN_MENU_TV(1, 1, "BotaoMenuTV");
NexBotao BTN_MENU_LAMPADA(1, 2, "BotaoMenuLPD");
NexBotao BTN_MENU_AC(1, 3, "BotaoMenuAC");
NexBotao BTN_MENU_SENSOR(1, 4, "BotaoMenuTemp");
NexBotao BTN_MENU_PROJETOR(1, 5, "BotaoMenuPT");
NexBotao BTN_MENU_TELA(1, 6, "BotaoMenuTela");

//* BOTÕES LÂMPADA
NexBotao BTN_MENU_INICIAL(3, 1, "BotaoInicial");
NexBotaoDuplo INTERRUPTOR_LAMPADA_1(3, 2, "interruptor1");
NexBotaoDuplo INTERRUPTOR_LAMPADA_2(3, 3, "interruptor2");
NexBotaoDuplo INTERRUPTOR_LAMPADA_3(3, 4, "interruptor3");
NexBotaoDuplo INTERRUPTOR_LAMPADA_4(3, 5, "interruptor4");


void processarLampada(NexBotaoDuplo& interruptor, const char* nomeLampada);

void configurarInicializacaoNextion()
{
    if(!display.begin(Serial2, NEXTION_BAUD_RATE, NEXTION_PIN_RX, NEXTION_PIN_TX))
    {
        debugErro("O Nextion não confirmou a inicialização");
    }
    else
    {
        debugInfo("Inicializacão Nextion confirmada");
    }
}

void loopNextion()
{
    display.atualizar();
}

void configurarEventosNextion()
{
  display.escutar(BTN_MENU_SENSOR);
  BTN_MENU_SENSOR.aoSoltar(enviarComandoSensor);

  display.escutar(INTERRUPTOR_LAMPADA_1);
  INTERRUPTOR_LAMPADA_1.aoSoltar([]()
  {
    processarLampada(INTERRUPTOR_LAMPADA_1, "Lampada_1");
  });

  display.escutar(INTERRUPTOR_LAMPADA_2);
  INTERRUPTOR_LAMPADA_2.aoSoltar([]()
  {
    processarLampada(INTERRUPTOR_LAMPADA_2, "Lampada_2");
  });

  display.escutar(INTERRUPTOR_LAMPADA_3);
  INTERRUPTOR_LAMPADA_3.aoSoltar([]()
  {
    processarLampada(INTERRUPTOR_LAMPADA_3, "Lampada_3");
  });

  display.escutar(INTERRUPTOR_LAMPADA_4);
  INTERRUPTOR_LAMPADA_4.aoSoltar([]()
  {
    processarLampada(INTERRUPTOR_LAMPADA_4, "Lampada_4");
  });
}

void processarLampada(NexBotaoDuplo& interruptor, const char* nomeLampada)
{
    uint32_t estadoLampada;

    interruptor.get("val", estadoLampada);

    enviarComandoLampada(nomeLampada, estadoLampada);
}
