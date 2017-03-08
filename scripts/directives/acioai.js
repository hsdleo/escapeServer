angular.module('app')
.directive('acioai',function(){
  return{
   templateUrl: 'templates/acionamentos_ai.html',
   controller: 'alcatrazController',
   replace: true
  }
})