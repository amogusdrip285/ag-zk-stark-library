import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'dart:io'; // Import the full dart:io library
import 'package:path/path.dart' as p;

// Define a typedef for the C function's signature
typedef ProveAndVerifyFunc = ffi.Int32 Function(
    ffi.Pointer<Utf8> path, ffi.Int32 traceLog, ffi.Int32 securityParam);

// Define a typedef for the Dart function's signature
typedef ProveAndVerify = int Function(
    ffi.Pointer<Utf8> path, int traceLog, int securityParam);

void main() {
  // 1. Load the shared library.
  // Since you are on Windows and have a .dll file, we specify it directly.
  final libraryPath = p.join(Directory.current.path, 'stark_library.dll');
  final dylib = ffi.DynamicLibrary.open(libraryPath);

  // 2. Look up the function symbol
  final proveAndVerify = dylib
      .lookup<ffi.NativeFunction<ProveAndVerifyFunc>>('prove_and_verify_from_file')
      .asFunction<ProveAndVerify>();

  // 3. Call the function
  print('Calling STARK proof from Dart...');
  // Note: Dart FFI requires absolute paths for file access from C++.
  final assemblyPath =
      '/mnt/c/dev/libSTARK/examples-tinyram/collatz_clean.asm'.toNativeUtf8();
  
  final result = proveAndVerify(assemblyPath, 10, 120);
  
  print('STARK FFI returned: $result'); // Should be 0

  // 4. Free the allocated C string
  malloc.free(assemblyPath);
}