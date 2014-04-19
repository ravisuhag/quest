var voice = angular.module('Voice', ['ui.select2']);

voice.controller('voiceCtrl', ['$scope','$rootScope','Tags',
  function($scope,$rootScope, Tags) {

  	$rootScope.menuvoice="active";
    $rootScope.menucr="";
    $rootScope.menunlp="";


  	$scope.micvalue="";
  	$scope.matchedtags="";

  	$scope.$watch('micvalue', function(newValue, oldValue) {
       Tags.fetch(newValue).then(function(tags) {
         $scope.matchedtags= tags;
        });
   });

  }
]);
