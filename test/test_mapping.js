var moths = require('../build/Release/moths');

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

mapping.setTile(3, 4, 3);

mapping.setupDataConnection();

// cache tile
status = mapping.cacheTileFile(false);

if (!status) {
    console.log("Cache Tile fail!");
} else {
    console.log("Welcome!");
}

