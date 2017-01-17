    (function(){
      var client;
      var messageTemp = "0";

      angular.module('app')
      .controller('piratasController', piratasController);

      piratasController.$inject = ['$scope','$interval'];

      function piratasController($scope,$interval) {

       $scope.format = 'mm:ss';
       $scope.nomeJogo = 'Piratas';
       var timer1 = 3600;
       console.log("teste de Log");
       function formatNumber(n) {return (n<10? '0' : '') + n;}
       client = mows.createClient('ws://192.168.0.100:9001/mqtt');
       client && client.subscribe('topicoArduinoProntoP');

       client.on('message', function (topic, message) {
         if(messageTemp != message){
           console.log(message);
           messageTemp = message;

           if(message=="1"){
            $scope.aguardando = false;
            $scope.aguardandoBau = true;
            $scope.preparar = false;
            $scope.tocarNada();
          }else{
            if(message=="2"){
              $scope.aguardando = false;
              $scope.preparar = true;
              $scope.aguardandoBau = false;
              $scope.tocarNada();
            }else{
              if(message=="3"){
                $scope.audioTrovao.setVolume(0.9);
                $scope.audioTrovao.play();
                $scope.efeitoTrovao();
                $scope.tocarMedo();
              }
              else{
                if(message=="4"){
                  $scope.somMedo.stop();
                  $scope.tocarPassagem();
                }
                else{
                  if(message=="5"){
                    $scope.audioTrovao.setVolume(0.8);
                    $scope.audioTrovao.play();
                    $scope.acaoBau();
                  }
                  else{
                    if(message=="6"){
                      $scope.tocarTimao();
                    }

                  }}}}}


                }
              });

       $scope.tocarNada = function(){
        $scope.audioNada.setVolume(0.1);
        $scope.audioNada.stop();
      };
      $scope.tocarAmbiente = function () {
        $scope.audioAmbiente.setVolume(0.5);
        $scope.audioAmbiente.playPause();
      };

      $scope.tocarMedo = function () {
        $scope.somMedo.setVolume(0.7);
        $scope.somMedo.playPause();
      };
      $scope.tocarPassagem= function () {
        $scope.aberturaPassagem.setVolume(0.4);
        $scope.aberturaPassagem.playPause();
      };
      $scope.tocarDerrota = function () {
        $scope.audioDerrotaPiratas.setVolume(0.6);
        $scope.audioDerrotaPiratas.play();
      };

      $scope.tocarEnigma = function () {
        $scope.audioEnigma.setVolume(0.4);  
        $scope.audioEnigma.play();
      };
      $scope.tocarRepetirEnigma = function () {
        $scope.audioRepetirEnigma.setVolume(0.4);  
        $scope.audioRepetirEnigma.play();
      };


      $scope.tocarExplosao = function () {
        $scope.audioExplosao.setVolume(0.4);  
        $scope.audioExplosao.play();
      };

      $scope.dicaMacaco = function(){
        $scope.dicaMacaco.setVolume(0.8);
        $scope.dicaMacaco.play();
      }

      $scope.dicaMapa = function(){
        $scope.dicaMapa.setVolume(0.8);
        $scope.dicaMapa.play();
      }

      $scope.dicaXadrez = function(){
        $scope.dicaXadrez.setVolume(0.8);
        $scope.dicaXadrez.play();
      }

      $scope.dicaRemo = function(){
        $scope.dicaRemo.setVolume(0.8);
        $scope.dicaRemo.play();
      }

      $scope.dicaTimao = function(){
        $scope.dicaTimao.setVolume(0.8);
        $scope.dicaTimao.play();
      }

      $scope.dicaMacaco = function(){
        $scope.dicaMacaco.setVolume(0.8);
        $scope.dicaMacaco.play();
      }


      $scope.tocarTrovao1 = function () {
        $scope.audioTrovao.setVolume(0.8);
        $scope.audioTrovao.play();
        var msg = '70' ;
        client && client.publish('topicoPrincipalP', String(msg));
      };

      $scope.tocarTrovao2 = function () {
        $scope.audioTrovao.setVolume(0.8);
        $scope.audioTrovao.play();
        var msg = '90' ;
        client && client.publish('topicoPrincipalP', String(msg));
      };

      $scope.tocarMacaco = function () {
        $scope.audioMacaco.setVolume(0.4);
        $scope.audioMacaco.play();
      };

      $scope.tocarObjetos = function () {
        $scope.audioObjetos.setVolume(1);
        $scope.audioObjetos.play();
      };


      $scope.minuto = formatNumber(Math.floor(timer1 / 60));
      $scope.segundo = formatNumber(timer1%60);
      $scope.message = 'Piratas Controller';
      

      $scope.imprimir = function(arg){
      }
      var timerDelay;
      $scope.delay = function(arg){

        timerDelay = $interval(function(){
          console.log("tempo passou");
          $scope.pararDelay();
        } 
        ,arg,0);
      };
      $scope.pararDelay = function() {
        if (angular.isDefined(timerDelay)) {
          $interval.cancel(timerDelay);
          timerDelay = undefined;
        }
      };

      
      var stop;
      $scope.startTimer = function() {
              // Don't start a new fight if we are already fighting
              if ( angular.isDefined(stop) ) return;
              
              stop = $interval(function() {
                if (timer1 > 0 ) {
                  timer1 = timer1- 1;
                  if(timer1 == 60){$scope.tocarSino();}
                  $scope.minuto = formatNumber(Math.floor(timer1 / 60));
                  $scope.segundo = formatNumber(timer1%60);
                } else {
                  $scope.stopTimer();
                  $scope.tocarSirene();
                  $scope.tocarDerrota();
                }
              }, 1000,0);
            };

            $scope.stopTimer = function() {
              if (angular.isDefined(stop)) {
                $interval.cancel(stop);
                stop = undefined;
              }
            };

            $scope.resetTimer = function() {
              $scope.stopTimer();
              timer1 = 3600;

              $scope.minuto = formatNumber(Math.floor(timer1 / 60));
              $scope.segundo = formatNumber(timer1%60);
            };

            $scope.$on('$destroy', function() {
              // Make sure that the interval is destroyed too
              $scope.stopTimer();
            });

           //$scope.sound = ngAudio.load("sounds/sirene.mp3"); // returns NgAudioObject


           $scope.dicas = [{"id":"1","texto":"Macaco"},
           {"id":"2","texto":"Mapa"},
           {"id":"3","texto":"Xadrez"},
           {"id":"4","texto":"Remo"},
           {"id":"5","texto":"Timao"}];


           $scope.alertas = [{"id":"1","texto":"Não tire as GARRAFAS"},
           {"id":"2","texto":"Não FORÇE nenhum objeto"}];

           $scope.acionamentos = [{"id":"1","texto":"Abrir Passagem"},
           {"id":"2","texto":"Fechar Passagem"},
           {"id":"3","texto":"Desligar Luz Conves"},
           {"id":"4","texto":"Ligar Luz Conves"},
           {"id":"5","texto":"Desligar Luz Capitao"},
           {"id":"6","texto":"Ligar Luz Capitao"},
           {"id":"7","texto":"Abrir Saída"},
           {"id":"8","texto":"Fechar Saída"}];

           $scope.efeitos = [{"id":"1","texto":"Macaco"},
           {"id":"2","texto":"Trovao(final com luz)"},
           {"id":"3","texto":"Trovao(final sem luz)"},
           {"id":"4","texto":"Repetir Enigma"},
           {"id":"5","texto":"Explosao Saida"},
           {"id":"6","texto":"Derrota"}];


           $scope.prepararJogo = function() {
            client && client.publish('topicoPrincipalP', String('01'));
            $scope.comandoLuzCapitao(0);

          };
          $scope.startJogo = function() {
            $scope.startTimer();
            $scope.tocarAmbiente();
            $scope.comandoLuzCapitao(1);
            //client && client.publish('topicoPrincipal', String('01'));
          };


          $scope.resetarJogo = function() {
            //$scope.resetTimer();
            //$scope.comandoLuzCela(0);
            //$scope.audioAmbiente.stop();
            //client && client.publish('topicoPrincipal', String('00'));
          };

          $scope.comandoPassagem = function(cod) {
            var msg = '1' + cod; 
            client && client.publish('topicoPrincipalP', String(msg));
            $scope.message = cod;

          };

          $scope.comandoSaida = function(cod) {
            var msg = '2' + cod;
            client && client.publish('topicoPrincipalP', String(msg));
            $scope.message = cod;
          };
          $scope.comandoGaveta= function(cod) {
            var msg = '3' + cod;
            client && client.publish('topicoPrincipalP', String(msg));
            $scope.message = cod;
          };
          $scope.comandoLuzCapitao = function(cod) {
            var msg = '4' + cod;
            client && client.publish('topicoPrincipalP', String(msg));
            $scope.message = cod;
          };

          $scope.comandoLuzConves= function(cod) {
            var msg = '5' + cod;
            client && client.publish('topicoPrincipalP', String(msg));
            $scope.message = cod;
          };
          $scope.comandoBau= function(cod) {
            var msg = '6' + cod;
            client && client.publish('topicoPrincipalP', String(msg));
            $scope.message = cod;
          };
          $scope.efeitoTrovao= function() {
            var msg = '70' ;
            client && client.publish('topicoPrincipalP', String(msg));
          };
          $scope.acaoBau= function() {
            var msg = '80' ;
            client && client.publish('topicoPrincipalP', String(msg));
            $scope.tocarAmbiente();
          };



        }
      })();