#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace last_changed {

class LastChanged : public sensor::Sensor, public PollingComponent {
  public:
    sensor::Sensor *sensor_;
    binary_sensor::BinarySensor *binary_sensor_;
    unsigned long start_;

    void set_sensor(sensor::Sensor *sensor) { sensor_ = sensor; }
    void set_binary_sensor(binary_sensor::BinarySensor *binary_sensor) { binary_sensor_ = binary_sensor; }
    void dump_config() override;
    void setup() override;
    void update() override;
};

}  // namespace last_changed
}  // namespace esphome
