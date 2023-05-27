#pragma once
#define NDEBUG
// https://github.com/dotnet/runtime/blob/v7.0.0/src/mono/wasi/mono-wasi-driver/driver.c
#include <string.h>

#include <wasm/driver.h>
#include <mono/metadata/exception.h>
#include <assert.h>

#include "include/driver_ex.h"

MonoMethod* method_CountVowels;
__attribute__((export_name("count_vowels"))) int count_vowels()
{
	if (!method_CountVowels)
	{
		method_CountVowels = lookup_dotnet_method("SamplePluginNew", "SamplePluginNew", "Functions", "CountVowels", -1);
		assert(method_CountVowels);
	}

	void* method_params[] = { };
	MonoObject* exception;
	MonoObject* result;
	mono_wasm_invoke_method_ref(method_CountVowels, NULL, method_params, &exception, &result);
	assert(!exception);

	int int_result = mono_unbox_int(result);
	return int_result;
}