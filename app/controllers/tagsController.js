var addon = require('./../../bin/build/Release/spellcheck');
addon.initdict();

exports.render = function(req, res) {
  fetchTags= addon.matched(req.query.q).split(";");
  res.send(fetchTags);
};
