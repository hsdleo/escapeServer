angular.module('app')
.directive('dicasa',function(){
  return{
   templateUrl: 'templates/dicas_a.html',
   controller: 'alcatrazController',
   replace: true
  }
})