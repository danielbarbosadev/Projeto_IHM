#include <Arduino.h>
#include <NextionUI.h>

#include "IHM.h"
#include "DebugManager.h"
#include "Projetor.h"
#include "Tela.h"
#include "Televisao.h"
#include "Lampadas.h"
#include "ArCondicionado.h"
#include "Temperatura.h"

const uint32_t NEXTION_BAUD_RATE = 9600;
const uint8_t NEXTION_PIN_TX = 17;
const uint8_t NEXTION_PIN_RX = 18;

NexDisplay display;

NexBotao BTN_MENU_TV(1, 1, "BotaoMenuTV");
NexBotao BTN_MENU_LAMPADA(1, 2, "BotaoMenuLPD");
NexBotao BTN_MENU_AC(1, 3, "BotaoMenuAC");
NexBotao BTN_MENU_TEMP(1, 4, "BotaoMenuTemp");
NexBotao BTN_MENU_PROJETOR(1, 5, "BotaoMenuPT");
NexBotao BTN_MENU_TELA(1, 6, "BotaoMenuTela");
NexBotao BTN_MENU_INICIAL(2, 1, "BotaoInicial");

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
  display.escutar(BTN_MENU_TEMP);
  BTN_MENU_TEMP.aoSoltar(enviarComandoTemperatura);
}
