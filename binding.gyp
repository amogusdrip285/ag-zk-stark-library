{
  "targets": [
    {
      "target_name": "stark",
      "sources": [
        "addon.cpp",
        "stark_ffi.cpp",
        
        # TinyRAM Sources
        "tinyram/stark-tinyram/src/TinyRAM/TinyRAMDefinitions.cpp",
        "tinyram/stark-tinyram/src/TinyRAM/TinyRAMInstance.cpp",
        "tinyram/stark-tinyram/src/TinyRAMtoBair/ConstraintSystemToBair/cs2Bair.cpp",
        "tinyram/stark-tinyram/src/TinyRAMtoBair/RamToContraintSystem/ALU.cpp",
        "tinyram/stark-tinyram/src/TinyRAMtoBair/RamToContraintSystem/ALUInputConsistency.cpp",
        "tinyram/stark-tinyram/src/TinyRAMtoBair/RamToContraintSystem/generalPurpose.cpp",
        "tinyram/stark-tinyram/src/TinyRAMtoBair/RamToContraintSystem/MemoryConsraints.cpp",
        "tinyram/stark-tinyram/src/TinyRAMtoBair/RamToContraintSystem/traceConsistency.cpp",
        "tinyram/stark-tinyram/src/TinyRAMtoBair/RamToContraintSystem/transitionFunction.cpp",

        # libstark Sources
        "libSTARK/src/protocols/protocol.cpp",
        "libSTARK/src/protocols/Fri/prover.cpp",
        "libSTARK/src/protocols/Fri/verifier.cpp",
        "libSTARK/src/protocols/Fri/common/common.cpp",
        "libSTARK/src/protocols/Fri/verifier_details/queryGenerator.cpp",
        "libSTARK/src/protocols/Ali/prover.cpp",
        "libSTARK/src/protocols/Ali/verifier.cpp",
        "libSTARK/src/protocols/Ali/common_details/common.cpp",
        "libSTARK/src/protocols/Ali/verifier_details/queriesGen.cpp",
        "libSTARK/src/protocols/common/verifier.cpp",
        "libSTARK/src/protocols/common/proofs.cpp",
        "libSTARK/src/protocols/common/CryptoCommitment/MerkleCommitment.cpp",
        "libSTARK/src/reductions/BairToAcsp/BairToAcsp.cpp",
        "libSTARK/src/reductions/BairToAcsp/Details/witnessReduction.cpp",
        "libSTARK/src/reductions/BairToAcsp/Details/witnessMappings.cpp",
        "libSTARK/src/reductions/BairToAcsp/Details/constraints.cpp",
        "libSTARK/src/reductions/BairToAcsp/Details/constraintSystemsTestLocations.cpp",
        "libSTARK/src/reductions/BairToAcsp/Details/commonMappings.cpp",
        "libSTARK/src/reductions/BairToAcsp/Details/commonDeffinitions.cpp",
        "libSTARK/src/reductions/BairToAcsp/Details/AcspSummandsPolynomial.cpp",
        "libSTARK/src/reductions/BairToAcsp/Details/instanceMappings.cpp",
        "libSTARK/src/reductions/BairToAcsp/Details/neighborsConstructor.cpp",
        "libSTARK/src/reductions/BairToAcsp/Details/spaces.cpp",
        "libSTARK/src/reductions/BairToAcsp/Routing/BenesNetwork.cpp",
        "libSTARK/src/reductions/BairToAcsp/Routing/BitReverseButterfliesNetwork.cpp",
        "libSTARK/src/reductions/BairToAcsp/Routing/BtrflyBasedPermutation.cpp",
        "libSTARK/src/reductions/BairToAcsp/Routing/DeBruijnPermutationNet.cpp",
        "libSTARK/src/reductions/BairToAcsp/Routing/FoldNetwork.cpp",
        "libSTARK/src/reductions/BairToAcsp/Routing/LongDeBruijnPermutationNet.cpp",
        "libSTARK/src/reductions/BairToAcsp/Routing/LongSymmetricDeBruijnNetwork.cpp",
        "libSTARK/src/reductions/BairToAcsp/Routing/PermutationRoutingNet.cpp",
        "libSTARK/src/reductions/BairToAcsp/Routing/SymmetricDeBruijnNetwork.cpp",
        "libSTARK/src/reductions/BairToAcsp/Routing/TandemNetwork.cpp",
        "libSTARK/src/languages/Bair/BairWitnessChecker.cpp",
        "libSTARK/src/languages/Bair/ConstraintsSys.cpp",
        "libSTARK/src/languages/Acsp/AcspWitnessChecker.cpp",
        "libSTARK/src/common/Utils/Timing.cpp",
        "libSTARK/src/common/Utils/specsPrint.cpp",
        "libSTARK/src/common/Utils/ErrorHandling.cpp",
        "libSTARK/src/common/Infrastructure/Infrastructure.cpp",
        "libSTARK/src/common/Algebra/MultiVarPoly.cpp",
        "libSTARK/src/common/Algebra/LinearSpace.cpp",
        "libSTARK/src/common/Algebra/ShiftedSubspacePolynomial.cpp",

        # gadgetlib Sources
        "tinyram/gadgetlib/gadgetlib/common_use.cpp",
        "tinyram/gadgetlib/gadgetlib/constraint.cpp",
        "tinyram/gadgetlib/gadgetlib/gadget.cpp",
        "tinyram/gadgetlib/gadgetlib/infrastructure.cpp",
        "tinyram/gadgetlib/gadgetlib/protoboard.cpp",

        # algebralib Sources
        "algebra/algebralib/src/AffinePolynomial.cpp",
        "algebra/algebralib/src/AffineSpace.cpp",
        "algebra/algebralib/src/BitExtract.cpp",
        "algebra/algebralib/src/CircuitPolynomial.cpp",
        "algebra/algebralib/src/ErrorHandling.cpp",
        "algebra/algebralib/src/FFT.cpp",
        "algebra/algebralib/src/FieldElement.cpp",
        "algebra/algebralib/src/LinearPolynomial.cpp",
        "algebra/algebralib/src/MappingsSys.cpp",
        "algebra/algebralib/src/PolynomialDegree.cpp",
        "algebra/algebralib/src/SelectorSum.cpp",
        "algebra/algebralib/src/SubspacePolynomial.cpp",
        "algebra/algebralib/src/UnivariatePolynomialGeneral.cpp",
        "algebra/algebralib/src/variable.cpp",
        "algebra/algebralib/src/novelFFT.cpp",

        # FFT Sources
        "algebra/FFT/src/Basis.cpp",
        "algebra/FFT/src/Definitions.cpp",
        "algebra/FFT/src/Element.cpp",
        "algebra/FFT/src/FFT.cpp",
        "algebra/FFT/src/Polynomials.cpp"
      ],
      "include_dirs": [
        "node_modules/node-addon-api",
        "libSTARK/src",
        "tinyram/stark-tinyram/src",
        "algebra/algebralib/headers",
        "algebra/FFT/src",
        "tinyram/gadgetlib",
        "."
      ],
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1,
          "AdditionalOptions": [
            "/std:c++14",
            "/GR"
          ]
        }
      }
    }
  ]
}
