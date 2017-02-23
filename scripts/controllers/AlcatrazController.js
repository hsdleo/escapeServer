    (function(){

     var client;

     angular.module('app')
     .controller('alcatrazController', alcatrazController);

     alcatrazController.$inject = ['$scope','$interval'];

     function alcatrazController($scope,$interval) {
       $scope.format = 'mm:ss';
       var timer1 = 3600;

       function formatNumber(n) {return (n<10? '0' : '') + n;}
       client = mows.createClient('ws://192.168.0.100:9001/mqtt')
       client && client.subscribe('topicoArduinoProntoA');

       client.on('message', function (topic, message) {
         console.log(message);

         if(message=="1"){
          $scope.aguardando = false;
          $scope.preparar = true;
          $scope.tocarNada();
         }
        if(message=="2"){

        }

         $scope.message = message;
       });

       $scope.tocarNada = function(){
      $scope.audioNada.setVolume(0.1);
        $scope.audioNada.stop();
       };
      $scope.tocarAmbiente = function () {
        $scope.audioAmbiente.setVolume(0.2);
        $scope.audioAmbiente.play();
      };
      $scope.tocarDerrota = function () {
        $scope.audioDerrota.setVolume(0.6);
        $scope.audioDerrota.play();
      };
      $scope.tocarDicaCama = function () {
        $scope.audioDicaCama.setVolume(0.25);
        $scope.audioDicaCama.play();
      };
      $scope.tocarDicaBanho = function () {
        $scope.audioDicaBanho.setVolume(0.25);
        $scope.audioDicaBanho.play();
      };
      $scope.tocarDicaQuebra = function () {
        $scope.audioDicaQuebra.setVolume(0.25);
        $scope.audioDicaQuebra.play();
      };
      $scope.tocarDicaDirecoes = function () {
        $scope.audioDicaDirecoes.setVolume(0.25);
        $scope.audioDicaDirecoes.play();
      };
      $scope.tocarDicaFichas = function () {
        $scope.audioDicaFichas.setVolume(0.25);
        $scope.audioDicaFichas.play();
      };
      $scope.tocarDicaAlvo = function () {
        $scope.audioDicaAlvo.setVolume(0.25);
        $scope.audioDicaAlvo.play();
      };
      $scope.tocarDicaCobertor2 = function () {
        $scope.audioDicaCobertor2.setVolume(0.25);
        $scope.audioDicaCobertor2.play();
      };
      $scope.tocarTelefone = function () {
        $scope.audioTelefone.setVolume(0.25);
        $scope.audioTelefone.playPause();
      };
      $scope.tocarArma = function () {
        $scope.audioArma.setVolume(0.25);
        $scope.audioArma.playPause();
      };
      $scope.tocarUnlock = function () {
        $scope.audioUnlock.setVolume(0.25);
        $scope.audioUnlock.playPause();
      };


      $scope.tocarSirene = function () {
        $scope.audioSirene.setVolume(0.2);
        $scope.audioSirene.playPause();
      };
      $scope.tocarObjetos = function () {
        $scope.audioObjetos.setVolume(1);
        $scope.audioObjetos.play();
      };
      $scope.tocarGarrafas = function () {
        $scope.audioGarrafas.setVolume(0.6);
        $scope.audioGarrafas.play();
      };
      $scope.tocarDescarga = function () {
        $scope.audioDescarga.setVolume(0.2);
        $scope.audioDescarga.play();
      };
      $scope.tocarDisjuntor = function () {
        $scope.audioDisjuntor.setVolume(0.2);
        $scope.audioDisjuntor.play();
        
      };


      $scope.minuto = formatNumber(Math.floor(timer1 / 60));
      $scope.segundo = formatNumber(timer1%60);
      $scope.message = 'Alcatraz Controller';
      $scope.imprimir = function(arg){
      }
  
      var stop;
      $scope.startTimer = function() {
              // Don't start a new fight if we are already fighting
              if ( angular.isDefined(stop) ) return;
              
              stop = $interval(function() {
                if (timer1 > 0 ) {
                  timer1 = timer1- 1;
                  if(timer1 == 60){$scope.tocarSirene();}
                  $scope.minuto = formatNumber(Math.floor(timer1 / 60));
                  $scope.segundo = formatNumber(timer1%60);
                } else {
                  $scope.stopTimer();
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


           $scope.dicas = [{"id":"1","texto":"Cama (1)"},
           {"id":"2","texto":"Cama (2)"},
           {"id":"3","texto":"Ficha (1)"},
           {"id":"4","texto":"Ficha (2)"},
           {"id":"5","texto":"Alvo"},
           {"id":"6","texto":"Banho"},
           {"id":"7","texto":"(TEL)Cobertor"},
           {"id":"8","texto":"(TEL)Quebra Cabeça"},
           {"id":"9","texto":"Tangram"}];


           $scope.alertas = [{"id":"1","texto":"Não tire as GARRAFAS"},
           {"id":"2","texto":"Não FORÇE nenhum objeto"}];

           $scope.acionamentos = [{"id":"1","texto":"Abrir Passagem"},
           {"id":"2","texto":"Fechar Passagem"},
           {"id":"3","texto":"Desligar GiroFlex"},
           {"id":"4","texto":"Ligar GiroFlex"},
           {"id":"5","texto":"Desligar Luz"},
           {"id":"6","texto":"Ligar Luz"},
           {"id":"7","texto":"Abrir Saída"},
           {"id":"8","texto":"Fechar Saída"},
           {"id":"9","texto":"Som Derrota"}];

           $scope.efeitos = [{"id":"1","texto":"Descarga"},
           {"id":"2","texto":"Disjuntor"},
           {"id":"3","texto":"Sirene"},
           {"id": "4","texto":"Telefone"}];

    
           $scope.prepararJogo = function() {
            client && client.publish('topicoPrincipalA', String('01'));
            $scope.comandoLuzCela(1);

          };
          $scope.startJogo = function() {
            $scope.startTimer();
            $scope.tocarAmbiente();
            $scope.comandoLuzCela(0);

            client && client.publish('topicoPrincipalA', String('01'));
          };


          $scope.resetarJogo = function() {
            $scope.resetTimer();
            $scope.comandoLuzCela(0);
            $scope.audioAmbiente.stop();
            client && client.publish('topicoPrincipalA', String('00'));
          };

          $scope.comandoPassagem = function(cod) {
            var msg = '1' + cod; 
            client && client.publish('topicoPrincipalA', String(msg));
            $scope.message = cod;

          };

          $scope.comandoSaida = function(cod) {
            var msg = '2' + cod;
            client && client.publish('topicoPrincipalA', String(msg));
            $scope.message = cod;
          };

          $scope.comandoGiroflex= function(cod) {
            var msg = '4' + cod;
            client && client.publish('topicoPrincipalA', String(msg));
            $scope.message = cod;
          };

          $scope.comandoLuzCela = function(cod) {
            var msg = '3' + cod;
            client && client.publish('topicoPrincipalA', String(msg));
            $scope.message = cod;
          };

        }
      })();