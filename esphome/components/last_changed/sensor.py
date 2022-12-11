import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, sensor
from esphome.const import CONF_ID
from esphome.const import DEVICE_CLASS_EMPTY, UNIT_SECOND
from esphome.const import STATE_CLASS_MEASUREMENT
from esphome.const import CONF_SENSOR, CONF_BINARY_SENSOR


last_changed_ns = cg.esphome_ns.namespace("last_changed")
LastChanged = last_changed_ns.class_(
    "LastChanged", sensor.Sensor, cg.Component
)


CONFIG_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_SECOND,
    accuracy_decimals=0,
    device_class=DEVICE_CLASS_EMPTY,
    state_class=STATE_CLASS_MEASUREMENT,
)


CONFIG_SCHEMA = CONFIG_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(LastChanged),
        cv.Optional(CONF_SENSOR): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_BINARY_SENSOR): cv.use_id(binary_sensor.BinarySensor),
    }
).extend(cv.polling_component_schema('60s'))


        # cv.has_exactly_one_key(CONF_SENSOR, CONF_BINARY_SENSOR),
#     )
# )


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    if CONF_SENSOR in config:
        sens = await cg.get_variable(config[CONF_SENSOR])
        cg.add(var.set_sensor(sens))
    if CONF_BINARY_SENSOR in config:
        sens = await cg.get_variable(config[CONF_BINARY_SENSOR])
        cg.add(var.set_binary_sensor(sens))
