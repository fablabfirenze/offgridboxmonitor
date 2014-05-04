var monitorApp = angular.module('monitorApp', ['ngRoute']);


monitorApp.config(['$httpProvider',function($httpProvider) {
    $httpProvider.defaults.transformRequest = function(data) {
        if (data === undefined) {
            return data;
        }
        return $.param(data);
    };
    $httpProvider.defaults.headers.common['Content-Type'] = 'application/x-www-form-urlencoded; charset=UTF-8';
    $httpProvider.defaults.headers.common['X-ApiKey'] = 'WlFZxKfaCNL1hiG3XF7lFsJ6GeUWVIdRFGcwK1LmGW0WZnNw';
    
}]);

monitorApp.config(['$routeProvider',
    function($routeProvider) {
        $routeProvider
                .when('/homepage', {
                    //templateUrl: '/js/angular/app/partials/test.html',
                    templateUrl: 'scripts/angular/app/views/homePage.html',
                    controller: 'homePageCtrl'
                })
                .when('/about', {
                    templateUrl: 'scripts/angular/app/views/about.html',
                    controller: 'aboutCtrl'
                })
                .otherwise({
                    redirectTo: '/homepage'
                            //templateUrl: 'partials/test.html',
                            //controller: 'TestCtrl'
                });
    }]);

monitorApp.controller('navigationCtrl',['$scope','$location','$route',
    function($scope,$location,$route){
        $scope.isMenuItemActive = function(path){
            var split_path = $location.path().split("/");
            // console.log(split_path);
             // console.log(split_path.indexOf(path));
             // console.log(path);
            return split_path.indexOf(path) > -1;
            //return path === $location.path();
        };
}]);

monitorApp.controller('homePageCtrl', ['$scope','$http', function($scope,$http) {
        $http.get('https://api.xively.com/v2/feeds/419601260').success(function(data) {
            $scope.datastreams_one = data.datastreams;
        }).error(function(e){
            console.log('err');
        });
        
    }]);

monitorApp.controller('aboutCtrl', ['$scope','$http', function($scope,$http) {
    }]);



