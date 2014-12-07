{
	"includes": [
		    '../moths/3rd/skia/gyp/common.gypi',
		    ],
    'targets': [
        {
            'target_name': 'moths',
	    'includes': [
                '../moths/gyp/mapping.gypi',
                ],
            'sources': [
                '../moths/gyp/mapping.gypi', 'addon.cc', 'moths_for_node.cc',
                ],
'cflags_cc': [
	'-fexceptions',
	],

             'dependencies': [
                    '../moths/3rd/skia/gyp/etc1.gyp:libetc1',
                    '../moths/3rd/skia/gyp/flags.gyp:flags',
                    '../moths/3rd/skia/gyp/jsoncpp.gyp:jsoncpp',
                    '../moths/3rd/skia/gyp/pdf.gyp:pdf',
                    '../moths/3rd/skia/gyp/skia_lib.gyp:skia_lib',
                    '../moths/3rd/skia/gyp/tools.gyp:crash_handler',
                    '../moths/3rd/skia/gyp/tools.gyp:gm_expectations',
                    '../moths/3rd/skia/gyp/tools.gyp:proc_stats',
                    '../moths/3rd/skia/gyp/tools.gyp:resources',
                    '../moths/3rd/skia/gyp/tools.gyp:sk_tool_utils',
                    ],

		

    #        'direct_dependent_settings': {
                'include_dirs': [
                    '../g-map/src/mapping_core/',
                    '../moths/3rd/rapidjson/include/',
                    '../moths/3rd/agg/include/',
                    '../moths/3rd/skia/src/core',
                    '../moths/3rd/skia/src/effects',
                    '../moths/3rd/skia/src/images',
                    '../moths/3rd/skia/src/pipe/utils',
                    '../moths/3rd/skia/src/utils',
                    ],
                'defines': [
                    '_USE_MATH_DEFINES',
                    ],
#                },
            'link_settings': {
                "ldflags": [
                    '-lgeos_c',
                    '-lgdal',
                    '-L/usr/local/lib',
                    '-lprotobuf-lite',
                    '-L/home/xuxiang/Documents/boost_1_56_0/stage/lib/',
                    '-lboost_system',
                    '-lboost_thread',
                    '-lboost_filesystem',
                    ],
                },
            },
        ],
    }
