angular.module('app')
.directive('aciop',function(){
  return{
   templateUrl: 'templates/acionamentos_p.html',
   controller: 'piratasController',
   replace: true
  }
})