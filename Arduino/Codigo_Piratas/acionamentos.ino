
/*
void abrirPassagem(){
  digitalWrite(relePassagem,LOW);
  delay(300);
  digitalWrite(relePassagem,HIGH);
}
void fecharPassagem(){
  digitalWrite(relePassagem,LOW);
  delay(300);
  digitalWrite(relePassagem,HIGH);
}*/

void abrirPassagem(){
  digitalWrite(relePassagem,HIGH);
  delay(300);
  digitalWrite(relePassagem,LOW);
}
void fecharPassagem(){
  digitalWrite(relePassagem,HIGH);
  delay(300);
  digitalWrite(relePassagem,LOW);
}
void abrirGaveta(){
  digitalWrite(releGaveta,HIGH);
}
void fecharGaveta(){
  digitalWrite(releGaveta,LOW);
  //abriuGaveta = false;
}

void abrirSaida(){
  digitalWrite(releSaida,HIGH);
}
void fecharSaida(){
  digitalWrite(releSaida,LOW);
  //abriuSaidapronto = false;
}
void ligarLuzBau(){
  digitalWrite(releBau,LOW);
}
void desligarLuzBau(){
  digitalWrite(releBau,HIGH);
}

void efeitoTrovao1(){

  desligarLuzCapitao();
  desligarLuzConves();
  delay(100);
  ligarLuzCapitao();
  ligarLuzConves();
  delay(100);
  desligarLuzCapitao();
  desligarLuzConves();
  delay(100);
  ligarLuzCapitao();
  ligarLuzConves();
  delay(100);
  
}
void efeitoTrovao2(){

  desligarLuzCapitao();
  desligarLuzConves();
  delay(100);
  ligarLuzCapitao();
  ligarLuzConves();
  delay(100);
  desligarLuzCapitao();
  desligarLuzConves();
  delay(100);
  ligarLuzCapitao();
  ligarLuzConves();
  delay(100);
  desligarLuzCapitao();
  desligarLuzConves();
  
}

void ligarLuzCapitao(){
  digitalWrite(releLuzCapitao,HIGH);
}
void desligarLuzCapitao(){
  digitalWrite(releLuzCapitao,LOW);
}

void ligarLuzConves(){
  digitalWrite(releLuzConves,LOW);
}
void desligarLuzConves(){
  digitalWrite(releLuzConves,HIGH);
}

void  ligarLed(int led){
  analogWrite(led,180);
}

void  desligarLed(int led){
  analogWrite(led,0);
}


void funcaoAcaoBau(){
        //if(!acaoBau){
        desligarLuzConves();
        ligarLuzBau();
        efeitoTrovao2();
        delay(12000);
        desligarLuzBau();
        ligarLuzConves();
        startSensorTimao = true;
        startSensorBau = false;
        //}
       // acaoBau = true;
  
}

