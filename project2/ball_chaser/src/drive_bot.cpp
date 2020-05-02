#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "ball_chaser/DriveToTarget.h"


/* A global ros::Publisher to publish motor commands */
ros::Publisher motor_cmd_pub;



bool drive_callback(ball_chaser::DriveToTarget::Request& req,
                            ball_chaser::DriveToTarget::Response& res)
{
  ROS_INFO("DriveToTargetRequest received - linear_x: %1.2f, angular_z: %1.2f", (float)req.linear_x, (float)req.angular_z);

  // Publish command velocity to "/cmd_vel"
  geometry_msgs::Twist cmd_vel_;

  cmd_vel_.linear.x = req.linear_x; // both of them are float64
  cmd_vel_.angular.z = req.angular_z; // both of them are float64
  
  motor_cmd_pub.publish(cmd_vel_);

  // Return a response message
  res.msg_feedback = "Velocity cmd sent: linear_x = " + std::to_string(cmd_vel_.linear.x) + ", angular_z = " + std::to_string(cmd_vel_.angular.z);

  ROS_INFO_STREAM(res.msg_feedback);
  

  return true;

}

int main(int argc, char** argv)
{
  // Initialize a ROS node
  ros::init(argc, argv, "drive_bot");

  // Create a ROS NodeHandle object
  ros::NodeHandle nh;

  motor_cmd_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

  // Define a drive /ball_chaser/command_robot service with the callback function
  ros::ServiceServer service = nh.advertiseService("/ball_chaser/command_robot", drive_callback);
  ROS_INFO("Ready to send command velocities");


  // Handle ROS communication events
  ros::spin();


  return 0;

}



