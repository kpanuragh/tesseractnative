{
    "targets": [{
        "target_name": "tessractnative",
        "sources": [
            "src/main.cc",
            "src/hocr/hocr.cc",
            "src/skew_fix/skew_fix.cc",
            "src/fix_rotate/fix_rotate.cc"
        ],
          "cflags" : [
			"-std=c++11"
		],
		"cflags!" : [
			"-fno-exceptions"
		],
         "libs":[
             "opencv4"
         ], 
		"cflags_cc!": [
			"-fno-rtti",
			"-fno-exceptions"
		],
		"ldflags" : [
			"-Wl,-rpath,'$$ORIGIN'"
		],
        'conditions': [
      ['OS=="linux"', {
 'include_dirs': [
            "/usr/local/include/opencv4/"
        ]
      }],
      ['OS=="win"', {
          'include_dirs': [
            "<!(node env_windows_include.js)"
        ],
        'libraries': ["ws2_32.lib","<!(node env_windows_lib.js)"],
           "copies": [
            {
              "destination": "<(module_root_dir)/build/Release",
              "files": ["<!(node env_windows_dll.js)"]
            }
          ]
      }]],
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
        
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }],
     
}