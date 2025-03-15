#include <gz/msgs/stringmsg.pb.h>
#include <gz/common/Console.hh>
#include <gz/sensors/Util.hh>
#include <gz/msgs/Utility.hh>
#include "DummySensor.hh"

using namespace custom;

//////////////////////////////////////////////////
bool DummySensor::Load(const sdf::Sensor &_sdf)
{
  auto type = gz::sensors::customType(_sdf);
  if ("dummy" != type)
  {
    gzerr << "Trying to load [dummy] sensor, but got type ["
          << type << "] instead." << std::endl;
    return false;
  }

  // Load common sensor params
  gz::sensors::Sensor::Load(_sdf);

  // Create a node for communication
  if (this->Topic().empty())
    this->SetTopic("/dummy_sensor");

  // Advertise topic where data will be published
  this->pub = this->node.Advertise<gz::msgs::StringMsg>(this->Topic());

  gzlog << "DummySensor topic: " << this->Topic() << std::endl;
  gzlog << "DummySensor loaded successfully!" << std::endl;

  return true;
}

//////////////////////////////////////////////////
bool DummySensor::Update(const std::chrono::steady_clock::duration &_now)
{
  gz::msgs::StringMsg msg;
  
  *msg.mutable_header()->mutable_stamp() = gz::msgs::Convert(_now);
  msg.set_data(this->message);

  this->pub.Publish(msg);
  return true;
}
