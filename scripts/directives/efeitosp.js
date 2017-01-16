angular.module('app')
.directive('efeitosp',function(){
  return{
   templateUrl: 'templates/efeitosSonoros_p.html',
   controller: 'piratasController',
   replace: true
  }
})