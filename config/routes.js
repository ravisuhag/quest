module.exports = function (app) {

    // Home routes
    var index = require('../app/controllers/index');
    app.get('/', index.render);
};
