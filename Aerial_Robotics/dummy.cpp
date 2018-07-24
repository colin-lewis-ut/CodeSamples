#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include <sstream>
#include <math.h>

using namespace std;

//Provides dummy inputs to test linear regression calculations without dependency on upstream CV scripts

geometry_msgs::PoseStamped testp;

int main(int argc, char **argv)
{
   ros::init(argc, argv, "dummy");
   ros::NodeHandle n;
   int count = 0;

   ros::Publisher chatter_pub = n.advertise<geometry_msgs::PoseStamped>("roombaPose", 1000);//creates a Publisher channel which linreg subscribes to

   ros::Rate loop_rate(10);//Publish rate. Does not need to mathc realtime data in dummy

   while (ros::ok())//simple main loop which publishes ascending numbers
   {
      testp.pose.position.x = count;
      testp.pose.position.y = count;
      testp.pose.position.z = 2.9;//elevation not needed for this gen of testing; fixed for convenience
      testp.header.stamp.nsec = count;
      chatter_pub.publish(testp);
      cout<<testp<<endl;
      ++count;
      ros::spinOnce();
      loop_rate.sleep();
   }
  return 0;
}
