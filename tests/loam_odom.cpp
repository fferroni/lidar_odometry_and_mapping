#include <cmath>
#include <vector>

#include <common.h>
#include <load_imu.h>
#include <scan_registration.h>
#include <laser_odometry.h>
#include <laser_mapping.h>

#include <velodyne/point_types.h>
#include <velodyne/velodyne_point_cloud.h>
#include <velodyne/kitti_utils.h>

#include <pcl/io/ply_io.h>


using namespace velodyne_pointcloud;
using namespace but_velodyne;

const float SCAN_PERIOD = 0.1;

bool endsWith(const std::string& str, const std::string& suffix) {
    return suffix == str.substr(str.size() - suffix.size());
}

/**
 * Usage:
 * bazel build -c opt tests:loam_odom
 * ./bazel-bin/tests/loam_odom pose_file.txt aggregated.ply $(ls *.bin | sort | xargs)
 */
int main(int argc, char** argv) {

    // first argument is pose file dump
    std::ofstream output_file;
    output_file.open(argv[1]);

    // second argument is aggregated cloud PLY
    std::string output_ply = argv[2];

    // rest of arguments are sorted .bin files of a KITTI sequence
    std::vector<std::string> clouds_to_process;
    for (auto i=3; i < argc; ++i)
    {
        clouds_to_process.push_back(argv[i]);
    }

    LoamImuInput imu(SCAN_PERIOD);
    ScanRegistration scanReg(imu, SCAN_PERIOD);
    LaserOdometry laserOdom(SCAN_PERIOD);
    LaserMapping mapping(SCAN_PERIOD);

    pcl::PointCloud<pcl::PointXYZ> aggregated_cloud;
    VelodynePointCloud cloud;
    float time = 0;
    for (auto i = 0; i < clouds_to_process.size(); i++) {
        std::string filename = clouds_to_process[i];

        if (endsWith(filename, ".bin"))
        {
            but_velodyne::VelodynePointCloud::fromKitti(filename, cloud);
        }
        else
        {
            std::cout << "Not valid file" << std::endl;
            return -1;
        }

        LaserOdometry::Inputs odomInputs;
        scanReg.run(cloud, time, odomInputs);

        LaserMapping::Inputs mappingInputs;
        laserOdom.run(odomInputs, mappingInputs);

        LaserMapping::Outputs mappingOutputs;
        mapping.run(mappingInputs, mappingOutputs, time);

        Eigen::Affine3f transf = pcl::getTransformation(-mappingOutputs.transformToMap[3],
                                                        -mappingOutputs.transformToMap[4],
                                                         mappingOutputs.transformToMap[5],
                                                        -mappingOutputs.transformToMap[0],
                                                        -mappingOutputs.transformToMap[1],
                                                         mappingOutputs.transformToMap[2]);

        time += SCAN_PERIOD;

        // aggregate (need to first get point cloud back into KITTI coordinates)
        auto xyz = cloud.getXYZCloudPtr();
        Eigen::Matrix4f transformation;
        transformation << 0, -1,  0,  0, 0,  0, -1,  0, 1,  0,  0,  0, 0,  0,  0,  1;
        auto t = transformation * transf.matrix() * transformation;
        std::cout << t << std::endl;
        output_file << t << std::endl;
        pcl::transformPointCloud(*xyz, *xyz, t);
        aggregated_cloud += *xyz;
        pcl::io::savePLYFileBinary(output_ply, aggregated_cloud);
    }

    output_file.close();
    return 0;
}
