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

//* BOTÕES PROJETOR
NexBotao BotaoInicialProjetor(4, 1, "BotaoInicial");
NexBotaoDuplo congelarProjetor(4, 2, "freezePT");
NexBotaoDuplo mudoProjetor(4, 3, "mutePT");
NexBotao PT_ZOOMOUT(4, 4, "PT_ZOOMOUT");
NexBotao PT_ZOOMIN(4, 5, "PT_ZOOMIN");
NexBotao volProjetorAumentar(4, 6, "volPT_DOWN");
NexBotao volProjetorDiminuir(4, 7, "volPT_UP");
NexBotao configAdicionais(4, 8, "moreConfigs");
NexBotaoDuplo projetor1(4, 9, "PT_esquerda");
NexBotaoDuplo projetor2(4, 10, "PT_direita");
NexBotaoDuplo ambosprojetores(4, 11, "PT_ambos");
NexBotao powerProjetor(4, 12, "powerPT");

//* BOTÕES MORE CONFIGS PROJETOR
NexBotao BotaoVoltarProjetor(5, 1, "MenuProjetor");
NexBotao setaEsquerda(5, 2, "setaESQ");
NexBotao setaDireita(5, 3, "setaDIR");
NexBotao setaBaixo(5, 4, "setaDOWN");
NexBotao setaCima(5, 5, "setaUP");
NexBotao botaoSelect(5, 6, "botaoSelect");
NexBotao botaoEsc(5, 7, "botaoESC");

//* BOTÕES AR-CONDICIONADO
NexImagem PopUP(6, 1, "p0");
NexBotao BotaoInicial(6, 2, "BotaoInicial");
NexBotaoDuplo AC_1(6, 3, "AC_1");
NexBotaoDuplo AC_2(6, 4, "AC_2");
NexBotaoDuplo AC_3(6, 5, "AC_3");
NexBotaoDuplo AC_4(6, 6, "AC_4");
NexBotaoDuplo AC_autoMode(6, 7, "AC_autoMode");
NexBotaoDuplo AC_coolMode(6, 8, "AC_coolMode");
NexBotaoDuplo AC_fanMode(6,9, "AC_fanMode");
NexBotaoDuplo AC_fanMEDIUM(6, 10, "AC_fanMEDIUM");
NexBotaoDuplo AC_fanLOW(6, 11, "AC_fanLOW");
NexBotaoDuplo AC_fanHIGH(6, 12, "AC_fanHIGH");
NexBotaoDuplo AC_fanQUIET(6, 13, "AC_fanQUIET");
NexTexto temp_AC(6, 14, "t0");
NexBotao AC_temp_UP(6, 15, "AC_temp_UP");
NexBotao AC_temp_DOWN(6, 16, "AC_temp_DOWN");
NexBotaoDuplo AC_ALL(6, 17, "AC_ALL");
NexBotao PowerAC(6, 18, "powerAC");

//* BOTÕES TEMPERATURA
NexBotao BotaoInicialSensor(7, 1, "BotaoInicial");

//* BOTÕES TELA
NexBotao btnMenuInicialTela(8, 1, "BotaoInicial");
NexBotao DescerTela (8, 2, "telaDOWN");
NexBotao SubirTela (8, 3, "telaUP");
NexBotao TelaParar (8, 4, "telaFreeze");
NexBotaoDuplo Tela1(8, 5, "tela_Esquerda");
NexBotaoDuplo Tela2(8, 6, "tela_Direita");
NexBotaoDuplo todasTelas(8, 7, "ambasTelas");

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
  interruptorLampada1.aoSoltar([](){processarLampada(interruptorLampada1, "lampada_1");});

  display.escutar(interruptorLampada2);
  interruptorLampada2.aoSoltar([](){processarLampada(interruptorLampada2, "lampada_2");});

  display.escutar(interruptorLampada3);
  interruptorLampada3.aoSoltar([](){processarLampada(interruptorLampada3, "lampada_3");});

  display.escutar(interruptorLampada4);
  interruptorLampada4.aoSoltar([](){processarLampada(interruptorLampada4, "lampada_4");});

  display.escutar(projetor1);
  projetor1.aoSoltar([](){strcpy(projetorEscolhido, "projetor_1");});

  display.escutar(projetor2);
  projetor2.aoSoltar([](){strcpy(projetorEscolhido, "projetor_2");});

  display.escutar(powerProjetor);
  powerProjetor.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_POWER);});

  display.escutar(congelarProjetor);
  congelarProjetor.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_FREEZE);});

  display.escutar(mudoProjetor);
  mudoProjetor.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_MUTE);});

  display.escutar(configAdicionais);
  configAdicionais.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_MENU);});

  display.escutar(volProjetorAumentar);
  volProjetorAumentar.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_VOL_UP);});

  display.escutar(volProjetorDiminuir);
  volProjetorDiminuir.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_VOL_DOWN);});

  display.escutar(setaCima);
  setaCima.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_UP);});

  display.escutar(setaBaixo);
  setaBaixo.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_DOWN);});

  display.escutar(setaDireita);
  setaDireita.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_RIGHT);});

  display.escutar(setaEsquerda);
  setaEsquerda.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_LEFT);});

  display.escutar(botaoSelect);
  botaoSelect.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_ENTER);});

  display.escutar(botaoEsc);
  botaoEsc.aoSoltar([](){enviarComandoProjetor(EPSON_CMD_ESC);});

  display.escutar(Tela1);
  Tela1.aoSoltar([](){strcpy(telaEscolhida, "tela_1");});

  display.escutar(Tela2);
  Tela2.aoSoltar([](){strcpy(telaEscolhida, "tela_2");});

  display.escutar(todasTelas);
  todasTelas.aoSoltar([](){strcpy(telaEscolhida, "telas");});

  display.escutar(SubirTela);
  SubirTela.aoSoltar([](){enviarComandoTela(TELA_UP);});

  display.escutar(DescerTela);
  DescerTela.aoSoltar([](){enviarComandoTela(TELA_DOWN);});

  display.escutar(TelaParar);
  TelaParar.aoSoltar([](){enviarComandoTela(TELA_STOP);});

  display.escutar(PowerTV);
  PowerTV.aoSoltar([](){enviarComandotelevisao(TV_POWER);});

  display.escutar(HDMITV);
  HDMITV.aoSoltar([](){enviarComandotelevisao(TV_HDMI);});

  display.escutar(volTV_UP);
  volTV_UP.aoSoltar([](){enviarComandotelevisao(TV_VOL_UP);});

  display.escutar(volTV_DOWN);
  volTV_DOWN.aoSoltar([](){enviarComandotelevisao(TV_VOL_DOWN);});
  
  display.escutar(muteTV);
  muteTV.aoSoltar([](){enviarComandotelevisao(TV_MUTE);});
}

void processarLampada(NexBotaoDuplo& interruptor, const char* nomeLampada)
{
  uint32_t estadoLampada;

  interruptor.get("val", estadoLampada);

  enviarComandoLampada(nomeLampada, estadoLampada);
}
