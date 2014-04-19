#include <node.h>
#include <v8.h>

#include <spellchecksrc>

using namespace v8;
using namespace std;


Handle<Value> initdictMethod(const Arguments& args) {
  HandleScope scope;
  init2();

  return scope.Close(String::New(final_ans.c_str()));
}


Handle<Value> matchingMethod(const Arguments& args) {
  HandleScope scope;

  doit("lappy");

  return scope.Close(String::New(final_ans.c_str()));
}




void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "matched", matchingMethod);
  NODE_SET_METHOD(target, "initdict", initdictMethod);
}

NODE_MODULE(spellcheck, init);






