//Module Dependencies  
var express = require('express'),
    fs = require('fs');

//Load configurations
var env = process.env.NODE_ENV = process.env.NODE_ENV || 'development',
    config = require('./config/config');

//App initialization
var app = express();

//For Parsing POST requests
app.use(express.bodyParser());

//Express app settings
require('./config/express')(app);

//Routes Intialization
require('./config/routes')(app);


// Start app by listening to port
var port = process.env.PORT || config.port;
app.listen(port);
console.log('Server Listening on port  ' + port);


//expose app
exports = module.exports = app;
