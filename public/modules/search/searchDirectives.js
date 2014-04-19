navbar.directive('search', function(Tags) {
  return {
    restrict: 'AE',
    template: '<input id="ia-search" class="header-search" ui-select2="navsearch" type="hidden" ng-model="selectedQuery">',
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
        }
      });
    }
  };
});
