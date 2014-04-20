var gsfhacks = angular.module('Gsfhacks',
	['ngRoute','Home','Voice','Nlp','About', 'Search']
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
      when('/about', {
        templateUrl: '/modules/about/about.html',
        controller: 'aboutCtrl'
      }).
      otherwise({
        redirectTo: '/'
      });
  }]);
