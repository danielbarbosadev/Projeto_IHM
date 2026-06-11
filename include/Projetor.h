#ifndef PROJETOR_H
#define PROJETOR_H

extern char projetorEscolhido[32];

void verificarMensagemProjetor(const String& mensagem);
void enviarComandoProjetor(uint32_t comandoProjetor);
void mostrarErroProjetor(const char* mensagemErro);

#endif