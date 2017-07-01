#include <EEPROM.h>
#include <UIPEthernet.h>
#include <PubSubClient.h>
#include <RotaryEncoder.h>
//#include <Servo.h>
#include "configuracao.h"

RotaryEncoder encoder(A2, A3);
//Servo servoBau;
/*


//DECLARAÇÃO DOS PINOS

//OUTPUTS
const int releLuzCapitao = 2;
const int releLuzConves =    3;
const int releGaveta = 4;
const int releSaida  = 5;
const int ledOn = 6;
const int ledConfig = 7;
const int botaoStart = 8;
//INPUTS
const int sensorGaveta =  A0;
const int sensorbarco1 = A1;
const int sensorbarco2 = A4;
const int sensorbarco3 = A5;
const int sensorBau = A6;




//DECLARAÇÃO DAS VARIÁVEIS

boolean start = false;
boolean startSensores = false;
boolean abriuGaveta = false;
boolean abriuSaida = false;
boolean abriuConves;
boolean luzCapitao = true;
boolean luzConves = false;
boolean modoManual = false;
boolean etapa1Timao = false;
boolean etapa2Timao = false;

int posicaoTimao = 0;
*/
void setup() {
  // put your setup code here, to run once:
//Serial.begin(9600);
//Serial.println("Inicio");
  
pinMode(releLuzCapitao,OUTPUT);
pinMode(releLuzConves,OUTPUT);
pinMode(relePassagem,OUTPUT);
pinMode(releGaveta,OUTPUT);
pinMode(releSaida,OUTPUT);
pinMode(releBau,OUTPUT);
pinMode(ledOn,OUTPUT);
pinMode(ledConfig,OUTPUT);
//digitalWrite(releSaida,LOW);
digitalWrite(releBau,HIGH);
//digitalWrite(relePassagem,HIGH);//OK
digitalWrite(relePassagem,LOW);// NOVO RELE
digitalWrite(releSaida,HIGH);//OK
digitalWrite(releGaveta,HIGH);//OK
digitalWrite(releLuzCapitao,HIGH);//OK NORMALMENTE FECHADO
digitalWrite(releLuzConves,HIGH);//NORMALMENTE ABERTO
ligarLuzCapitao();
desligarLuzConves();
//pinMode(botaoStart,INPUT_PULLUP);
//modoManual = digitalRead(botaoStart);
//if(!modoManual){
ligarLed(ledConfig);
Ethernet.begin(mac);
//Serial.println(Ethernet.localIP());
client.setServer(server, 1883);
client.setCallback(callback);
piscarLed(ledConfig,4);


//}

}

void loop() {

  
/*
  if(modoManual){
    fecharPassagem();
    fecharSaida();
    startSensores = true;
    ligarLed(ledOn);
    start = false;
    delay(200);
   if(startSensores){
        checkAlvo();
        checkQuadro();
        //checkChavePassagem();
        //checkChaveSaida();
                }
  //imprimir();
  delay(300);
  }
*/
 
if(!modoManual){
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 

if(preparar){
  //Serial.print("lendo  ");
  prepararBau();
 
}
if(start){
  //Serial.println("comecou");
    //fecharPassagem();
    fecharSaida();
    fecharGaveta();
    
    //apagarConves();
    ligarLuzCapitao();
    startSensorGaveta = true;
    //ligarLed(ledOn);
    start = false;
    
    delay(200);
}
  
if(startSensorGaveta){
  
  checkGaveta();
  //checkChavePassagem();
  //checkChaveSaida();
}
if(startSensorBarcos){
  
  checkBarcos();
}
if(startSensorBau){
  
  checkBau();
}
if(startSensorTimao){
  
  checkTimao();
}

}


  //imprimir();
delay(10);

  
}//FIM DO LOOP



//FUNÇÕES







void imprimir(){

  Serial.print("Sensor Bau =  ");
  Serial.print(analogRead(sensorBau));
  Serial.print("  Sensor Gaveta =  ");
  Serial.println(analogRead(sensorGaveta));
  
  //Serial.print("\t Sensor Barcos =  ");
 // Serial.println(digitalRead(sensorBarco1));
}





void callback(char* topic, byte* payload, unsigned int length) {

  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] "); 
  
  if(payload[0] =='0'){
    //Serial.println("Start");
    start = true;
  }else{
  piscarLed(ledOn,1);
  if(payload[0] =='1'){
    //Serial.println("ChegouPassagem");
    
    if(payload[1] == '1'){
      //Serial.println("ABRIU");
      abrirPassagem();
    }
    else fecharPassagem();
    
  }else{
    if(payload[0] =='2'){
    //Serial.println("ChegouSaida");
     if(payload[1] == '1'){
      //Serial.println("ABRIU");
      abrirSaida();
    }
    else fecharSaida();
  } 
  else{
    if(payload[0] =='3'){
    //Serial.println("ChegouGaveta");
     if(payload[1] == '1'){
      //Serial.println("ABRIU");
      abrirGaveta();
    }
    else fecharGaveta();
    
  } else {
    if(payload[0] =='4'){
    //Serial.println("ChegouLuzCapitao");
     if(payload[1] == '1'){
      //Serial.println("ABRIU");
      ligarLuzCapitao();
    }
    else desligarLuzCapitao();
    
  }
  else {
    if(payload[0] =='5'){
    //Serial.println("ChegouLuzConves");
     if(payload[1] == '1'){
      //Serial.println("ABRIU");
      ligarLuzConves();
    }
    else desligarLuzConves();
    
  }
  else {
    if(payload[0] =='6'){
    //Serial.println("ChegouBau");
     if(payload[1] == '1'){
      //Serial.println("ABRIU");
      ligarLuzBau();
    }
    else desligarLuzBau();
    
  }
  else{
    if(payload[0] =='7'){
    //Serial.println("ChegouTrovao");
     if(payload[1] == '1'){
      //Serial.println("ABRIU");
      efeitoTrovao2();
    }
    else efeitoTrovao2();
  }
  else{
    if(payload[0] =='8'){
    //Serial.println("chegouAcaobau");
     if(payload[1] == '1'){
      //Serial.println("ABRIU");
      funcaoAcaoBau();
    }
    else funcaoAcaoBau();
  }
  else{
    if(payload[0] =='9'){
    //Serial.println("ChegouTrovao");
     if(payload[1] == '1'){
      //Serial.println("ABRIU");
      efeitoTrovao1();
    }
    else efeitoTrovao1();
  }
  else{
    if(payload[0] =='a'){
    
     if(payload[1] == '1'){
      
      
    }
    
  }
  else{
    if(payload[0] =='b'){
    
     if(payload[1] == '1'){
      
      
    }
  
  }
  else{
    if(payload[0] =='c'){
    
     if(payload[1] == '1'){
      
      
    }
  
  }
  
  
  
  }}}}}}}}}}}}

  /*
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }*/
  Serial.println();
}


void piscarLed(int porta,int quantidade){

  for(int i=0;i<quantidade;i++){
    desligarLed(porta);
    delay(100);
    ligarLed(porta);
    delay(100);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClientP")) {
      //Serial.println("connected");
      desligarLed(ledConfig);
      ligarLed(ledOn);
      client.publish("topicoArduinoProntoP","1");
      delay(1000);
      preparar = true;
      client.subscribe("topicoPrincipalP");
    } else {
      //Serial.print("failed, rc=");
      piscarLed(ledConfig,2);
      //Serial.print(client.state());
      //Serial.println(" try again in 3 seconds");
      // Wait 5 seconds before retrying
      delay(3000);
    }
  }
}


void atualizaEEPROM(){
 // lê o valor na entrada analógica e guarda em val
  int hiByteLeitura = EEPROM.read(0);
  int loByteLeitura = EEPROM.read(1);
   int val = 256*hiByteLeitura + loByteLeitura ;
   val = val+1;  
   if(val > 40000){
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
      }
   }
  // divide val que é um inteiro de 16 bits em dois bytes
  
   byte hiByte = highByte(val);
   byte  loByte = lowByte(val);
   
  EEPROM.write(0, hiByte);
  EEPROM.write(1, loByte);
  char buffer[7];
  dtostrf(val, 7, 0, buffer);
  
  client.publish("contagem_piratas",buffer);
  
}







