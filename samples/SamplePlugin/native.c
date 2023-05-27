#pragma once
#define NDEBUG
// https://github.com/dotnet/runtime/blob/v7.0.0/src/mono/wasi/mono-wasi-driver/driver.c
#include <string.h>

#include <mono-wasi/driver.h>
#include <mono/metadata/exception.h>
#include <assert.h>

int initialize_dotnet_plugin_runtime() {
	// Assume the runtime pack has been copied into the output directory as 'runtime'
	// Otherwise we have to mount an unrelated part of the filesystem within the WASM environment
	const char* app_base_dir = "./WasiConsoleApp/bin/Debug/net7.0";
	char* assemblies_path;
	asprintf(&assemblies_path, "%s:%s/runtime/native:%s/runtime/lib/net7.0", app_base_dir, app_base_dir, app_base_dir);

	add_assembly(app_base_dir, "WasiConsoleApp.dll");
	mono_set_assemblies_path(assemblies_path);

	mono_wasm_load_runtime("", 0);

	MonoAssembly* assembly = mono_wasm_assembly_load ("WasiConsoleApp.dll");
	MonoMethod* entry_method = mono_wasm_assembly_get_entry_point (assembly);
	MonoObject* out_exc;
	MonoObject *exit_code = mono_wasm_invoke_method (entry_method, NULL, NULL, &out_exc);
	return mono_unbox_int (exit_code);
}


MonoMethod* method_CountVowels;
__attribute__((export_name("count_vowels"))) int count_vowels()
{
	if (!method_CountVowels)
	{
		mono_wasm_load_runtime("unused", 0);
		method_CountVowels = lookup_dotnet_method("SamplePlugin", "SamplePlugin", "Functions", "CountVowels", -1);
		assert(method_CountVowels);
	}

	void* method_params[] = { };
	MonoObject* exception;
	MonoObject* result = mono_wasm_invoke_method(method_CountVowels, NULL, method_params, &exception);
	assert(!exception);

	int int_result = mono_unbox_int(result);
	return int_result;
}