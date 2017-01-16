angular.module('app')
.directive('efeitosa',function(){
  return{
   templateUrl: 'templates/efeitosSonoros_a.html',
   controller: 'alcatrazController',
   replace: true
  }
})