#ifndef IMH_H
#define IHM_H

#include <Nextion.h>

extern uint32_t NEXTION_BAUD_RATE;

extern uint8_t NEXTION_PIN_TX;

extern uint8_t NEXTION_PIN_RX;

//* SIMPLE BUTTON 
extern NexButton BTN_MENU_TV;
extern NexButton BTN_MENU_LAMPADA;
extern NexButton BTN_MENU_AC;
extern NexButton BTN_MENU_TEMP;
extern NexButton BTN_MENU_PROJETOR;
extern NexButton BTN_MENU_TELA;
extern NexDSButton BTN_TESTE_DUAL;
extern NexButton BTN_TESTE_SIMPLE;

void configurarInicializacaoNextion();
void configurarEventosNextion();
void soltouBotaoDual();
void soltouBotaoSimple();

#endif