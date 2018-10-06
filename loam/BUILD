cc_library(
    name = "loam",
    srcs = glob(
        ["src/*.cpp", "src/*.h"],
        exclude = [
            "src/LaserMapping.cpp",
            "src/LaserOdometry.cpp",
            "src/MultiScanRegistration.cpp",
            "src/ScanRegistration.cpp",
            "src/TransformMaintenance.cpp",
        ],
    ),
    hdrs = glob(
        ["include/*.h", "include/*.hpp"],
        exclude = [
            "include/common.h",
            "include/LaserMapping.h",
            "include/LaserOdometry.h",
            "include/MultiScanRegistration.h",
            "include/ScanRegistration.h",
            "include/TransformMaintenance.h",
        ],
    ),
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        "@pcl",
    ],
)
