# Irrigation firmware verification

From the `AGIS/` PlatformIO project directory:

```sh
pio run -e esp32doit-devkit-v1
g++ -std=c++11 -Wall -Wextra -Werror -Ilib/Algorithms \
  lib/Algorithms/{PID,IrrigationControl}.cpp test/irrigation_control.cpp -o /tmp/agis-control-test
/tmp/agis-control-test
```

The host test uses the firmware's actual PID and control step with simulated sensor inputs.
Its plant model feeds the pump PWM back into the next flow sample; it does not verify GPIO,
sensor calibration, or WebSocket delivery on an ESP32.

## Commissioning

The loop runs every five seconds without waiting for Wi-Fi. It cools/ventilates
above 28 °C or 55% relative humidity, and regulates measured flow only when
`"irrigation": {"target_flow_lpm": 1.5}` (example, not a recommended target) is
added to the top level of the SPIFFS `/config.json`. With no positive target the
pump stays off. A positive target requests **continuous** flow; this is not a
watering scheduler or dry-run protection. Validate the target and water supply
before enabling it on hardware.

The shipped config has no Wi-Fi credentials. To enable WebSocket access, add
a `wifi` object with `ssid` and (for a secured network) `password` to the
device's SPIFFS config locally; do not commit credentials.

PWM follows the checked-in schematic: pump GPIO 5 and fan connector XS2 GPIO 14
(GPIO 12 sets its supply polarity). The YF-S201 flow input defaults to GPIO 18
and assumes 450 pulses/L. The DHT11 defaults to GPIO 4 per the firmware config.
If reusing a SPIFFS config with legacy `"waterflow_pin": [2]`, change it to
`[18]` for the schematic wiring. Sensor pins can still be overridden in `wiring`.

Serial (115200 baud) and WebSocket `/ws` emit the same sampled JSON. The
`DHT_Sensor` array is unchanged; `Waterflow_Sensor` reports measured and target
flow (L/min), and `Actuators` reports the two 0–255 PWM commands. `getReadings`
rebroadcasts the latest sample without re-reading sensors.
