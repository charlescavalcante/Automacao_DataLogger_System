# Monitoramento de sala de ordenha usando um Datalogger

Esse projeto tem como o objetivo a Automação de baixo custo para controlar e monitorar o bem-estar animal em salas de ordenha,  qual irá captar a temperatura e umidade do ar e armazenar esses dados junto com a data e hora em um cartão de memória para posteriores análises estatísticas.

Esse trabalho é para fins de Pesquisa de Iniciação Cientifíca da UFMT-Cuiabá.
Pesquisa vinculada ao Projeto AUTOMAÇÃO E INTELIGÊNCIA ARTIFICIAL EM PROCESSOS AGROPECUÁRIOS E FLORESTAIS.

Orientador: Prof. Dr. PEDRO HURTADO DE MENDOZA BORGES
Autor: Charles E. Cavalcante -> Graduando em Agronomia
Faculdade de Agronomia e Zootecnia - FAAZ/UFMT

O Codigo é para a confecção de um datalogger usando a placa lógica arduino (R3) e alguns componentes.
** Componentes utilizados:
  • Microcontrolador Arduino UNO R3;
  • Sensor DTH22 -> Coneção: **1º Perna -> 5v, 2º pin2, "" 4º GNG; (3º perna não utilizada);
  • Módulo Micro SD -> Coneção: ** MOSI -> pin 11, ** MISO -> pin 12,  ** CLK -> pin 13, ** CS -> pin 10;
  • Módulo RTC DS3231 -> Coneção: **GND -> GND, ** VCC -> 5v,  ** SDA -> A4, ** SCL -> A5;
  • protoboard 400 furos.

