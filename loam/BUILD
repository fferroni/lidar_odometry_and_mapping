cc_library(
    name = "velodyne",
    srcs = [
        "src/velodyne/velodyne_point_cloud.cpp",
    ],
    hdrs = [
        "include/velodyne/kitti_utils.h",
        "include/velodyne/point_types.h",
        "include/velodyne/velodyne_point_cloud.h",
    ],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        "@opencv",
        "@pcl",
    ],
)

cc_library(
    name = "loam",
    srcs = glob(
        ["src/*.cpp"],
        exclude = ["src/common_ros.cpp"],
    ),
    hdrs = glob(
        ["include/*.h"],
        exclude = ["include/common_ros.h"],
    ),
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        ":velodyne",
        "@pcl",
    ],
)

cc_test(
    name = "scan_registration_test",
    srcs = ["test/scan_registration_test.cpp"],
    deps = [
        ":loam",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "laser_odometry_test",
    srcs = ["test/laser_odometry_test.cpp"],
    deps = [
        ":loam",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "laser_mapping_test",
    srcs = ["test/laser_mapping_test.cpp"],
    deps = [
        ":loam",
        "@googletest//:gtest_main",
    ],
)
