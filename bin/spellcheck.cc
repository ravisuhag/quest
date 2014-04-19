#include <node.h>
#include <v8.h>

#include "spellchecksrc.cc"

using namespace v8;



Handle<Value> initdictMethod(const Arguments& args) {
  HandleScope scope;
  init2();
  return scope.Close(String::New("done"));
}

Handle<Value> matchingMethod(const Arguments& args) {
  HandleScope scope;
  string c_arg = *v8::String::Utf8Value(args[0]->ToString());
  doit(c_arg);
  return scope.Close(String::New(final_ans.c_str()));
}




void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "matched", matchingMethod);
  NODE_SET_METHOD(target, "initdict", initdictMethod);
}

NODE_MODULE(spellcheck, init);






