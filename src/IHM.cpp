
#include <Arduino.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "IHM.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "Projetor.h"
#include "Tela.h"
#include "Televisao.h"
#include "Lampadas.h"
#include "ArCondicionado.h"
#include "Temperatura.h"

uint32_t NEXTION_BAUD_RATE = 9600;

uint8_t NEXTION_PIN_TX = 18; //Pino TX vai no RX do Nextion

uint8_t NEXTION_PIN_RX = 17; //Pino RX vai no TX do Nextion

//* ======================
//* INSTÂNCIAS
//*=======================

//* SIMPLE BUTTON 
NexButton bntMenuInicial(1, 2, "BotaoInicial");
NexButton btnMenuTelevisao(1, 1, "BotaoMenuTV");
NexButton btnMenuLampadas(1, 2, "BotaoMenuLPD");
NexButton btnMenuArCondicionado(1, 3, "BotaoMenuAC");
NexButton btnMenuTemperatura(1, 4, "BotaoMenuTemp");
NexButton btnMenuProjetorTela(1, 5, "BotaoMenuPT");

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
    btnMenuArCondicionado.attachPop(configurarTelaArCondicionado);
    //btnMenuTelevisao.attachPop();
    //btnMenuLampadas.attachPop();
    //btnMenuProjetorTela.attachPop();
    //btnMenuTemperatura.attachPop();

    nexClearListenList();

    nexListen(btnMenuArCondicionado);
    nexListen(btnMenuLampadas);
    nexListen(btnMenuTemperatura);
    nexListen(btnMenuProjetorTela);
    nexListen(btnMenuTelevisao);
}

void configurarTelaArCondicionado()
{
    sendCommand("ArCondicionado");
}


