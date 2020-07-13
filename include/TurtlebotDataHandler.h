#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "string.h"
#include <vector>
#include "Eigen/Dense"

using namespace Eigen;

class TurtlebotDataHandler{
    private:
        ros::NodeHandle nh_;
        ros::NodeHandle nhLocal_;
        ros::Subscriber map_;
        ros::Subscriber lidar_;
        ros::Subscriber vel_;
        
        //ros::Publisher odom_;

        //Pose = [x, y, theta] (position, orientation)
        std::vector<double> PoseVector_;
        Eigen::Matrix3d Covariance_;

        nav_msgs::OccupancyGrid mapSaved_;
        sensor_msgs::LaserScan laserSaved_;



        bool moving_ = false;

        std::vector<double> velocitySaved_;
        double linearVelocity_;
        double angularVelocity_;

    public:
        bool mapReceived_ = false;
        bool laserReceived_ = false;
        bool movementReceived_ = false;

        ros::Time startMoving_;// = ros::Time::now();
        ros::Time stopMoving_;


        TurtlebotDataHandler(const ros::NodeHandle &nh, const ros::NodeHandle &nhLocal);

        ~TurtlebotDataHandler() = default;

        void init();

        void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& map);

        void lidarCallback(const sensor_msgs::LaserScan::ConstPtr& scan);

        void velocityCallback(const geometry_msgs::Twist::ConstPtr& vel);

        std::vector<double> getPose();
   
        Eigen::Matrix3d getCovariance();

        nav_msgs::OccupancyGrid getMap();

        sensor_msgs::LaserScan getLaser();

        std::vector<double> getVelocity();

};