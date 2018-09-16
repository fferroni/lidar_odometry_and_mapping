licenses(["notice"])

package(default_visibility = ["//visibility:public"])

# This assumes you have opencv pre-installed in your system.
cc_library(
    name = "opencv",
    hdrs = glob(["opencv/*.h"]),
    linkopts = [
        "-L/usr/local/lib",
        "-lopencv_core"
    ],
    includes = ["."],
)