#include "last_changed.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"


namespace esphome {
namespace last_changed {

static const char *const TAG = "last_changed";

void LastChanged::dump_config() {
  ESP_LOGCONFIG(TAG, "LastChanged");
}

void LastChanged::setup() {
  this->publish_state(0);
  this->start_ = millis();
  if (this->sensor_ != nullptr) {
    this->sensor_->add_on_state_callback([this](float state) {
      this->start_ = millis();
    });
  }
}

void LastChanged::update() {
  this->publish_state((millis() - this->start_) / 1000);
}

}  // namespace last_changed
}  // namespace esphome
