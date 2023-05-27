using System;

internal class Program
{
  // Investigate why non-empty argument list leads to error
  // https://github.com/dotnet/runtime/blob/release/8.0-preview4/src/mono/mono/metadata/object.c#L4239
  public static void Main()
  {
    Console.WriteLine("Hello, Wasi Console!");
  }
}