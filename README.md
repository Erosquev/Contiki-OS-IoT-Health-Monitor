# Contiki OS IoT Health Monitor

Este projeto foi desenvolvido na disciplina de Sistemas Operacionais Ciberfísicos do curso de Ciência da Computação. Trata-se de uma simulação de um sistema IoT para monitoramento de saúde (e-Health) utilizando o sistema operacional Contiki OS. O sistema simula a leitura de sensores vitais e utiliza comunicação entre processos para gerar alertas de emergência.

## Descrição do Projeto

O software emula três sensores biomédicos independentes (Cardíaco, Oxímetro e Termômetro) que operam concorrentemente. Cada sensor é um processo leve (protothread) que gera dados simulados e verifica se os valores estão dentro de faixas seguras. Caso uma anomalia seja detectada, um evento é disparado para um processo central de "Alerta", demonstrando o funcionamento da comunicação inter-processos (IPC) orientada a eventos do Contiki.

## Funcionalidades

- Monitoramento de Frequência Cardíaca (BPM) com detecção de Bradicardia (<50) e Taquicardia (>90).
- Monitoramento de Saturação de Oxigênio (SpO2) com alerta de Hipóxia (<90%).
- Monitoramento de Temperatura Corporal com detecção de Hipotermia (<35°C) e Febre (>37°C).
- Sistema centralizado de recebimento e exibição de alertas.
- Geração de dados aleatórios para fins de simulação e teste de estresse.

## Estrutura Técnica

O projeto explora os seguintes recursos do kernel do Contiki OS:

- Protothreads: Uso das macros PROCESS_THREAD para criar multitarefa cooperativa leve.
- Event Timers (etimer): Controle temporal para a periodicidade das leituras dos sensores (a cada 3 segundos).
- Eventos e Mensagens: Uso da função process_post() para comunicação assíncrona entre os processos sensores e o processo de alerta.

## Pré-requisitos

Para compilar e executar este projeto, é necessário um ambiente de desenvolvimento compatível com Contiki OS, como:

- Instant Contiki (Máquina Virtual padrão).
- Ambiente Linux com toolchain instalada.
- Simulador Cooja (para simulação de rede e hardware).

## Como Executar

A execução depende do alvo (target) desejado. Para rodar como uma aplicação nativa no Linux para testes de lógica:

1. Navegue até o diretório do projeto via terminal.
2. Compile o projeto direcionando para o alvo nativo:

make TARGET=native

3. Execute o binário gerado (o nome do arquivo geralmente corresponde ao nome do arquivo .c principal ou do projeto):

./nome_do_executavel.native

Caso utilize o simulador Cooja, basta criar uma nova simulação, adicionar um "Mote Type" apontando para este código fonte e instanciar os nós.

## Exemplo de Saída (Log)

Abaixo um exemplo do comportamento esperado no terminal:

[BATIMENTOS] 72 bpm
[OXIGÊNIO] 98%
[TEMPERATURA] 36.5°C
[BATIMENTOS] 130 bpm
Batimento cardíaco está alto!
>>> ALERTA RECEBIDO: Alerta batimento alto
[TEMPERATURA] 39.2°C
Usuário está com febre!
>>> ALERTA RECEBIDO: Temperatura está muito alta!

## Autor

- Eros Felipe de Quevedo dos Santos
- Curso: Bacharelado em Ciência da Computação
