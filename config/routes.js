module.exports = function (app) {

    // Home routes
    var index = require('../app/controllers/index');
    app.get('/', index.render);

    var tag = require('../app/controllers/tagsController');
    app.get('/tags', tag.render);

};
