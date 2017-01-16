// create the module and name it scotchApp
//var app = angular.module('app', ['mediaPlayer','ui.router']);
var app = angular.module('app', ['mediaPlayer','ui.router']);

//var app = angular.module('app', ['ui.router']);

app.config(function($stateProvider, $urlRouterProvider) {

 $urlRouterProvider.otherwise('/alcatraz');

 $stateProvider
     .state('alcatraz', {
         url: '/alcatraz',
         templateUrl: 'views/alcatraz.html',
         controller: 'alcatrazController'
     })
     .state('piratas', {
         url: '/piratas',
         templateUrl: 'views/piratas.html',
         controller: 'piratasController'
     })
     ;

});