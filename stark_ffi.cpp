#include <iostream>
#include <string>
#include <vector>
#include <memory>

// C-style header for the FFI
#include "stark_ffi.h"

// libstark headers
#include "protocols/protocol.hpp"
#include "TinyRAMtoBair/ConstraintSystemToBair/cs2Bair.hpp"
#include "TinyRAMtoBair/RamToContraintSystem/ALU.hpp"
#include "TinyRAM/TinyRAMInstance.hpp"

// These helper functions are kept internal to this .cpp file
// by placing them in an anonymous namespace.
namespace {

libstark::BairInstance constructInstance(const TinyRAMProgram& prog, const unsigned int t){
    resetALU_GadgetGlobalState();
    std::shared_ptr<const TinyRAMProtoboardParams> archParams(new TinyRAMProtoboardParams(prog.archParams().numRegisters, trRegisterLen, trOpcodeLen, 16, 1));
    gadgetlib::ProtoboardPtr pb_instance = gadgetlib::Protoboard::create(archParams);
    cs2Bair cs2bair_instance(pb_instance, prog, int(gadgetlib::POW2(t) - 1), false);
    std::unique_ptr<cs2BairConstraints> cs2bairConstraints_(new cs2BairConstraints(cs2bair_instance));
    std::unique_ptr<cs2BairMemoryCS> cs2bairMemoryCS_(new cs2BairMemoryCS(cs2bair_instance));
    size_t numVars = (cs2bairConstraints_->numVars() / 2);
    return libstark::BairInstance(numVars, t, std::move(cs2bairConstraints_), std::move(cs2bairMemoryCS_), cs2bair_instance.getBoundaryConstraints(), std::vector<Algebra::FieldElement>(numVars, Algebra::zero()));
}

libstark::BairWitness constructWitness(const TinyRAMProgram& prog, const unsigned int t){
    resetALU_GadgetGlobalState();
    std::shared_ptr<const TinyRAMProtoboardParams> archParams(new TinyRAMProtoboardParams(prog.archParams().numRegisters, trRegisterLen, trOpcodeLen, 16, 1));
    gadgetlib::ProtoboardPtr pb_witness = gadgetlib::Protoboard::create(archParams);
    cs2Bair cs2bair_witness(pb_witness, prog, int(gadgetlib::POW2(t) - 1), true);
    std::unique_ptr<cs2BairColoring> cs2bairColoring_(new cs2BairColoring(cs2bair_witness));
    std::unique_ptr<cs2BairMemory> cs2bairMemory_(new cs2BairMemory(cs2bair_witness));
    return libstark::BairWitness(std::move(cs2bairColoring_), std::move(cs2bairMemory_));
}

} // anonymous namespace

//
// This is the implementation of our C-style FFI function.
//
extern "C" int prove_and_verify_from_file(const char* assembly_path, int trace_len_log, int security_param) {
    try {
        // Convert C-style string to a C++ string
        std::string assemblyFile(assembly_path);

        // 1. Initialize global parameters for TinyRAM
        initTinyRAMParamsFromEnvVariables();
        
        // 2. Construct the TinyRAM program and load instructions from the file
        TinyRAMProgram program(assemblyFile, REGISTERS_NUMBER, trRegisterLen);
        program.addInstructionsFromFile(assemblyFile);

        // 3. Construct the BAIR instance and witness from the program
        const auto bairInstance = constructInstance(program, trace_len_log);
        const auto bairWitness = constructWitness(program, trace_len_log);

        // 4. Execute the STARK protocol
        const bool verification_result = libstark::Protocols::executeProtocol(bairInstance, bairWitness, security_param, false, false, true);
        
        // 5. Return the result as a simple integer
        if (verification_result) {
            return 0; // Success: Proof verified
        } else {
            return 1; // Failure: Proof did not verify
        }

    } catch (const std::exception& e) {
        // If any C++ exception occurs, catch it and return an error code.
        // This prevents the exception from crossing the FFI boundary.
        std::cerr << "A C++ exception occurred in STARK FFI: " << e.what() << std::endl;
        return -1; // Error
    } catch (...) {
        // Catch any other unknown exceptions
        std::cerr << "An unknown exception occurred in STARK FFI." << std::endl;
        return -1; // Error
    }
}