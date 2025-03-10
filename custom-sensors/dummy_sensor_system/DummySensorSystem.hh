#ifndef DUMMYSENSORSYSTEM_HH_
#define DUMMYSENSORSYSTEM_HH_

#include <gz/sim/System.hh>
#include <gz/sensors/Sensor.hh>
#include <gz/transport/Node.hh>
#include "../dummy_sensor/DummySensor.hh"




namespace custom
{
  /// \brief Example showing how to tie a custom sensor, in this case a
  /// dummy sensor, into simulation.
  class DummySensorSystem:
    public gz::sim::System,
    public gz::sim::ISystemPreUpdate,
    public gz::sim::ISystemPostUpdate
  {
    // Documentation inherited.
    // During PreUpdate, check for new sensors that were inserted
    // into simulation and create more components as needed.
    public: void PreUpdate(const gz::sim::UpdateInfo &_info,
        gz::sim::EntityComponentManager &_ecm) final;

    // Documentation inherited.
    // During PostUpdate, update the known sensors and publish their data.
    // Also remove sensors that have been deleted.
    public: void PostUpdate(const gz::sim::UpdateInfo &_info,
        const gz::sim::EntityComponentManager &_ecm) final;

    /// \brief Remove custom sensors if their entities have been removed from
    /// simulation.
    /// \param[in] _ecm Immutable reference to ECM.
    private: void RemoveSensorEntities(
        const gz::sim::EntityComponentManager &_ecm);

    /// \brief A map of custom entities to their sensors
    private: std::unordered_map<gz::sim::Entity,
        std::shared_ptr<DummySensor>> entitySensorMap;
  };
}

#endif
