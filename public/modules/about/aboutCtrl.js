var about = angular.module('About', ['ui.select2']);

about.controller('aboutCtrl', ['$scope','$rootScope',
  function($scope, $rootScope) {
  	$rootScope.menucr="active";
  	$rootScope.menuvoice="";
  	$rootScope.menunlp="";

  }
]);
