#ifndef LAMPADAS_H
#define LAMPADAS_H

extern char lampadaEscolhida[32];

void guardarEstadoLampada(uint8_t numLampadaSalvar, bool estado);
bool carregarEstadoLampada(uint8_t numLampadaCarregar);
void verificarHandshakeLampadas(const String& mensagem);
void enviarComandoLampada(bool comandoLampada);

#endif