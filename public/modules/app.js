var gsfhacks = angular.module('Gsfhacks',
	['ngRoute','Home']
);


gsfhacks.config(['$routeProvider','$locationProvider',
  function($routeProvider, $locationProvider) {
    $locationProvider.html5Mode(false);

    $routeProvider.
      when('/', {
        templateUrl: '/modules/home/home.html',
        controller: 'homeCtrl'
      }).
      otherwise({
        redirectTo: '/'
      });
  }]);
