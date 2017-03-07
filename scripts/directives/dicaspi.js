angular.module('app')
.directive('dicaspi',function(){
  return{
   templateUrl: 'templates/dicas_pi.html',
   controller: 'piratasController',
   replace: true
  }
})