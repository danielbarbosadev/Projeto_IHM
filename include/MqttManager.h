#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>

void configurarMQTT();
void conectarMQTT();
void garantirMQTTConectado();
void loopMQTT();

void publicarMensagem(const char* topico, const char* mensagem);
void publicarMensagemNoTopico(uint32_t indiceTopico, const char* mensagem);

bool mqttEstaConectado();

const char* obterTopicoPublicacao(uint32_t indiceTopico);
const char* obterTopicoRecebimento(uint32_t indiceTopico);
uint32_t obterTotalTopicosRecebimento();

typedef void (*CallbackMensagemMQTT)(const char* topico, const String& mensagem);

void registrarCallbackMensagem(CallbackMensagemMQTT callback);

#endif