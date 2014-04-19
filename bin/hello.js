var addon = require('./build/Release/spellcheck');
addon.initdict();

console.log(addon.matched("lappy"));

