#include <Arduino.h>
#include <Nextion.h>

#include "IHM.h"
#include "DebugManager.h"
#include "Projetor.h"
#include "Tela.h"
#include "Televisao.h"
#include "Lampadas.h"
#include "ArCondicionado.h"
#include "Temperatura.h"

uint32_t NEXTION_BAUD_RATE = 9600;
uint8_t NEXTION_PIN_TX = 17;
uint8_t NEXTION_PIN_RX = 18;

NexButton BTN_MENU_TV(1, 1, "BotaoMenuTV");
NexButton BTN_MENU_LAMPADA(1, 2, "BotaoMenuLPD");
NexButton BTN_MENU_AC(1, 3, "BotaoMenuAC");
NexButton BTN_MENU_TEMP(1, 4, "BotaoMenuTemp");
NexButton BTN_MENU_PROJETOR(1, 5, "BotaoMenuPT");
NexButton BTN_MENU_TELA(1, 6, "BotaoMenuTela");
NexButton BTN_MENU_INICIAL(2, 1, "BotaoInicial");

void configurarInicializacaoNextion()
{
    bool nextionInicializado = nexInit(NEXTION_BAUD_RATE, NEXTION_PIN_RX, NEXTION_PIN_TX);

    if(!nextionInicializado)
    {
        debugErro("O Nextion não confirmou a inicialização");
    }
    else
    {
        debugInfo("Nextion Inicializado");
    }
}

void configurarEventosNextion()
{
  BTN_MENU_TEMP.attachPop(enviarComandoTemperatura);

  nexListen(BTN_MENU_TEMP);
}
