{
    "targets": [{
        "target_name": "tessractnative",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "src/main.cc",
            "src/hocr/hocr.cc"
        ],
        'configurations': {
            'Debug': {
                'msvs_settings': {
                            'VCCLCompilerTool': {
                                'RuntimeLibrary': '3' # /MDd
                    },
                },
            },
            'Release': {
                'msvs_settings': {
                            'VCCLCompilerTool': {
                                'RuntimeLibrary': '2' # /MD
                    },
                },
            },
        },
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': ["ws2_32.lib"],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}