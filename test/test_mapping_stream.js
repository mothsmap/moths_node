var moths = require('../build/Release/moths');
var fs = require('fs');

var map_dir = "/home/xuxiang/Documents/mapping";
var cache_dir = map_dir + "/cache";
var font_dir = map_dir + "/fonts";
var status = true;

console.log("Loading fonts...");
var fm = new moths.FontManager();
fm.loadFonts(font_dir);

console.log("create mapping task...");
var mapping = new moths.Mapping(map_dir, cache_dir);

mapping.renderLabel(true);

mapping.expand(32);

mapping.setFontManager(fm);

status = mapping.loadLOD();
if (!status) {
    console.log("Load LOD fail!");
}

status = mapping.loadStyle();
if (!status) {
    console.log("Load Style fail!");
}

mapping.setTile(0, 0, 0);

mapping.setupDataConnection();

// cache tile
var image_content = mapping.cacheTileStream(false);
//console.log(image_content);

var filename = mapping.getTileFileName();

//var buf = new Buffer(filename, 'base64');
//console.log(buf.length);
fs.writeFile(filename, image_content, 'base64', function (err) {
              if (err) throw err;
              console.log('file saved');
          });

if (!status) {
    console.log("Cache Tile fail!");
} else {
    //console.log("image content:\n" + image_content);
    console.log("Welcome!");
}

