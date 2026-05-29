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
NexDSButton BTN_TESTE_DUAL(1, 7, "btnTestDual");
NexButton BTN_TESTE_SIMPLE(1, 8, "btnTesteSimple");

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
    BTN_TESTE_DUAL.attachPop(soltouBotaoDual);
    BTN_TESTE_SIMPLE.attachPop(soltouBotaoSimple);

    nexListen(BTN_TESTE_DUAL);
    nexListen(BTN_TESTE_SIMPLE);
}

void soltouBotaoDual()
{
    uint32_t estadoBotaoDual;
    BTN_TESTE_DUAL.getValue(&estadoBotaoDual);

    processarComandoProjetor(estadoBotaoDual);  
    
}

void soltouBotaoSimple()
{

}