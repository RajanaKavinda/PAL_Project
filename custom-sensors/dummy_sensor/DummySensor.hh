#ifndef DUMMY_SENSOR_HH_
#define DUMMY_SENSOR_HH_

#include <gz/sensors/Sensor.hh>
#include <gz/transport/Node.hh>

namespace custom
{
  /// \brief A simple custom sensor that publishes "Hello World"
  class DummySensor : public gz::sensors::Sensor
  {
    /// \brief Load the sensor with SDF parameters.
    /// \param[in] _sdf SDF Sensor parameters.
    /// \return True if loading was successful
    public: virtual bool Load(const sdf::Sensor &_sdf) override;

    /// \brief Update the sensor and generate data
    /// \param[in] _now The current time
    /// \return True if the update was successful
    public: virtual bool Update(
      const std::chrono::steady_clock::duration &_now) override;

    /// \brief Node for communication
    private: gz::transport::Node node;

    /// \brief Publishes sensor data
    private: gz::transport::Node::Publisher pub;
  };
}

#endif
