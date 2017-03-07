angular.module('app')
.directive('dicasai',function(){
  return{
   templateUrl: 'templates/dicas_ai.html',
   controller: 'alcatrazController',
   replace: true
  }
})