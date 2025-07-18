{
  "targets": [
    {
      "target_name": "stark",
      "sources": [ "addon.cpp" ],
      "include_dirs": [
        "/mnt/c/dev/libSTARK/node_modules/node-addon-api",
        "/mnt/c/dev/libSTARK/node_modules/napi-macros",
        "/mnt/c/dev/libSTARK/libstark/src",
        "/mnt/c/dev/libSTARK/tinyram/stark-tinyram/src",
        "/mnt/c/dev/libSTARK/algebra/algebralib/headers",
        "/mnt/c/dev/libSTARK/algebra/FFT/src",
        "/mnt/c/dev/libSTARK/tinyram/gadgetlib",
        "/mnt/c/dev/libSTARK"
      ],
      "link_settings": {
        "libraries": [
          "-L/mnt/c/dev/libSTARK/bin/libstark",
          "-L/mnt/c/dev/libSTARK/bin/gadgetlib",
          "-L/mnt/c/dev/libSTARK/bin/algebralib",
          "-L/mnt/c/dev/libSTARK/bin/FFT",
          "-Wl,-Bstatic", "-lstark", "-lgadgetlib", "-lalgebralib", "-lfft", "-lgmp",
          "-Wl,-Bdynamic", "-lpthread", "-fopenmp"
        ]
      },
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "msvs_settings": {
        "VCCLCompilerTool": { "ExceptionHandling": 1 }
      }
    }
  ]
}