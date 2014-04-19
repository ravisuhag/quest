var home = angular.module('Home', ['ui.select2']);

home.controller('homeCtrl', ['$scope','$rootScope',
  function($scope, $rootScope) {
  	$rootScope.menucr="active";
  	$rootScope.menuvoice="";

  }
]);
