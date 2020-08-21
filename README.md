# Monitoramento de sala de ordenha usando um Datalogger

Esse projeto tem como o objetivo a Automação de baixo custo para controlar e monitorar o bem-estar animal em salas de ordenha,
o qual irá captar a temperatura e umidade do ar e armazenar esses dados junto com a data e hora em um cartão de memória para posteriores análises estatísticas determinando o ITU.

Esse trabalho é a fim de Pesquisa de Iniciação Cientifíca da UFMT-Cuiabá.
Pesquisa vinculada ao Projeto AUTOMAÇÃO E INTELIGÊNCIA ARTIFICIAL EM PROCESSOS AGROPECUÁRIOS E FLORESTAIS.

Faculdade de Agronomia e Zootecnia - FAAZ/UFMT;
Orientador: Prof. Dr. Pedro Hurtado de Mendoza Borges;
Departamento de Solos e Engenharia Rural - DSER;
Autor: Charles Esteffan Cavalcante -> Graduando em Agronomia.


O Código é para a confecção de um datalogger usando a placa lógica arduino (R3) e alguns componentes.
# Componentes utilizados:
  - Microcontrolador Arduino UNO R3;
  - Sensor DTH22 -> Conexão: **1º Perna -> 5v, 2º pin2, ** 4º GNG; (3º perna não utilizada);
  - Módulo Micro SD -> Conexão: ** MOSI -> pin 11, ** MISO -> pin 12,  ** CLK -> pin 13, ** CS -> pin 10;
  - Módulo RTC DS3231 -> Conexão: **GND -> GND, ** VCC -> 5v,  ** SDA -> A4, ** SCL -> A5;
  - Protoboard 400 furos.

