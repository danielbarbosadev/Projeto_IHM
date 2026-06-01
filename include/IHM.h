#ifndef IHM_H
#define IHM_H

#include <NextionUI.h>

extern const uint32_t NEXTION_BAUD_RATE;

extern const uint8_t NEXTION_PIN_TX;

extern const uint8_t NEXTION_PIN_RX;

extern NexDisplay display;

extern NexBotao BTN_MENU_TV;
extern NexBotao BTN_MENU_LAMPADA;
extern NexBotao BTN_MENU_AC;
extern NexBotao BTN_MENU_TEMP;
extern NexBotao BTN_MENU_PROJETOR;
extern NexBotao BTN_MENU_TELA;
extern NexBotao BTN_MENU_INICIAL;

extern NexBotao BTN_MENU_INICIAL;
extern NexBotao BTN_MENU_INICIAL;
extern NexBotaoDuplo INTERRUPTOR_LAMPADA_1;
extern NexBotaoDuplo INTERRUPTOR_LAMPADA_2;
extern NexBotaoDuplo INTERRUPTOR_LAMPADA_3;
extern NexBotaoDuplo INTERRUPTOR_LAMPADA_4;

void configurarInicializacaoNextion();
void loopNextion();
void configurarEventosNextion();
void processarLampada(NexBotaoDuplo& interruptor, const char* nomeLampada);

#endif