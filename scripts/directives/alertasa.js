angular.module('app')
.directive('alertasa',function(){
  return{
   templateUrl: 'templates/alertas_a.html',
   controller: 'alcatrazController',
   replace: true
  }
})