#ifndef TELA_H
#define TELA_H

extern char telaEscolhida[32];

void verificarHandshakeTela(const String& mensagem);
void enviarComandoTela(uint32_t comandoTela);


#endif