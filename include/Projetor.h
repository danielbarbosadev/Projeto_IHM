#ifndef PROJETOR_H
#define PROJETOR_H

extern const char *comandoProjetor;

void verificarHandshakeProjetor(const String& mensagem);
void enviarComandoProjetor(uint8_t comandoProjetor);
void processarComandoProjetor(uint32_t estadoPowerProjetor);

#endif