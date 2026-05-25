//* ======================
//* BIBLIOTECAS
//*=======================
#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h> 
#include <PubSubClient.h>

//* ======================
//* ARQUIVOS LOCAIS
//*=======================
#include "secrets.h"
#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"

//* ======================
//* INSTÂNCIAS
//*=======================
WiFiClient wifiClient;
WiFiClientSecure wifiClientSecure;

PubSubClient mqttClient;

CallbackMensagemMQTT callbackDaAplicacao = nullptr;


void registrarCallbackMensagem(CallbackMensagemMQTT callback)
{
    callbackDaAplicacao = callback;

    if (callbackDaAplicacao != nullptr)
    {
        debugInfo("Callback da aplicação registrado com sucesso");
    }
    else
    {
        debugErro("Callback da aplicação não foi registrado");
    }
}

const char *obterTopicoPublicacao(uint32_t indiceTopico)
{
    if (indiceTopico < 0 || indiceTopico >= TOTAL_TOPICOS_PUBLICAR)
    {
        debugErro("Indice inválido para tópico de publicação: " + String(indiceTopico));
        return "";
    }
    return TOPICOS_PUBLICAR[indiceTopico];
}

const char *obterTopicoRecebimento(uint32_t indiceTopico)
{
    if (indiceTopico < 0 || indiceTopico >= TOTAL_TOPICOS_RECEBER)
    {
        debugErro("Indice inválido para tópico de publicação: " + String(indiceTopico));
        return "";
    }
    return TOPICOS_RECEBER[indiceTopico];
}

void callbackInternoMQTT(char* topico, byte* payload, uint32_t tamanho)
{
    String mensagem = "";

    //Transformando numeros em letras da tabela ASCI
    for (uint32_t i = 0; i < tamanho; i++) 
    {
        mensagem += (char)payload[i];
    }

    debugInfo("=======================");
    debugInfo(" Mensagem MQTT recebida");
    debugInfo("=======================");
    debugInfo("Tópico: " + String(topico));
    debugInfo("Mensagem: " + mensagem);

    if(callbackDaAplicacao != nullptr) 
    {
        callbackDaAplicacao(topico, mensagem);
    }

    else 
    { 
        debugErro("Mensagem recebida, mas nenhum callback da aplicação foi registrado");
    }
}

void configurarMQTT()
{
    debugInfo("=========================");
    debugInfo(" Configurando MQTT...");
    debugInfo("=========================");

    if (USAR_AWS_IOT)
    {
     debugInfo("Modo seleconado: AWS IoT Core."); 
     
     if(strlen(AWS_CERT_CA) > 100)
     {
        debugInfo("AWS Certificado CA do broker MQTT configurado");
        wifiClientSecure.setCACert(AWS_CERT_CA);
     }
     else
     {
       debugErro("Certificado CA não configurado.");  
     }

     if(strlen(AWS_CERT_CRT) > 100)
     {
        debugInfo("AWS Certificado CRT do broker MQTT configurado");
        wifiClientSecure.setCertificate(AWS_CERT_CRT);
     }
     else
     {
        debugErro("Certificado CRT não configurado.");
     }

     if(strlen(AWS_CERT_PRIVATE) > 100)
     {
        debugInfo("AWS Certificado PRIVATE do broker MQTT configurado");
        wifiClientSecure.setPrivateKey(AWS_CERT_PRIVATE);
     }
     else
     {
        debugErro("Certificado PRIVATE não configurado.");
     }

     mqttClient.setClient(wifiClientSecure);
     mqttClient.setServer(AWS_IOT_ENDPOINT, AWS_IOT_PORT);

     debugInfo("Endpoint AWS IoT: " + String(AWS_IOT_ENDPOINT));
     debugInfo("Porta AWS IoT: " + String(AWS_IOT_PORT));
    }

    else if (MQTT_TLS)
    {
        debugInfo("Modo seleconado: MQTT com TLS.");
        if(strlen(MQTT_CERTIFICADO_CA) > 100)
        {
            debugInfo("Certificado CA do broker MQTT configurado");
            wifiClientSecure.setCACert(MQTT_CERTIFICADO_CA);
        }
        else
        {
            debugErro("Certificado não configurado. Usando setInsecure apenas para teste.");
            wifiClientSecure.setInsecure();

        }

        mqttClient.setClient(wifiClientSecure);
        mqttClient.setServer(MQTT_BROKER, MQTT_PORTA);

        debugInfo("Broker MQTT: " + String(MQTT_BROKER));
        debugInfo("Porta MQTT: " + String(MQTT_PORTA));
    }

    else 
    {
        debugInfo("Modo selecionar: MQTT sem TLS.");
        
        mqttClient.setClient(wifiClient);
        mqttClient.setServer(MQTT_BROKER, MQTT_PORTA);

        debugInfo("Broker MQTT: " + String(MQTT_BROKER));
        debugInfo("Porta MQTT: " + String(MQTT_PORTA));

    }

    mqttClient.setCallback(callbackInternoMQTT);
    debugInfo("Callback interno no MQTT configurado");
}

void conectarMQTT()
{
    if (!WiFiEstaConectado)
    {
        debugErro("MQTT não pode conectar porque o WiFi está deconectado.");
        return;
    }

    debugInfo("=========================");
    debugInfo("Iniciando conexão MQTT...");
    debugInfo("=========================");

    uint32_t tentativasMQTT = 0;
    uint32_t maxTentativasMQTT = 5;

    while(!mqttClient.connected() && tentativasMQTT < maxTentativasMQTT)
    {
        debugInfo("Tentando conectar ao broker MQTT. Tentativa: " + String(tentativasMQTT));

        bool conectado = false;

        if(USAR_AWS_IOT)
        {
            conectado = mqttClient.connect(AWS_IOT_CLIENT_ID);
        }

        else
        {
            if(strlen(MQTT_USUARIO) > 0)
            {
                debugInfo("Conectando MQTT com usuário e senha");

                conectado = mqttClient.connect(
                    MQTT_CLIENT_ID, 
                    MQTT_USUARIO, 
                    MQTT_SENHA);
            }
            else // Conexão em modo anônimo
            {
                debugInfo("Conectando MQTT sem usuário e senha");
                conectado = mqttClient.connect(MQTT_CLIENT_ID);
            }
        }
        if (conectado)
        {
            debugInfo("MQTT conectado com sucesso.");
            uint32_t totalTopicos = obterTotalTopicosRecebimento();

            debugInfo("Total de tópicos para inscrição: " + String(totalTopicos));

            for(uint32_t i = 0; i < totalTopicos; i++)
            {
                const char* topico = obterTopicoRecebimento(i);

                bool inscrito = mqttClient.subscribe(topico);

                if(inscrito)
                {
                    debugInfo("Inscrito no tópico: " + String(topico));
                }
                else
                {
                    debugErro("Falha ao se inscrever no tópico: " + String(topico));
                }
            }

            publicarMensagemNoTopico(0, "ESP32 conectado ao MQTT");
        }
        else 
        {
            debugErro("Falha ao conectar no MQTT. Código de erro: " + String(mqttClient.state()));
            tentativasMQTT++;
            delay(2000);
        }
    } // FIM DO WHILE
    if(!mqttClient.connected())
    {
        debugErro("Não foi possível conectar ao broker MQTT após " + String(maxTentativasMQTT) + " tentativas");
    }
}

uint32_t obterTotalTopicosRecebimento()
{
    return TOTAL_TOPICOS_RECEBER;
}

void garantirMQTTConectado()
{
    if(!WiFiEstaConectado())
    {
        debugErro("MQTT não reconectado porque o WiFi está desconectado.");
        return;
    }

    if(!mqttClient.connected())
    {
        debugErro("MQTT desconectado. Tentando reconectar...");
        conectarMQTT();
    }
}

void loopMQTT()
{
    mqttClient.loop();
}

void publicarMensagem(const char* topico, const char* mensagem)
{
    if(!mqttClient.connected())
    {
        debugErro("Não foi possível publicar. MQTT deconectado.");
        return;
    }

    bool publicado = mqttClient.publish(topico, mensagem);

    if(publicado)
    {
        debugInfo("Mensagem publicada via MQTT.");
        debugInfo("Tópico: " + String(topico));
        debugInfo("Mensagem: " + String(mensagem));
    }
    else
    {
        debugErro("Falha ao publicar mensagem no tópico: " + String(topico));
    }
}

void publicarMensagemNoTopico(uint32_t indiceTopico, const char* mensagem)
{
    const char* topico = obterTopicoPublicacao(indiceTopico);

    if(strlen(topico) == 0)
    {
        debugErro("Não foi possível publicar. Indice de tópico inválido: " + String(indiceTopico));
        return;
    }

    publicarMensagem(topico, mensagem);
}

bool mqttEstaConectado()
{
    return mqttClient.connected();
}


