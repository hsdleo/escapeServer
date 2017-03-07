angular.module('app')
.directive('efeitospi',function(){
  return{
   templateUrl: 'templates/efeitosSonoros_pi.html',
   controller: 'piratasController',
   replace: true
  }
})