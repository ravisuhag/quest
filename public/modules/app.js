var gsfhacks = angular.module('Gsfhacks',
	['ngRoute','Home','Voice','Nlp', 'Search']
);


gsfhacks.config(['$routeProvider','$locationProvider',
  function($routeProvider, $locationProvider) {
    $locationProvider.html5Mode(false);

    $routeProvider.
      when('/', {
        templateUrl: '/modules/home/home.html',
        controller: 'homeCtrl'
      }).
      when('/voice', {
        templateUrl: '/modules/voice/voice.html',
        controller: 'voiceCtrl'
      }).
      when('/nlp', {
        templateUrl: '/modules/nlp/nlp.html',
        controller: 'nlpCtrl'
      }).
      otherwise({
        redirectTo: '/'
      });
  }]);
