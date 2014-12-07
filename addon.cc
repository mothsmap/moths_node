#include <node.h>
#include "moths_for_node.h"

void initAll(v8::Handle<v8::Object> exports) {
  FontManagerWrapper::Init(exports);
  MappingWrapper::Init(exports);
}

NODE_MODULE(moths, initAll)

