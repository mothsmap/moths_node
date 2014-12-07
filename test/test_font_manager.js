var moths = require('../build/Release/moths');

console.log("Loading fonts...");

var fm = new moths.FontManager();

fm.loadFonts("fonts/");

console.log("Welcome!");