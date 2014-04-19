#include <node.h>
#include <v8.h>

#include "spellchecksrc2.cc"

using namespace v8;



Handle<Value> initdictMethod(const Arguments& args) {
  HandleScope scope;
  init2();
  return scope.Close(String::New("done"));
}

Handle<Value> matchingMethod(const Arguments& args) {
  HandleScope scope;
  string c_arg = *v8::String::Utf8Value(args[0]->ToString());
  string last_ans= final_ans;

  doit2(c_arg);
  if (final_ans.length()<= 1){
  	final_ans= last_ans;
  }

  return scope.Close(String::New(final_ans.c_str()));
}




void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "matched", matchingMethod);
  NODE_SET_METHOD(target, "initdict", initdictMethod);
}

NODE_MODULE(spellcheck, init);






