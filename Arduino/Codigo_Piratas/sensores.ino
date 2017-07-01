void checkGaveta(){
  
    if(!abriuGaveta){
      abriuGaveta = true;
      for(int i = 0;i<2;i++){
        if(analogRead(sensorGaveta) > 600){
            abriuGaveta = false;
        }
      }
      if(abriuGaveta) {
        
        //abrirGaveta();
        //delay(1000);
        client.publish("topicoArduinoProntoP","3");
        delay(500);
        abrirGaveta();
        //Serial.println("abriugaveta");
  
        
        startSensorGaveta = false;
        startSensorBarcos = true; 
        //abriuSaida = false;
      }
   }
}

void checkBarcos(){
    
      for(int i = 0;i<3;i++){
        if(digitalRead(sensorBarco1) == 0 && digitalRead(sensorBarco2) == 0 && digitalRead(sensorBarco3) == 0){
          if(!acaoPassagem){
            acaoPassagem = true;
        client.publish("topicoArduinoProntoP","4"); 
        delay(500); 
        abrirPassagem();
        //Serial.println("abriubarcos");
        ligarLuzCapitao();
        ligarLuzConves();
        startSensorBarcos = false;
        startSensorBau = true;
        atualizaEEPROM();
        }
        }
      }
}

void prepararBau(){
  //Serial.println(analogRead(sensorBau));
  if(analogRead(sensorBau) < 600){   
    preparar = false;
    client.publish("topicoArduinoProntoP","2");
 
  }
  delay(200);
}
void checkBau(){
  
    if(!abriuBau){
      abriuBau = true;
      for(int i = 0;i<3;i++){
        if(analogRead(sensorBau) < 600){
          
            abriuBau = false;
        }
      }
      //if(abriuSaida) abrirSaida();
      if(abriuBau){
        
       // Serial.println("checkTimaoS");
       client.publish("topicoArduinoProntoP","5");
       startSensorBau = false;
        /*
        desligarLuzConves();
        desligarLuzCapitao();
        ligarLuzBau();
        delay(4000);
        desligarLuzBau();
        ligarLuzConves();
        startSensorTimao = true;
        startSensorBau = false;
        //abriuPassagem = false;*/
      }
       
   }
}

void checkTimao(){

/*
  static int pos = 0;
  encoder.tick();

  int newPos = encoder.getPosition();
  if (pos != newPos) {
    Serial.print(newPos);
    Serial.println();
    pos = newPos;
  } // if*/
  

    encoder.tick();
    int newPos = encoder.getPosition();
//Serial.println(newPos);
   if(newPos > posicaoTimao){
      if(etapa1Timao  && ( girouWest > (2*UMA_VOLTA - 4) ) && (girouWest < (2*UMA_VOLTA + 4) ) ){
        etapa2Timao = true;
        
        //Serial.println("etapa 2");
      }
      if(etapa1Timao && !etapa2Timao){
      if((girouWest > (2*UMA_VOLTA + 4) )|| (girouWest < (2*UMA_VOLTA-4))){
        etapa1Timao = false;
        etapa2Timao = false;
        //Serial.println("ZEROU");
      }
      }
      girouWest = 0;
      girouEast++;
      contador++;
      if(etapa2Timao && (girouEast >= ((int) ((3.8)*UMA_VOLTA)) ) ){
        //ligarLuzCapitao();
        //abrirSaida();
        if(!acaoTimao){
        desligarLuzConves();  
        client.publish("topicoArduinoProntoP","6");
        
        
        
        //abrirSaida();     
        //delay(3000);
        //ligarLuzConves();  
        acaoTimao = true;
        }
        //Serial.println("ABRIU PORRA");
      }

    }else if(newPos < posicaoTimao){
      if(etapa2Timao && girouEast < (4*UMA_VOLTA - 4)){
        etapa1Timao = false;
        etapa2Timao = false;
        //Serial.println("ZEROU");
      }
      if(girouEast >= (3*UMA_VOLTA)){
        etapa1Timao = true;
        //Serial.println("etapa 1");
      }
      
      
      girouEast = 0;
      girouWest++;
      contador++;

    }
    posicaoTimao = newPos;

}

