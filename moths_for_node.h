#ifndef __moths_for_node__
#define __moths_for_node__

#include "font_manager.h"
#include "mapping.h"
#include <node.h>

using namespace map;

class MappingWrapper;
class FontManagerWrapper: public node::ObjectWrap {
  friend class MappingWrapper;

 private:
  FontManager* font_manager_;

  explicit FontManagerWrapper();
  ~FontManagerWrapper();

  static v8::Persistent<v8::Function> constructor;

  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  static v8::Handle<v8::Value> loadFonts(const v8::Arguments& args);

 public:
  static void Init(v8::Handle<v8::Object> exports);
};

class MappingWrapper: public node::ObjectWrap {
 private:
  Mapping* mapping_;

  explicit MappingWrapper(std::string map_directory, std::string cache_directory);
  ~MappingWrapper();

  static v8::Persistent<v8::Function> constructor;

  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  // export functions
  // lod -- 3
  static v8::Handle<v8::Value> loadLOD(const v8::Arguments& args);
  static v8::Handle<v8::Value> loadLODFromFile(const v8::Arguments& args);
  static v8::Handle<v8::Value> loadLODFromString(const v8::Arguments& args);
  // style -- 6
  static v8::Handle<v8::Value> loadStyle(const v8::Arguments& args);
  static v8::Handle<v8::Value> loadStyleFromFile(const v8::Arguments& args);
  static v8::Handle<v8::Value> loadStyleFromString(const v8::Arguments& args);

  // data -- 7
  static v8::Handle<v8::Value> setupDataConnection(const v8::Arguments& args);

  // control function -- 10
  static v8::Handle<v8::Value> renderLabel(const v8::Arguments& args);
  static v8::Handle<v8::Value> setTile(const v8::Arguments& args);
  static v8::Handle<v8::Value> expand(const v8::Arguments& args);

  // cache function -- 13
  static v8::Handle<v8::Value> cacheTileFile(const v8::Arguments& args);
  static v8::Handle<v8::Value> cacheTileStream(const v8::Arguments& args);
  static v8::Handle<v8::Value> cacheVectorTile(const v8::Arguments& args);

  // access function  -- 22
  static v8::Handle<v8::Value> getTileFileName(const v8::Arguments& args);
  static v8::Handle<v8::Value> getVectorTileFileName(const v8::Arguments& args);
  static v8::Handle<v8::Value> getResolution(const v8::Arguments& args);
  static v8::Handle<v8::Value> getMapDirectory(const v8::Arguments& args);   
  static v8::Handle<v8::Value> getOutputDirectory(const v8::Arguments& args);

  static v8::Handle<v8::Value> setMapDirectory(const v8::Arguments& args);
  static v8::Handle<v8::Value> setBoundary(const v8::Arguments& args);
  static v8::Handle<v8::Value> setOutputDirectory(const v8::Arguments& args);
  static v8::Handle<v8::Value> setFontManager(const v8::Arguments& args);

 public:
  static void Init(v8::Handle<v8::Object> exports);
}; 

#endif
