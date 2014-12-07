var express = require('express');
var moths = require('../build/Release/moths');

var app = express();

// global variables
var map_dir = "/home/xuxiang/Documents/mapping";
var cache_dir = map_dir + "/cache";
var font_dir = map_dir + "/fonts";

var status = true;

console.log("Loading fonts...");
var fm = new moths.FontManager();
fm.loadFonts(font_dir);

app.get('/', function(req, res) {
	res.type('text/plain');
	res.end('Hello');
    });

app.get('/tile/:z/:x/:y', function(req, res) {
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

	var level = parseInt(req.params.z);
	var row = parseInt(req.params.x);
	var col = parseInt(req.params.y);
	
	//	console.log("level=" + level + ", row=" + row + ", col=" + col);

	mapping.setTile(level, row, col);

	mapping.setupDataConnection();

	// cache tile
	var image_content = mapping.cacheTileStream(false);

	var buf = new Buffer(image_content, 'base64');

	if (!status) {
	    console.log("Cache Tile fail!");
	} else {
	    res.type('image/png');
	    res.end(buf);
	}
    });

app.listen(3000);
