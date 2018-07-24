#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include <sstream>
#include <deque>
#include <cmath>


using namespace std;

//Calculates predicted positions fo observed targets through linear regression

//not proud of how many global variables are here, but allows for rapid changes
std_msgs::String msg;
std::stringstream ss_mode;
geometry_msgs::PoseStamped RoombaPose;
geometry_msgs::PoseStamped waypoint;
geometry_msgs::PoseStamped newpoint;
deque<geometry_msgs::PoseStamped> points;//very helpful default structure "double ended que"; iterable, pushable & poppable

void chatterCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)//function that is called when a message is received
{
 newpoint=*msg;
 newpoint.pose.position.z=1.5;
 if (newpoint.pose.position.x != points.front().pose.position.x || newpoint.pose.position.y != points.front().pose.position.y){ //checks against oversampling, as targets rarely stop
    if (points.size() <= 5){//limits the number of relevant points included
     points.push_front(newpoint);
      cout<<"push front" << endl;
    }
    else {
     points.pop_back();
     points.push_front(newpoint);
     cout<<"pop back"<< endl;
    }
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "linreg");//Creates ROS node

  ros::NodeHandle n;//self referencing handle for ROS interfacing
  geometry_msgs::PoseStamped buffer;//handle for incoming messages

  ros::Subscriber sub = n.subscribe("roombaPose", 1, chatterCallback);
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::PoseStamped>("waypoint", 1);//publishes waypoint targets, used by control's code
  ros::Publisher mode_pub = n.advertise<std_msgs::String>("mode", 1);
 
  ss_mode << "SEARCH"; //ss_mode is used to set control code mode
  msg.data = ss_mode.str();
  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
  ss_mode.str("");
  double mx = 0, my = 0, sx = 0, sy = 0, st = 0, sxt = 0, syt = 0, sy2 = 0, sx2 = 0, st2 = 0, ix = 0, iy = 0;

    //when enough points are supplied, this block calculates a waypoint using location & time data supplied through the deques
    if (points.size() >= 5){
       for (int i = 0; i < points.size()-1; i++){

          double nx = points[i].pose.position.x - points.back().pose.position.x;
          double ny = points[i].pose.position.y - points.back().pose.position.y;
          double nt = (points[i].header.stamp.sec + points[i].header.stamp.nsec * pow(10,-9)) - (points.back().header.stamp.sec + points.back().header.stamp.nsec * pow(10,-9));//extracts the time from the message time stamps
          sx = sx + nx;
          sy = sy + ny;
          st = st + nt; 
          sxt = sxt + nx * nt;
          syt = syt + ny * nt;
          sx2 = sx2 + nx * nx;
          sy2 = sy2 + ny * ny;
          st2 = st2 + nt * nt;
       }

       cout<<"delta T in use: "<<st<<endl;
       cout<<"the back x point is "<<points.back().pose.position.x<<endl;

       mx = ((points.size()-1)*sxt-sx*st)/((points.size()-1)*st2-(st*st));//finds dx/dt
       my = ((points.size()-1)*syt-sy*st)/((points.size()-1)*st2-(st*st));//finds dy/dt
       
    }
    //normalized velocity; compared to known real velocity
    double mxy = sqrt(pow(mx,2) + pow(my,2));
    mx = mx/mxy;
    my = my/mxy;
    cout<<"dx/dt norm: "<<mx<<endl;
    cout<<"dy/dt norm: "<<my<<endl;

//target moves at .33 m/s, waypoints are projected 10s ahead

    waypoint.pose.position.x = (10 *.33 *mx);
    waypoint.pose.position.y = (10 *.33 *my);
    waypoint.pose.position.z = .5; 
    
    if (points.size() >= 5)//this block uses waypoints once enough data is supplied
    {
      ss_mode << "GOTO";
      msg.data = ss_mode.str();
      while (ros::ok())
      {
        chatter_pub.publish(waypoint);
        mode_pub.publish(msg);
      }
      break;
    }
    mode_pub.publish(msg);//else just the mode message is published
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  return 0;
}
