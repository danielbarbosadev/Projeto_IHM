#ifndef IMH_H
#define IHM_H

#include <Nextion.h>

//* SIMPLE BUTTON 
NexButton bntMenuInicial(1, 2, "BotaoInicial");
NexButton btnMenuTelevisao(1, 1, "BotaoMenuTV");
NexButton btnMenuLampadas(1, 2, "BotaoMenuLPD");
NexButton btnMenuArCondicionado(1, 3, "BotaoMenuAC");
NexButton btnMenuTemperatura(1, 4, "BotaoMenuTemp");
NexButton btnMenuProjetorTela(1, 5, "BotaoMenuPT");

void configurarInicializacaoNextion();
void configurarEventosNextion();
void configurarTelaArCondicionado();



#endif