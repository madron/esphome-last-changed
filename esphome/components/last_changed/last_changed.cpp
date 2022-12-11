#include "last_changed.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"


namespace esphome {
namespace last_changed {

static const char *const TAG = "last_changed";
float sensor_state;
bool binary_sensor_state;

void LastChanged::dump_config() {
  ESP_LOGCONFIG(TAG, "LastChanged");
}

void LastChanged::setup() {
  this->publish_state(0);
  this->start_ = millis();
  // Sensor
  if (this->sensor_ != nullptr) {
    sensor_state = this->sensor_->get_raw_state();
    this->sensor_->add_on_state_callback([this](float state) {
      if (this->sensor_->get_raw_state() != sensor_state) {
        this->start_ = millis();
        sensor_state = this->sensor_->get_raw_state();
      }
    });
  }
  // BinarySensor
  if (this->binary_sensor_ != nullptr) {
    binary_sensor_state = this->binary_sensor_->state;
    this->binary_sensor_->add_on_state_callback([this](bool state) {
      if (this->binary_sensor_->state != binary_sensor_state) {
        this->start_ = millis();
        binary_sensor_state = this->binary_sensor_->state;
      }
    });
  }
}

void LastChanged::update() {
  this->publish_state((millis() - this->start_) / 1000);
}

}  // namespace last_changed
}  // namespace esphome
