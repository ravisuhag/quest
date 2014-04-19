var search = angular.module('Search', ['ui.select2']);

search.controller('SearchCtrl', ['$scope','Tags','$location',
  function($scope,Tags,$location) {
    
    // Search Box
    $scope.navsearch = {
      minimumInputLength: 3,
      placeholder: 'Search',
      maximumSelectionSize: 1,
      'multiple': true,
      query: function(query) {
        Tags.fetch(query.term).then(function(tags) {
          query.callback(tags);
        });
      },
      formatResult: function(item) {
        return '<div>' +
          '<span class="search-results-name">' + item.text + '</span >' +
          '</div>';
      }
    };

  }
]);
