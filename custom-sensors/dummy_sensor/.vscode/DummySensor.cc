#include <gz/msgs/stringmsg.pb.h>
#include <gz/common/Console.hh>
#include <gz/sensors/Util.hh>
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

  // Advertise topic where data will be published
  this->pub = this->node.Advertise<gz::msgs::StringMsg>(this->Topic());

  gzmsg << "DummySensor loaded successfully!" << std::endl;

  return true;
}

//////////////////////////////////////////////////
bool DummySensor::Update(const std::chrono::steady_clock::duration &_now)
{
  gz::msgs::StringMsg msg;
  msg.set_data("Hello World");

  this->pub.Publish(msg);
  return true;
}
