#include <Arduino.h>
#include <NextionUI.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "IHM.h"
#include "DebugManager.h"
#include "Enum.h"
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
NexBotao btnMenuTv(1, 1, "BotaoMenuTV");
NexBotao btnMenuLampada(1, 2, "BotaoMenuLPD");
NexBotao btnMenuArCondicionado(1, 3, "BotaoMenuAC");
NexBotao btnMenuSensor(1, 4, "BotaoMenuTemp");
NexBotao btnMenuProjetor(1, 5, "BotaoMenuPT");
NexBotao btnMenuTela(1, 6, "BotaoMenuTela");

//* BOTÕES TELEVISÃO
NexBotao BtnInicialTelevisao(2, 1, "BotaoInicial");
NexBotaoDuplo PowerTV(2, 2, "PowerTV");
NexBotao HDMITV(2, 3, "HDMITV");
NexBotao volTV_UP(2, 4, "volTV_UP");
NexBarraProgresso volBarTV(2, 5, "volBarTV");
NexBotao volTV_DOWN(2, 6, "volTV_DOWN");
NexBotaoDuplo muteTV(2, 7, "muteTV");

//* BOTÕES LÂMPADA
NexBotao btnMenuInicialLampada(3, 1, "BotaoInicial");
NexBotaoDuplo interruptorLampada1(3, 2, "interruptor1");
NexBotaoDuplo interruptorLampada2(3, 3, "interruptor2");
NexBotaoDuplo interruptorLampada3(3, 4, "interruptor3");
NexBotaoDuplo interruptorLampada4(3, 5, "interruptor4");

//* BOTÕES TELA
NexBotao btnMenuInicialTela(7, 1, "BotaoInicial");
NexBotao DescerTela (7, 2, "telaDOWN");
NexBotao SubirTela (7, 3, "telaUP");
NexBotao TelaParar (7, 4, "telaFreeze");
NexBotaoDuplo Tela1(7, 5, "tela_Esquerda");
NexBotaoDuplo Tela2(7, 6, "tela_Direita");

//* BOTÕES PROJETOR
NexBotao BotaoInicialProjetor(4, 1, "BotaoInicial");
NexBotaoDuplo PowerPT(4, 2, "PowerPT");
NexBotaoDuplo freezePT(4, 3, "freezePT");
NexBotaoDuplo mutePT(4, 4, "mutePT");
NexBotao PT_ZOOMIN(4, 5, "PT_ZOOMIN");
NexBotao PT_ZOOMOUT(4, 6, "PT_ZOOMOUT");
NexBotao volProjetorAumentar(4, 7, "volPT_DOWN");
NexBotao volProjetorDiminuir(4, 8, "volPT_UP");
NexBotao configAdicionais(4, 9, "moreConfigs");
NexBotaoDuplo Projetor1(4, 10, "PT_esquerda");
NexBotaoDuplo Projetor2(4, 11, "PT_direita");

// BOTÕES AR-CONDICIONADO
// NexBotao BotaoInicial(5, 1, "BotaoInicial");
// NexBotaoDuplo PowerAC(5, 2, "PowerAC");
// NexBotao AC_1(5, 3, "AC_1");
// NexBotao AC_2(5, 4, "AC_2");
// NexBotao AC_3(5, 5, "AC_3");
// NexBotao AC_4(5, 6, "AC_4");
// NexBotaoDuplo AC_autoMode(5, 7, "AC_autoMode");
// NexBotaoDuplo AC_coolMode(5, 8, "AC_coolMode");
// NexBotaoDuplo AC_fanMode(5, 9, "AC_fanMode");
// NexBotaoDuplo AC_fanMEDIUM(5, 10, "AC_fanMEDIUM");
// NexBotaoDuplo AC_fanLOW(5, 11, "AC_fanLOW");
// NexBotaoDuplo AC_fanHIGH(5, 12, "AC_fanHIGH");
// NexBotaoDuplo AC_fanQUIET(5, 13, "AC_fanQUIET");
// NexTexto temp_AC(5, 14, "temp_AC");
// NexBotao AC_temp_UP(5, 15, "AC_temp_UP");
// NexBotao AC_temp_DOWN(5, 16, "AC_temp_DOWN");

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
  display.escutar(btnMenuSensor);
  btnMenuSensor.aoSoltar(enviarComandoSensor);

  display.escutar(interruptorLampada1);
  interruptorLampada1.aoSoltar([](){processarLampada(interruptorLampada1, "Lampada_1");});

  display.escutar(interruptorLampada2);
  interruptorLampada2.aoSoltar([](){processarLampada(interruptorLampada2, "Lampada_2");});

  display.escutar(interruptorLampada3);
  interruptorLampada3.aoSoltar([](){processarLampada(interruptorLampada3, "Lampada_3");});

  display.escutar(interruptorLampada4);
  interruptorLampada4.aoSoltar([](){processarLampada(interruptorLampada4, "Lampada_4");});

  display.escutar(Tela1);
  Tela1.aoSoltar([](){strcpy(telaEscolhida, "Tela_1");});

  display.escutar(Tela2);
  Tela2.aoSoltar([](){strcpy(telaEscolhida, "Tela_2");});

  display.escutar(SubirTela);
  SubirTela.aoSoltar([](){enviarComandoTela(SUBIR);});

  display.escutar(DescerTela);
  DescerTela.aoSoltar([](){enviarComandoTela(DESCER);});

  display.escutar(TelaParar);
  TelaParar.aoSoltar([](){enviarComandoTela(PARAR);});
}

void processarLampada(NexBotaoDuplo& interruptor, const char* nomeLampada)
{
    uint32_t estadoLampada;

    interruptor.get("val", estadoLampada);

    enviarComandoLampada(nomeLampada, estadoLampada);
}
