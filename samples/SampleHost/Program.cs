using Extism.Sdk.Native;

using System.Text;

Environment.SetEnvironmentVariable("WASMTIME_BACKTRACE_DETAILS", "1");

// var path = "../../../../SamplePlugin/bin/Debug/net7.0/SamplePlugin.wasm";
var path = "../../../../SamplePluginNew/bin/Debug/net8.0/wasi-wasm/AppBundle/SamplePluginNew.wasm";

var bytes = File.ReadAllBytes(path);
var context = new Context();
var plugin = context.CreatePlugin(bytes, withWasi: true);
if (plugin.FunctionExists("_start"))
{
    plugin.CallFunction("_start", Span<byte>.Empty);
}

var exists = plugin.FunctionExists("count_vowels");

var output = plugin.CallFunction("count_vowels", Encoding.UTF8.GetBytes("Hello World!"));

Console.WriteLine(Encoding.UTF8.GetString(output));