// Location Service -- | Fetch Locs : Modify acc go select2 : return promise

navbar.factory('Locs', ['$http',
  function($http) {
    var Locs = function(data) {
      angular.extend(this, data);
    };

    Locs.fetch = function(name) {
      return $http.get('/locs?name=' + name)
        .then(function(response) {

          var locs = {
            results: []
          };
          rawlocs = response.data;
          rawlocs.forEach(function(element, index) {
            locs.results.push({
              id: index,
              _id: element.id,
              text: element.name
            });
          });
          return locs;
        });
    };

    return Locs;
  }
]);

