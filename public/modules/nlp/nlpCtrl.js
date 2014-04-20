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

          var nouns = new Array(),
            verbs = new Array(),
            adjs = new Array();
          var goodString = "";
          var ar = response.data.keyword_extractor.keywords;
          for (var i = 0; i < ar.length; i++){
            if (ar[i].tags === "A") adjs.push(ar[i].term), goodString += ar[i].term + " ";
            else if (ar[i].tags === "N") nouns.push(ar[i].term), goodString += ar[i].term + " ";
            else if (ar[i].tags === "V") verbs.push(ar[i].term);
          }

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
