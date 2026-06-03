#ifndef PROJETOR_H
#define PROJETOR_H

extern char projetorEscolhido[32];

void verificarHandshakeProjetor(const String& mensagem);
void enviarComandoProjetor(uint32_t comandoProjetor);

#endif