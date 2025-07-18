#include <napi.h>
#include "stark_ffi.h" // Your C header

// This is the bridge function exposed to JavaScript
Napi::Number ProveAndVerifyWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Get arguments from JavaScript
    std::string path = info[0].As<Napi::String>().Utf8Value();
    int trace_len = info[1].As<Napi::Number>().Int32Value();
    int security_param = info[2].As<Napi::Number>().Int32Value();

    // Call the actual C function from your library
    int result = prove_and_verify_from_file(path.c_str(), trace_len, security_param);

    // Return the result to JavaScript
    return Napi::Number::New(env, result);
}

// Boilerplate to register the addon
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "proveAndVerify"),
                Napi::Function::New(env, ProveAndVerifyWrapped));
    return exports;
}

NODE_API_MODULE(stark, Init)