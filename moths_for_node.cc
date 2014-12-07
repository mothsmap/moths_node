#include "moths_for_node.h"

v8::Persistent<v8::Function> FontManagerWrapper::constructor;
v8::Persistent<v8::Function> MappingWrapper::constructor;

FontManagerWrapper::FontManagerWrapper() {
  font_manager_ = new FontManager;
}

FontManagerWrapper::~FontManagerWrapper() {
  delete font_manager_;
}

void FontManagerWrapper::Init(v8::Handle<v8::Object> exports) {
  // function template
  v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
  tpl->SetClassName(v8::String::NewSymbol("FontManager"));

  // prototype template
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("loadFonts"), v8::FunctionTemplate::New(loadFonts)->GetFunction());

  constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
  
  // export class
  exports->Set(v8::String::NewSymbol("FontManager"), constructor);
}

v8::Handle<v8::Value> FontManagerWrapper::New(const v8::Arguments& args) {
  v8::HandleScope scope;
  if (args.IsConstructCall()) {
    FontManagerWrapper* obj = new FontManagerWrapper();
    obj->Wrap(args.This());

    return args.This();
  } else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { args[0] };
    return scope.Close(constructor->NewInstance(argc, argv));
  }
}

v8::Handle<v8::Value> FontManagerWrapper::loadFonts(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsString()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  v8::String::Utf8Value str(args[0]->ToString());
  std::string s(*str);

  FontManagerWrapper* obj = ObjectWrap::Unwrap<FontManagerWrapper>(args.This());
  obj->font_manager_->LoadFonts(s);

  return scope.Close(v8::Undefined());
}


//***********************************************************************//
MappingWrapper::MappingWrapper(std::string map_directory, std::string cache_directory) {
  mapping_ = new Mapping(map_directory, cache_directory);
}

MappingWrapper::~MappingWrapper() {
  delete mapping_;
}

void MappingWrapper::Init(v8::Handle<v8::Object> exports) {
  // function template
  v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
  tpl->SetClassName(v8::String::NewSymbol("Mapping"));
  tpl->InstanceTemplate()->SetInternalFieldCount(22);

  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("loadLOD"), v8::FunctionTemplate::New(loadLOD)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("loadLODFromFile"), v8::FunctionTemplate::New(loadLODFromFile)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("loadLODFromString"), v8::FunctionTemplate::New(loadLODFromString)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("loadStyle"), v8::FunctionTemplate::New(loadStyle)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("loadStyleFromFile"), v8::FunctionTemplate::New(loadStyleFromFile)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("loadStyleFromString"), v8::FunctionTemplate::New(loadStyleFromString)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("setupDataConnection"), v8::FunctionTemplate::New(setupDataConnection)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("renderLabel"), v8::FunctionTemplate::New(renderLabel)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("setTile"), v8::FunctionTemplate::New(setTile)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("expand"), v8::FunctionTemplate::New(expand)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("cacheTileFile"), v8::FunctionTemplate::New(cacheTileFile)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("cacheTileStream"), v8::FunctionTemplate::New(cacheTileStream)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("cacheVectorTile"), v8::FunctionTemplate::New(cacheVectorTile)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("getTileFileName"), v8::FunctionTemplate::New(getTileFileName)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("getVectorTileFileName"), v8::FunctionTemplate::New(getVectorTileFileName)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("getResolution"), v8::FunctionTemplate::New(getResolution)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("getMapDirectory"), v8::FunctionTemplate::New(getMapDirectory)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("getOutputDirectory"), v8::FunctionTemplate::New(getOutputDirectory)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("setMapDirectory"), v8::FunctionTemplate::New(setMapDirectory)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("setBoundary"), v8::FunctionTemplate::New(setBoundary)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("setOutputDirectory"), v8::FunctionTemplate::New(setOutputDirectory)->GetFunction());
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("setFontManager"), v8::FunctionTemplate::New(setFontManager)->GetFunction());

  constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
  
  // export
  exports->Set(v8::String::NewSymbol("Mapping"), constructor);
}

v8::Handle<v8::Value> MappingWrapper::New(const v8::Arguments& args) {
  v8::HandleScope scope;
  // At least two string parameters
  if (args.IsConstructCall()) {
    if (args.Length() < 2) {
      v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
      return scope.Close(v8::Undefined());
    }

    if (!args[0]->IsString() || !args[1]->IsString()) {
      v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
      return scope.Close(v8::Undefined());
    }
    
    // fetch 
    v8::String::Utf8Value str1(args[0]->ToString());
    std::string map_directory(*str1);
    v8::String::Utf8Value str2(args[1]->ToString());
    std::string cache_directory(*str2);

    // create target class
    MappingWrapper* obj = new MappingWrapper(map_directory, cache_directory);
    obj->Wrap(args.This());

    return args.This();
  } else {
    const int argc = 2;
    v8::Local<v8::Value> argv[argc] = { args[0], args[1] };
    return scope.Close(constructor->NewInstance(argc, argv));
  }
}

v8::Handle<v8::Value> MappingWrapper::loadLOD(const v8::Arguments& args) {
  v8::HandleScope scope;

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());
  bool result = obj->mapping_->LoadLod();

  return scope.Close(v8::Boolean::New(result));
}

v8::Handle<v8::Value> MappingWrapper::loadLODFromFile(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsString()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  v8::String::Utf8Value str(args[0]->ToString());
  std::string filename(*str);
  bool result = obj->mapping_->LoadLodFromFile(filename);

  return scope.Close(v8::Boolean::New(result));
}

v8::Handle<v8::Value> MappingWrapper::loadLODFromString(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsString()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  v8::String::Utf8Value str(args[0]->ToString());
  std::string filename(*str);

  bool result = obj->mapping_->LoadLodFromString(filename.c_str());

  return scope.Close(v8::Boolean::New(result));
}

v8::Handle<v8::Value> MappingWrapper::loadStyle(const v8::Arguments& args) {
  v8::HandleScope scope;

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());
  bool result = obj->mapping_->LoadStyle();

  return scope.Close(v8::Boolean::New(result));
}

v8::Handle<v8::Value> MappingWrapper::loadStyleFromFile(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsString()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  v8::String::Utf8Value str(args[0]->ToString());
  std::string filename(*str);
  bool result = obj->mapping_->LoadStyleFromFile(filename.c_str());

  return scope.Close(v8::Boolean::New(result));
}

v8::Handle<v8::Value> MappingWrapper::loadStyleFromString(const v8::Arguments& args) {
  v8::HandleScope scope;
  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsString()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  v8::String::Utf8Value str(args[0]->ToString());
  std::string filename(*str);
  bool result = obj->mapping_->LoadStyleFromString(filename.c_str());

  return scope.Close(v8::Boolean::New(result));
}

v8::Handle<v8::Value> MappingWrapper::setupDataConnection(const v8::Arguments& args) {
  v8::HandleScope scope;

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());
  obj->mapping_->SetupDataConnection();
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> MappingWrapper::renderLabel(const v8::Arguments& args) {
  v8::HandleScope scope;
  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsBoolean()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  bool render_label = args[0]->BooleanValue();
  obj->mapping_->RenderLabelInTile(render_label);

  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> MappingWrapper::setTile(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 3) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  int level = args[0]->NumberValue();
  int row = args[1]->NumberValue();
  int col = args[2]->NumberValue();

  obj->mapping_->SetTile(level, row, col);

  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> MappingWrapper::expand(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsNumber()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());
  obj->mapping_->SetOuterPixels(args[0]->NumberValue());

  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> MappingWrapper::cacheTileFile(const v8::Arguments& args) {
  v8::HandleScope scope;
  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsBoolean()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  bool ultra_sharp = args[0]->BooleanValue();
  bool result = obj->mapping_->CacheTile(ultra_sharp);

  return scope.Close(v8::Boolean::New(result));
}

v8::Handle<v8::Value> MappingWrapper::cacheTileStream(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsBoolean()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  bool ultra_sharp = args[0]->BooleanValue();
  std::string image  = obj->mapping_->CacheTile2(ultra_sharp);

  return scope.Close(v8::String::New(image.c_str()));
}

v8::Handle<v8::Value> MappingWrapper::cacheVectorTile(const v8::Arguments& args) {
  v8::HandleScope scope;

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  bool result  = obj->mapping_->CacheVectorTile();

  return scope.Close(v8::Boolean::New(result));
}

v8::Handle<v8::Value> MappingWrapper::getTileFileName(const v8::Arguments& args) {
  v8::HandleScope scope;

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  std::string filename = obj->mapping_->GetTileName();

  return scope.Close(v8::String::New(filename.c_str()));
}

v8::Handle<v8::Value> MappingWrapper::getVectorTileFileName(const v8::Arguments& args) {
  v8::HandleScope scope;

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  std::string filename = obj->mapping_->GetTileName();

  return scope.Close(v8::String::New(filename.c_str()));
}

v8::Handle<v8::Value> MappingWrapper::getResolution(const v8::Arguments& args) {
  v8::HandleScope scope;

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  double res = obj->mapping_->GetResolution();

  return scope.Close(v8::Number::New(res));
}

v8::Handle<v8::Value> MappingWrapper::getMapDirectory(const v8::Arguments& args) {
  v8::HandleScope scope;

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  std::string dir = obj->mapping_->GetMapDirectory();

  return scope.Close(v8::String::New(dir.c_str()));
}

v8::Handle<v8::Value> MappingWrapper::getOutputDirectory(const v8::Arguments& args) {
  v8::HandleScope scope;

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  std::string dir = obj->mapping_->GetOutputDirectory();

  return scope.Close(v8::String::New(dir.c_str()));
}

v8::Handle<v8::Value> MappingWrapper::setMapDirectory(const v8::Arguments& args) {
  v8::HandleScope scope;
  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsBoolean()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  v8::String::Utf8Value str(args[0]->ToString());
  std::string dir(*str);
  obj->mapping_->SetMapDirectory(dir);

  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> MappingWrapper::setBoundary(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 4) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber() || !args[3]->IsNumber()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  v8::String::Utf8Value str(args[0]->ToString());
  std::string dir(*str);

  obj->mapping_->SetBoundary(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());

  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> MappingWrapper::setOutputDirectory(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsString()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }
  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  v8::String::Utf8Value str(args[0]->ToString());
  std::string dir(*str);
  obj->mapping_->SetOutputDirectory(dir);

  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> MappingWrapper::setFontManager(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 1) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  if (!args[0]->IsObject()) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New("Wrong arguments")));
    return scope.Close(v8::Undefined());
  }

  FontManagerWrapper* fm = node::ObjectWrap::Unwrap<FontManagerWrapper>(args[0]->ToObject());
  MappingWrapper* obj = ObjectWrap::Unwrap<MappingWrapper>(args.This());

  obj->mapping_->set_font_manager(fm->font_manager_);

  return scope.Close(v8::Undefined());
}
