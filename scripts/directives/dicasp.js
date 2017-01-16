angular.module('app')
.directive('dicasp',function(){
  return{
   templateUrl: 'templates/dicas_p.html',
   controller: 'piratasController',
   replace: true
  }
})