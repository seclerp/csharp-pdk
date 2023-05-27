#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/loader.h>

// For some reason, `mono_wasm_invoke_method_ref` is not included in `driver.h` but exist in `driver.c`.
// `mono_wasm_invoke_method` method was deprecated and removed.
void mono_wasm_invoke_method_ref (MonoMethod *method, MonoObject **this_arg_in, void *params[], MonoObject **_out_exc, MonoObject **out_result);