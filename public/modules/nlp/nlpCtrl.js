var nlp = angular.module('Nlp', ['ui.select2']);

nlp.controller('nlpCtrl', ['$scope', 'Nlpres', '$rootScope', 'Tags',
  function($scope, Nlpres, $rootScope, Tags) {
    $rootScope.menucr = "";
    $rootScope.menuvoice = "";
    $rootScope.menunlp = "active";

    // Search Box
    $scope.nlpsearch = {
      minimumInputLength: 3,
      placeholder: 'Search',
      maximumSelectionSize: 1,
      'multiple': true,
      query: function(query) {

        Nlpres.fetch(query.term).then(function(response) {

          $scope.nouns = [];
          $scope.verbs = [];
          $scope.adjs = [];
          var goodString = "";
          var ar = response.data.keyword_extractor.keywords;
          for (var i = 0; i < ar.length; i++) {
            if (ar[i].tags === "A") $scope.adjs.push(ar[i].term), goodString += ar[i].term + " ";
            else if (ar[i].tags === "N") $scope.nouns.push(ar[i].term), goodString += ar[i].term + " ";
            else if (ar[i].tags === "V") $scope.verbs.push(ar[i].term);
          }

          console.log('$scope.verbs:' + $scope.verbs);
          console.log('$scope.adjs:' + $scope.adjs);

          Tags.fetch(goodString).then(function(tags) {
            query.callback(tags);
          });

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
