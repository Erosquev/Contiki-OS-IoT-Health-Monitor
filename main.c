/*
 * Aluno: Eros Felipe de Quevedo dos Santos
 * Curso: Ciência da Computação
 * Disciplina: Sistemas Operacionais Ciberfísicos
 */

#include "contiki.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sys/etimer.h"

// -------------------------------------------------------------------
// Declaração dos Processos
// -------------------------------------------------------------------
PROCESS(medidorCardiaco, "medidorCardiaco");
PROCESS(medidorTemperatura, "medidorTemperatura");
PROCESS(medidorOxigenio, "medidorOxigenio");
PROCESS(alerta, "alerta");

// Defino quais processos iniciam automaticamente quando o sistema começa
AUTOSTART_PROCESSES(&medidorCardiaco, &medidorTemperatura, &medidorOxigenio, &alerta);

// -------------------------------------------------------------------
// Processo: Medidor Cardíaco
// -------------------------------------------------------------------
PROCESS_THREAD(medidorCardiaco, ev, data)
{
    // Timer do Contiki para controlar o intervalo de medições
    static struct etimer timer;
    // Variável para armazenar os batimentos por minuto
    static int bpm; 

    PROCESS_BEGIN(); 

    // Inicializa o gerador de números aleatórios com o clock atual
    // O mesmo sendo utilizado para o restante dos processos
    srand(clock_time()); 
    
    // Define o timer para 3 segundos
    etimer_set(&timer, CLOCK_SECOND * 3); 

    while(1) 
    {
        // Espera até que o timer expire
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        // Gera valor aleatório entre 20 e 140 bpm
        bpm = 20 + rand() % 121;
        printf("[BATIMENTOS] %d bpm\n", bpm);

        // Verifica se o batimento está abaixo ou acima do normal e envia alerta
        if(bpm < 50) 
        {
            printf("Batimento cardíaco está baixo!\n");
            process_post(&alerta, PROCESS_EVENT_MSG, (void*)"Alerta batimento baixo");
        } 
        else if(bpm > 90) 
        {
            printf("Batimento cardíaco está alto!\n");
            process_post(&alerta, PROCESS_EVENT_MSG, (void*)"Alerta batimento alto");
        }

        // Reinicia o timer para o próximo ciclo
        etimer_reset(&timer);
    }

    PROCESS_END(); 
}

// -------------------------------------------------------------------
// Processo: Medidor de Oxigênio
// -------------------------------------------------------------------
PROCESS_THREAD(medidorOxigenio, ev, data)
{
    // Timer para medir o oxigênio a cada 3 segundos
    static struct etimer timer; 
    // Armazena o valor da saturação de oxigênio
    static int oxigenio; 

    PROCESS_BEGIN();

    // Define intervalo de 3 segundos
    etimer_set(&timer, CLOCK_SECOND * 3); 

    while(1) 
    {
        // Espera o timer expirar antes de medir novamente
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        // Gera valor aleatório de oxigênio entre 80% e 100%
        oxigenio = 80 + rand() % 21;
        printf("[OXIGÊNIO] %d%%\n", oxigenio);

        // Se a saturação estiver baixa, gera um alerta
        if(oxigenio < 90) 
        {
            printf("A saturação está baixa!\n");
            process_post(&alerta, PROCESS_EVENT_MSG, (void*)"Oxigenio baixo!");
        }

        // Reinicia o timer
        etimer_reset(&timer);
    }

    PROCESS_END();
}

// -------------------------------------------------------------------
// Processo: Medidor de Temperatura
// -------------------------------------------------------------------
PROCESS_THREAD(medidorTemperatura, ev, data)
{
    // Timer de controle de tempo
    static struct etimer timer; 
    // Variável para armazenar temperatura
    static float temp; 

    PROCESS_BEGIN();

    // Intervalo de 3 segundos
    etimer_set(&timer, CLOCK_SECOND * 3); 

    while(1) 
    {
        // Espera o timer expirar
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        // Gera valor aleatório entre 34.0°C e 41.0°C
        temp = 34 + (rand() % 70) / 10.0;
        printf("[TEMPERATURA] %.1f°C\n", temp);

        // Verifica se a temperatura está fora do normal e gera alertas
        if(temp < 35.0) 
        {
            printf("Usuário está com hipotermia!\n");
            process_post(&alerta, PROCESS_EVENT_MSG, (void*)"Temperatura está muito baixa!");
        } 
        else if(temp > 37.0) 
        {
            printf("Usuário está com febre!\n");
            process_post(&alerta, PROCESS_EVENT_MSG, (void*)"Temperatura está muito alta!");
        }

        // Reinicia o timer
        etimer_reset(&timer);
    }

    PROCESS_END();
}

// -------------------------------------------------------------------
// Processo: Central de Alertas
// -------------------------------------------------------------------
PROCESS_THREAD(alerta, ev, data)
{
    PROCESS_BEGIN();

    while(1)
    {
        // Espera qualquer evento chegar
        PROCESS_WAIT_EVENT();

        // Se o evento recebido for uma mensagem, exibe o alerta
        if (ev == PROCESS_EVENT_MSG) 
        {
            printf(">>> ALERTA RECEBIDO: %s\n", (char *)data);
        }
    }

    PROCESS_END();
}
