#ifndef AR_CONDICIONADO_H
#define AR_CONDICIONADO_H

extern char AC_Escolhido[32];

void verificarMensagemArCondicionado(const String& mensagem);
void enviarComandoAC(uint32_t comandoAC);
void mostrarErroAc(const char* mensagemErro);


#endif