#define UMA_VOLTA 12
#define POSICAO_SERVO_ABERTO 150
#define POSICAO_SERVO_FECHADO 30
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress ip(192, 168, 1, 102);
//IPAddress server(192,168,1,3);
IPAddress server(192,168,0,100);
EthernetClient ethClient;
PubSubClient client(ethClient);



//OUTPUTS
const int releLuzCapitao = 2;
const int releLuzConves =    3;
const int releGaveta = 4;
const int releSaida  = 5;
const int relePassagem = 6;
const int releBau = 9;
const int ledConfig = 8;
const int ledOn = 7;
//INPUTS
const int sensorGaveta =  A0;
const int sensorBarco1 = A1;
const int sensorBarco2 = A4;
const int sensorBarco3 = A5;
const int sensorBau = A6;




//DECLARAÇÃO DAS VARIÁVEIS

boolean start = false;
boolean acaoBau = false;
boolean acaoTimao = false;
boolean acaoPassagem = false;
boolean preparar = false;
boolean startSensorGaveta = false;
boolean startSensorBarcos = false;
boolean startSensorBau = false;
boolean startSensorTimao = false;
boolean abriuGaveta = false;
boolean abriuPassagem = false;
boolean abriuSaida = false;
boolean abriuBau = false;

boolean luzCapitao = true;
boolean luzConves = false;
boolean modoManual = false;
boolean etapa1Timao = false;
boolean etapa2Timao = false;

int contador = 0;
int posicaoTimao = 0;
int girouWest = 0;
int girouEast = 0;
