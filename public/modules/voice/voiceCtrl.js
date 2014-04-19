var voice = angular.module('Voice', ['ui.select2']);

voice.controller('voiceCtrl', ['$scope','Tags',
  function($scope, Tags) {

  	$scope.micvalue="";
  	$scope.matchedtags="";

  	$scope.$watch('micvalue', function(newValue, oldValue) {
       Tags.fetch(newValue).then(function(tags) {
         $scope.matchedtags= tags;
        });
   });

  }
]);
