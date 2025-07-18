#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <protocols/protocol.hpp>
#include <TinyRAMtoBair/ConstraintSystemToBair/cs2Bair.hpp>
#include <TinyRAMtoBair/RamToContraintSystem/ALU.hpp>
#include <TinyRAM/TinyRAMInstance.hpp>

// Forward declarations for helper functions
libstark::BairInstance constructInstance(const TinyRAMProgram& prog, const unsigned int t);
libstark::BairWitness constructWitness(const TinyRAMProgram& prog, const unsigned int t);

// Main execution function, adapted from the official example
void execute(const std::string& assemblyFile, const unsigned int t, const unsigned int securityParameter){
    std::cout << "Executing simulation with assembly from " << assemblyFile << " over 2^" << t <<"-1 steps, and soundness error at most 2^-" << securityParameter << std::endl;
    
    // CRITICAL FIX 1: Use the correct initialization function
    initTinyRAMParamsFromEnvVariables(); 
	
    // CRITICAL FIX 2: Construct the program and explicitly load instructions
    TinyRAMProgram program(assemblyFile, REGISTERS_NUMBER, trRegisterLen);
    program.addInstructionsFromFile(assemblyFile);
    
    // Construct the instance and witness
    const auto bairInstance = constructInstance(program, t);
    const auto bairWitness = constructWitness(program, t);
    
    // Run the protocol
    libstark::Protocols::executeProtocol(bairInstance, bairWitness, securityParameter, false, false, true);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <assembly_file_path> -t<trace_length_log2> -s<security_parameter>" << std::endl;
        std::cout << "Example: " << argv[0] << " /mnt/c/dev/libSTARK/examples-tinyram/collatz.asm -t10 -s120" << std::endl;
        return 1;
    }

    std::string assemblyFile(argv[1]);
    unsigned int executionLenLog = std::stoul(std::string(argv[2]).substr(2));
    unsigned int securityParameter = std::stoul(std::string(argv[3]).substr(2));

    execute(assemblyFile, executionLenLog, securityParameter);

    return 0;
}

// Helper function implementations (copied from official main.cpp)
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