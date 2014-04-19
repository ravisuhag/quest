/**
 * Module dependencies.
 */
var express = require('express'),
    flash = require('connect-flash'),
    helpers = require('view-helpers'),
    config = require('./config');
    
var bodyParser = require('body-parser');

module.exports = function(app) {
  app.set('showStackError', true);

  //Prettify HTML
  app.locals.pretty = true;

  //Should be placed before express.static
  app.use(express.compress({
    filter: function(req, res) {
      return (/json|text|javascript|css/).test(res.getHeader('Content-Type'));
    },
    level: 9
  }));

  //Setting the fav icon and static folder
  app.use(express.favicon());
  app.use(express.static(config.root + '/public'));

  //Don't use logger for test env
  if (process.env.NODE_ENV !== 'test') {
    app.use(express.logger('dev'));
  }

  //Set views path, template engine and default layout
  app.set('views', config.root + '/app/views');
  app.set('view engine', 'ejs');

  //Enable jsonp
  app.enable("jsonp callback");

  app.configure(function() {
    app.use(express.cookieParser());
    app.use(bodyParser());
    app.use(express.urlencoded());
    app.use(express.json());
    app.use(express.methodOverride());


    // Express Mongo Session Store
    app.use(express.session(
        {secret: 'GSF-Hacks'}
    ));

    //connect flash for flash messages
    app.use(flash());

    //dynamic helpers
    app.use(helpers(config.app.name));

    //routes should be at the last
    app.use(app.router);

    //Assume "not found" in the error msgs is a 404.
    app.use(function(err, req, res, next) {
      //Treat as 404
      if (~err.message.indexOf('not found')) return next();

      //Log it
      console.error(err.stack);

      //Error page
      res.status(500).render('500', {
        error: err.stack
      });
    });

    //Assume 404 since no middleware responded
    app.use(function(req, res, next) {
      res.status(404).render('404', {
        url: req.originalUrl,
        error: 'Not found'
      });
    });

  });
};
