voice.factory('Tags', ['$http',
  function($http) {
    var Tags = function(data) {
      angular.extend(this, data);
    };

    Tags.fetch = function(query) {
      return $http.get('/tags?q=' + query)
        .then(function(response) {
          rawtags = response.data;
          var tags = {results: []};

          rawtags.forEach(function(element, index) {
            tags.results.push({
              id: index,
              text: element,
            });
          });

          return tags;
        });
    };

    return Tags;
  }
]);
