/*Codigo para Executação de um datalogger usando a placa lógica arduino e alguns componentes
  Esse trabalho é para vim de pesquisa de Iniciação Cientifíca da UFMT-Cuiabá
  
**Autor: Charles E. Cavalcante -> Graduando em Agronomia
  Componentes utilizados:
  • Microcontrolador Arduino UNO R3;
  • Sensor DHT22 -> Coneção: **1º Perna -> 5v, 2º pin 2, "" 4º GNG; (3º perna não utilizada);
  • Módulo Micro SD -> Coneção: ** MOSI -> pin 11, ** MISO -> pin 12,  ** CLK -> pin 13, ** CS -> pin 10;
  • Módulo RTC DS3231 -> Coneção: **GND -> GND, ** VCC -> 5v,  ** SDA -> A4, ** SCL -> A5;
  • protoboard 400 furos.
  ____________________________________________________________________________________________________*/
#include <SPI.h>      // Biblioteca de comunicação SPI Nativa
#include <SD.h>       //Inclui a Biblioteca para manipulação SD nativa
#include <Wire.h>     //Biblioteca para manipulação do protocolo I2C
#include <DS3231.h>   //Inclui a Biblioteca para manipulação do DS3231
#include "DHT.h"      //Inclui a Biblioteca para manipulação do DHT22

#define DHTPIN 2      //Define para o pino 2 a comunicação do DHT
#define DHTTYPE DHT22 // Define qual Modelo de sensor será utilizado (DHT22)

const int chipSelect = 10; // declarando o pino responsável por ativar o módulo SD
File arquivo;              //Declarando o objeto responsavel para escrever/ler o arquivo no Cartão SD

DS3231 rtc;                // Declarando o objeto do tipo DS3231
RTCDateTime dataehora;     // Declarando o objeto do tipo RTCDateTime

DHT dht(DHTPIN, DHTTYPE);  // Declarando o objeto responsável pela comunicação/sensor

int i = 1; 
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
  String RotuloTabela = ""; //Declarando e limpando a variavel que recebera o cabeçalho da tabela
  RotuloTabela = "  Data\t\t Hora \t   Temperatura(ºC)\tUmidade (%)";     // atribuindo valores do Cabeçalho da Tabela

  File arquivo = SD.open("DateLog.txt", FILE_WRITE); // Declarando e abrindo o arquivo onde será armazenado os dados da leitura do DTH e RTC

  if (arquivo) {
    arquivo.println(RotuloTabela);  // Escreve no arquivo o valor da string RotuloTabela e pulamos uma linha
    arquivo.close();           // Fechamento do arquivo
  }
  
  Serial.println("Dados contidos no arquivo");
  Serial.println("---------------------------");
  delay (1500);
  arquivo = SD.open("DateLog.txt", FILE_READ); // Abre o Arquivo
  if (arquivo) {
    while (arquivo.available()) { // Verifica existencia de dados no arquivo
      Serial.write(arquivo.read()); // Exibe o conteúdo do Arquivo enquanto encontrar dados 
    }
    arquivo.close(); // Fecha o Arquivo após ler
  }
  else {
    Serial.println("Erro ao Abrir Arquivo .txt"); // Imprime na tela caso ocorra erro ao abrir o arquivo
  }
  delay (1500);
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  dataehora = rtc.getDateTime();     //Atribuindo valores instantâneos de data e hora à instancia dataehora
  if (i == 1){
    Serial.println ("___________Dados Lidos do DHT22 & RTC 3231_____________ \n");      //Imprimindo o Dia
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
  Serial.print(dht.readTemperature());   //Imprimindo a temperatura
  Serial.print("\t\t");
  Serial.print(dht.readHumidity());      //Imprimindo a umidade
  Serial.println("");


 //Bloco para gravar os dados lidos pelo DHT22 e RTC
 
  File arquivo = SD.open("DateLog.txt", FILE_WRITE); // Abre o Arquivo
  if (arquivo) {
    arquivo.print(dataehora.day);      //Armazena no arquivo o Dia
    arquivo.print("/");
    arquivo.print(dataehora.month);    //Armazena no arquivo o Mês
    arquivo.print("/");
    arquivo.print(dataehora.year);     //Armazena no arquivo o Ano
    arquivo.print("\t");
    arquivo.print(dataehora.hour);     //Armazena no arquivo a Hora
    arquivo.print(":");
    arquivo.print(dataehora.minute);   //Armazena no arquivo o Minuto
    arquivo.print(":");
    arquivo.print(dataehora.second);   //Armazena no arquivo o Segundo
    arquivo.print("\t\t");
    arquivo.print(dht.readTemperature());   //Armazena no arquivo a Temperatura
    arquivo.print("\t\t");
    arquivo.print(dht.readHumidity());      //Armazena no arquivo a Umidade
    arquivo.println("");
    arquivo.close();           // Fechamos o arquivo
  }

  delay (900000); // Intervalo de 15 minutos para a proxima leitura e gravação no arquivo
  i +=1;
}
