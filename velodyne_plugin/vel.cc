#include <gazebo/gazebo_config.h>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>

#include <gazebo/gazebo_client.hh>

int main(int _argc, char **_argv)
{
    //load gazebo as a client
    gazebo::client::setup(_argc, _argv);

    //create a node for communication
    gazebo::transport::NodePtr node(new gazebo::transport::Node());
    node->Init();

    //publish to the velodyne topic
    gazebo::transport::PublisherPtr pub = 
        node->Advertise<gazebo::msgs::Vector3d>("~/my_velodyne/vel_cmd");

    //wait for a subscriber to connect to the publisher
    pub->WaitForConnection();

    //Create a Vector3d message
    gazebo::msgs::Vector3d msg;

    //set the velocity in the x-component
    gazebo::msgs::Set(&msg, ignition::math::Vector3d(std::atof(_argv[1]),0,0));

    //send the message
    pub->Publish(msg);

    //make sure to shut everything down
    gazebo::client::shutdown();
}