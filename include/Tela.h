#ifndef TELA_H
#define TELA_H

extern char telaEscolhida[32];

void verificarMensagemTela(const String& mensagem);
void enviarComandoTela(uint32_t comandoTela);
void mostrarErroTela(const char* mensagemErro);


#endif