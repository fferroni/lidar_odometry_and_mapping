cc_library(
    name = "loam",
    srcs = glob(
        ["src/*.cpp", "src/*.h"],
    ),
    hdrs = glob(
        ["include/**/*.h", "include/**/*.hpp"],
    ),
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        "@pcl",
    ],
)
