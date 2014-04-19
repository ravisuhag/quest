exports.render = function(req, res) {
  data = [{
    text: "Laptop"
    }, {
    text: "Mobile"
    }, {
    text: "Tablet"
  }];

  res.send(data);
};
