/*Codigo para Executação de um datalog usando a placa lógica arduino e alguns componentes
  Esse trabalho é para vim de pesquisa de Iniciação Cientifíca da UFMT-Cuiabá
**Autor: Charles E. Cavalcante -> Graduando em Agronomia
  Componentes utilizados:
  • Microcontrolador Arduino UNO R3;
  • Sensor DTH22 -> Coneção: **1º Perna -> 5v, 2º A1, "" 4º GNG; (3º perna não utilizada)
  • Módulo Micro SD -> Coneção: ** MOSI -> pin 11, ** MISO -> pin 12,  ** CLK -> pin 13, ** CS -> pin 10
  • Módulo RTC DS3231 -> Coneção: **GND -> GND, ** VCC -> 5v,  ** SDA -> A4, ** SCL -> A5
  • protoboard 400 furo;
  ____________________________________________________________________________________________________*/
#include <SPI.h>      // Biblioteca de comunicação SPI Nativa
#include <SD.h>       //Inclui a Biblioteca para manipulação SD nativa
#include <Wire.h>     //Biblioteca para manipulação do protocolo I2C
#include <DS3231.h>   //Inclui a Biblioteca para manipulação do DS3231
#include "DHT.h"      //Inclui a Biblioteca para manipulação do DHT22

#define DHTPIN 2      //Define para o pino 2 a comunicação
#define DHTTYPE DHT22 // Define qual sensor será utilizado

const int chipSelect = 10; // declarando o pino responsável por ativar o módulo SD
File arquivo;              //Declarando o objeto responsavel para escrever/ler o arquivo no Cartão SD

DS3231 rtc;                // Declarando o objeto do tipo DS3231
RTCDateTime dataehora;     // Declarando o objeto do tipo RTCDateTime

DHT dht(DHTPIN, DHTTYPE);  // Declarando o objeto responsável pela comunicação/sensor

int i = 1;                 // Declarando o contador de nº de leituras

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);     // Iniciando a comunicação Serial

  rtc.begin();            // Iniciando o RTC DS3231
  //rtc.setDateTime(__DATE__, __TIME__);   // Configurando valores iniciais do RTC 3231 (carregar o codigo 2x para o Arduino, sendo que na segunda comente esse comando)
  dht.begin();

  Serial.println ("Verificando conexão com o cartão SD");
  Serial.println ("-----------------------------------");
  delay (1500);
  while (!SD.begin(chipSelect)) {       // Validação da conexão do cartão SD, Se inserido ele pode operar
    Serial.println("Falha no cartao ou não está inserido");   // se o cartão não estiver inserido um aviso aparecerar na Monitor serial;
  }

  // Se o cartão estiver inserido....
  Serial.println("Cartão SD Inserido com sucesso "); // Mensagem de aviso de cartão SD conectado
  Serial.println ("-------------------------------");
  delay (1500);
  Serial.println("Cartão SD Inicializado e pronto para escrita de dados!!! ");
  Serial.println ("----------------------------------------------------");

  // Bloco para o cabeçalho da Tabela no Arquivo texto
  String RotuloTabela = ""; //Declarando e limpando o Vetor de dados
  RotuloTabela = "  Data\t\t Hora \t   Temperatura(ºC)\tUmidade (%)";     // Cabeçalho da Tabela

  File arquivo = SD.open("DateLog.txt", FILE_WRITE); // Declarando e abrindo o arquivo onde será armazenado os dados da leitura do DTH e RTC

  if (arquivo) {
    arquivo.println(RotuloTabela);  // Escrevemos no arquivo o valor da string RotuloTabela e pulamos uma linha
    arquivo.close();           // Fechamos o arquivo
  }
  
  Serial.println("Vamos o que tem no arquivo_____________________________________________");
  arquivo = SD.open("DateLog.txt", FILE_READ); // Abre o Arquivo
  if (arquivo) {
    while (arquivo.available()) { // Exibe o conteúdo do Arquivo
      Serial.write(arquivo.read());
    }
    arquivo.close(); // Fecha o Arquivo após ler
  }
  else {
    Serial.println("Erro ao Abrir Arquivo .txt"); // Imprime na tela
  }

  delay (5000);
}

void loop()
{
  // put your main code here, to run repeatedly:
  dataehora = rtc.getDateTime();     //Atribuindo valores instantâneos de data e hora à instancia dataehora
  if (i == 1){
    Serial.println ("___________Dados Lidos do DHT22_____________ \n");      //Imprimindo o Dia
    Serial.println ("  Data\t\t Hora \t   Temperatura(ºC)\tUmidade (%)");
  }
  
  Serial.print(dataehora.day);      //Imprimindo o Dia
  Serial.print("/");
  Serial.print(dataehora.month);    //Imprimindo o Mês
  Serial.print("/");
  Serial.print(dataehora.year);     //Imprimindo o Ano
  Serial.print("\t");
  Serial.print(dataehora.hour);     //Imprimindo a Hora
  Serial.print(":");
  Serial.print(dataehora.minute);   //Imprimindo o Minuto
  Serial.print(":");
  Serial.print(dataehora.second);   //Imprimindo o Segundo
  Serial.print("\t\t");
  Serial.print(dht.readTemperature());
  Serial.print("\t\t");
  Serial.print(dht.readHumidity());
  Serial.println("");
  i +=1;
 
 /*// Declarando e Limpando Variáveis
  
  float temperatura = 0 ; 
  float umidade = 0;      
  String Data = "";
  String Time = "";
  String leitura = "";
  String dht22 = "";

  Data = (dataehora.day) + "/" + (dataehora.month) + "/" + (dataehora.year) + "\t";
  
  Time = (dataehora.hour) + ":" + (dataehora.minute)+ ":" + (dataehora.second) + "\t\t";
  
  temperatura = dht.readTemperature(); // Função que realiza a leitura da temperatura do sensor dht11
  umidade = dht.readHumidity();        // Função que realiza a leitura da umidade do sensor dht11

  // Se tudo estiver ok, escrevemos os dados a serem armazenados em uma String
  dht22 = (temperatura) + "\t\t" + (umidade);
  leitura = (Data) + "\t\t" + (Time) + "\t\t" + (dht22);
  
  Serial.println("Salvando dados no arquivo_____________________________________________");
  Serial.println(leitura);
 
  delay (2000);
  */
  File arquivo = SD.open("DateLog.txt", FILE_WRITE); // Abre o Arquivo
  if (arquivo) {
    //arquivo.println(leitura);  // Escrevemos no arquivo o valor da string RotuloTabela e pulamos uma linha
    arquivo.print(dataehora.day);      //Imprimindo o Dia
    arquivo.print("/");
    arquivo.print(dataehora.month);    //Imprimindo o Mês
    arquivo.print("/");
    arquivo.print(dataehora.year);     //Imprimindo o Ano
    arquivo.print("\t");
    arquivo.print(dataehora.hour);     //Imprimindo a Hora
    arquivo.print(":");
    arquivo.print(dataehora.minute);   //Imprimindo o Minuto
    arquivo.print(":");
    arquivo.print(dataehora.second);   //Imprimindo o Segundo
    arquivo.print("\t\t");
    arquivo.print(dht.readTemperature());
    arquivo.print("\t\t");
    arquivo.print(dht.readHumidity());
    arquivo.println("");
    arquivo.close();           // Fechamos o arquivo
  }

  delay (900000);
}
