search.directive('search', function(Tags) {
  return {
    restrict: 'AE',
    template: '<input id="ia-search" class="header-search" ui-select2="navsearch" type="text" ng-model="selectedQuery">',
    replace: true,
    controller: ['$scope',
      function($scope) {

        // Controller code here

      }
    ],
    link: function(scope, el, attrs) {
      el.on('change', function(e) {

        if (e.added) {
          console.log(e.added);
          scope.selectedQuery =[];
          scope.$apply();
          angular.element('#s2id_autogen1').val(e.added.text);
        }
      });
    }
  };
});
