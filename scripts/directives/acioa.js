angular.module('app')
.directive('acioa',function(){
  return{
   templateUrl: 'templates/acionamentos_a.html',
   controller: 'alcatrazController',
   replace: true
  }
})