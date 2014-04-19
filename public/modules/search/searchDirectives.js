navbar.directive('search', function(Tags) {
  return {
    restrict: 'AE',
    template: '<input id="ia-search" class="header-search" ui-select2="navsearch" type="hidden" ng-model="selectedQuery">',
    replace: true,
    controller: ['$rootScope', '$scope','TableList', 'ArticlesList','ReportsList', 'Tags', 'SourceList', 'vTopics',
      function($rootScope, $scope, TableList, ArticlesList,ReportsList, Tags, SourceList, vTopics) {

        $scope.getArticles = function(tag) {
          //Function Init 
          ArticlesList.all = []; // Flush previous articles              
          ArticlesList.page = 1;
          ArticlesList.fetch(Tags.all, ArticlesList.page)
            .then(function(articles) {
              ArticlesList.all = articles;
              ArticlesList.page++;
              if (articles.length >= 10) ArticlesList.isMore = 1;
            });
        };

        $scope.getSources = function(tag) {
          SourceList.selected = []; // Flush previous Sources
          SourceList.all = [];

          SourceList.fetch(Tags.all)
            .then(function(data) {
              data.forEach(function(el, index) {
                el.selected = true;
                SourceList.selected.push(el.id);
                SourceList.all.push(el);
              });
            });
        };

        $scope.getReports = function(tag) {
          //Function Init 
          ReportsList.all = []; // Flush previous Reports              
          ReportsList.page = 1;
          ReportsList.fetch(Tags.all, ReportsList.page)
            .then(function(reports) {
              ReportsList.all = reports;
              ReportsList.page++;
              if (reports.length >= 10) ReportsList.isMore = 1;
            });
        };

        $scope.getTables = function(tag) {
          //Function Init 
          TableList.all = []; // Flush previous Table              
          TableList.page = 1;
          TableList.fetch(Tags.all, TableList.page)
            .then(function(tables) {
              TableList.all = tables;
              TableList.page++;
              if (tables.length >= 10) TableList.isMore = 1;
            });
        };

        $scope.getTopics = function(tag) {
          //Function Init 
          vTopics.all = []; // Flush previous articles              
          $scope.$parent.$parent.$broadcast('fetchtopic', Tags.all);
        };

      }
    ],
    link: function(scope, el, attrs) {
      el.on('change', function(e) {

        if (e.added) {
          Tags.primary.coll = e.added.cat;
          Tags.primary.id = e.added._id;
          Tags.primary.text = e.added.text;
          Tags.all = []; // Clear Tag Array
          Tags.all.push(Tags.primary);
          scope.activeQuery = e.added.text;
          scope.selectedQuery = [];
          scope.$apply();
          // scope.$parent.$parent.$broadcast('clearmulti', e.added);
          scope.getArticles();
          scope.getSources();
          scope.getTopics();
          scope.getReports();
          scope.getTables();
        }
      });
    }
  };
});
