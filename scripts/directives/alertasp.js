angular.module('app')
.directive('alertasp',function(){
  return{
   templateUrl: 'templates/alertas_p.html',
   controller: 'piratasController',
   replace: true
  }
})