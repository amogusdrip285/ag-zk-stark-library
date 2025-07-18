#ifndef STARK_FFI_H
#define STARK_FFI_H

// This header provides a C-style interface to the C++ libstark code.
// It can be included by C, C++, or other languages via their FFI mechanisms.

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Executes the full STARK proving and verification process for a given TinyRAM program.
 * * This function wraps the entire libstark protocol for a given assembly file.
 * It handles instance/witness generation, proving, and verifying.
 * * @param assembly_path A null-terminated C string representing the path to the TinyRAM assembly file.
 * @param trace_len_log The log base 2 of the maximum trace length (e.g., 10 for 1024 steps).
 * @param security_param The desired security level in bits (e.g., 120).
 * * @return int A status code:
 * -  0: Success, the proof was generated and verified correctly.
 * -  1: Failure, the proof was generated but did not verify.
 * - -1: Error, an exception occurred during the process.
 */
int prove_and_verify_from_file(const char* assembly_path, int trace_len_log, int security_param);

#ifdef __cplusplus
}
#endif

#endif // STARK_FFI_H