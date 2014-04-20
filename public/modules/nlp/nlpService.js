nlp.factory('Nlpres', ['$http',
  function($http) {
    var Nlpres = function(data) {
      angular.extend(this, data);
    };

    Nlpres.fetch = function(query) {
      return $http.get('https://cilenisapi.p.mashape.com/keyword_extractor?lang_input=en&text=' + query, 
        {headers: {'X-Mashape-Authorization': 'EkXrj76TjG5Zp74kvw3UUHrpAQwMSpAW'}})
        .then(function(response) {
          nlpres= response;
          return nlpres;
        });
    };

    return Nlpres;
  }
]);


