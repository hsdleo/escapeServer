
#include <UIPEthernet.h>
#include <PubSubClient.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress ip(192, 168, 1, 102);
//IPAddress server(192,168,1,3);
IPAddress server(192,168,0,100);
EthernetClient ethClient;
PubSubClient client(ethClient);




//DECLARAÇÃO DOS PINOS

//OUTPUTS
const int relePassagem = 2;
const int releSaida =    3;
const int releGiroflex = 4;
const int releLuzCela  = 5;
const int ledOn       = A2;
const int ledConfig   = A3;

//INPUTS
const int sensorAlvo =  A0;
const int sensorQuadro = A1;
const int botaoStart = 6;
const int botaoStart2 = 7;



//DECLARAÇÃO DAS VARIÁVEIS

boolean start = false;
boolean startSensores = false;
boolean abriuPassagem = false;
boolean abriuSaida = false;
boolean estadoChaveLuzCela;
boolean luzCela = true;
boolean modoManual = false;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Inicio");

pinMode(relePassagem,OUTPUT);
pinMode(releSaida,OUTPUT);
pinMode(releGiroflex,OUTPUT);
pinMode(releLuzCela,OUTPUT);
pinMode(ledOn,OUTPUT);
digitalWrite(relePassagem,HIGH);
//digitalWrite(releSaida,LOW);
digitalWrite(releSaida,HIGH);
digitalWrite(releGiroflex,HIGH);
digitalWrite(releLuzCela,HIGH);

pinMode(botaoStart2,INPUT_PULLUP);
pinMode(botaoStart,INPUT_PULLUP);

//modoManual = digitalRead(botaoStart);
//if(!modoManual){

piscarLed(ledConfig,3);
Ethernet.begin(mac);
//Ethernet.begin(mac, ip);
Serial.println(Ethernet.localIP());
client.setServer(server, 1883);
client.setCallback(callback);
piscarLed(ledConfig,4);
ligarLed(ledConfig);
//}

}

void loop() {

  
  if(!modoManual){
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 
  
if(start){
  Serial.println("comecou");
    fecharPassagem();
    fecharSaida();
    startSensores = true;
    ligarLed(ledOn);
    start = false;
    delay(200);
}
  

if(startSensores){
  checkAlvo();
  checkQuadro();
  //checkChavePassagem();
  //checkChaveSaida();
}
  //imprimir();
  delay(50);


  }

  
}//FIM DO LOOP



//FUNÇÕES

void checkAlvo(){
    if(!abriuPassagem){
      abriuPassagem = true;
      for(int i = 0;i<3;i++){
        if(analogRead(sensorAlvo) > 600){
            abriuPassagem = false;
        }
      }
      if(abriuPassagem) {
        abrirPassagem();
        client.publish("topicoArduinoPronto","2");
        desligarLuzCela();  //LIGAR GIROFLEX
        //abriuSaida = false;
      }
   }
}

void checkQuadro(){
    if(!abriuSaida){
      abriuSaida = true;
      for(int i = 0;i<2;i++){
        if(digitalRead(sensorQuadro) == 1){
            abriuSaida = false;
        }
      }
      //if(abriuSaida) abrirSaida();
      if(abriuSaida){
        abrirSaida();
        client.publish("topicoArduinoPronto","3");
        delay(300);

        //abriuPassagem = false;
      }
       
   }
}


void abrirPassagem(){
  digitalWrite(relePassagem,HIGH);
}
void fecharPassagem(){
  digitalWrite(relePassagem,LOW);
  abriuPassagem = false;
}
void abrirSaida(){
  digitalWrite(releSaida,HIGH);
}
void fecharSaida(){
  digitalWrite(releSaida,LOW);
  //abriuSaidapronto = false;
}

void ligarGiroflex(){
  digitalWrite(releGiroflex,LOW);
}
void desligarGiroflex(){
  digitalWrite(releGiroflex,HIGH);
}

void ligarLuzCela(){
  digitalWrite(releLuzCela,HIGH);
}
void desligarLuzCela(){
  digitalWrite(releLuzCela,LOW);
}

void  ligarLed(int led){
  analogWrite(led,180);
}

void  desligarLed(int led){
  analogWrite(led,0);
}

void alterarLuzCela(){
  if(luzCela){
    luzCela = false;
    digitalWrite(releLuzCela,HIGH);
  }else{
    luzCela = true;
    digitalWrite(releLuzCela,LOW);
  }
}


void imprimir(){

  
  
  Serial.print(analogRead(sensorAlvo));
  Serial.print("\t");
  Serial.print(digitalRead(sensorAlvo));
  Serial.print("\t");
  Serial.print(digitalRead(sensorQuadro));
  Serial.print("\t");
  Serial.println(analogRead(sensorQuadro));
  
}





void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  
  
  if(payload[0] =='0'){
    Serial.println("Start");
    start = true;
    
  }else{
  piscarLed(ledOn,1);
  if(payload[0] =='1'){
    Serial.println("ChegouPassagem");
    
    if(payload[1] == '1'){
      Serial.println("ABRIU");
      abrirPassagem();
    }
    else fecharPassagem();
    
  }else{
    if(payload[0] =='2'){
    Serial.println("ChegouSaida");
     if(payload[1] == '1'){
      Serial.println("ABRIU");
      abrirSaida();
    }
    else fecharSaida();
  } 
  else{
    if(payload[0] =='3'){
    Serial.println("ChegouGiroflex");
     if(payload[1] == '1'){
      Serial.println("ABRIU");
      ligarGiroflex();
    }
    else desligarGiroflex();
    
  } else {
    if(payload[0] =='4'){
    Serial.println("ChegouLuzCela");
     if(payload[1] == '1'){
      Serial.println("ABRIU");
      ligarLuzCela();
    }
    else desligarLuzCela();
    
  }
  }}}}

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
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      desligarLed(ledConfig);
      ligarLed(ledOn);
      client.publish("topicoArduinoPronto","1");
      client.subscribe("topicoPrincipal");
    } else {
      Serial.print("failed, rc=");
      piscarLed(ledConfig,2);
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
      // Wait 5 seconds before retrying
      delay(3000);
    }
  }
}







