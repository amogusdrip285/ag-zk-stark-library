#include <iostream>

// Include the C-style header for the function we want to test.
// This ensures our test program knows the function's signature.
#include "stark_ffi.h"

int main() {
    // Define the parameters for the STARK protocol test.
    // We use the known-good 'collatz_clean.asm' file you created.
    const char* assembly_file = "/mnt/c/dev/libSTARK/examples-tinyram/collatz_clean.asm";
    int trace_len_log = 10;
    int security_param = 120;

    std::cout << "Testing the STARK FFI function..." << std::endl;
    std::cout << "---------------------------------" << std::endl;

    // Call the C-style FFI function from your stark_ffi.cpp file.
    int result = prove_and_verify_from_file(assembly_file, trace_len_log, security_param);

    std::cout << "---------------------------------" << std::endl;
    std::cout << "FFI function returned status code: " << result << std::endl;

    // Check the result and print a clear pass/fail message.
    if (result == 0) {
        std::cout << "TEST PASSED: Proof verified successfully." << std::endl;
        return 0; // Exit with success code
    } else if (result == 1) {
        std::cout << "TEST FAILED: Proof did not verify." << std::endl;
        return 1; // Exit with a failure code
    } else {
        std::cout << "TEST FAILED: An error occurred during the process." << std::endl;
        return 1; // Exit with a failure code
    }
}