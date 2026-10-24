# MQTT Topics

All topics are namespaced by `DEVICE_ID`, e.g. `home/plug-001/...`

| Topic | Direction | Retained | Payload | Description |
|-------|-----------|----------|---------|-------------|
| `home/<DEVICE_ID>/command` | **subscribe** | no | `ON` / `OFF` / `TOGGLE` | Control the relay |
| `home/<DEVICE_ID>/state`   | publish | **yes** | `ON` / `OFF` | Current relay state |
| `home/<DEVICE_ID>/status`  | publish | **yes** | `online` / `offline` | LWT (Last Will) |

## Example (Mosquitto CLI)

Turn ON:
```bash
mosquitto_pub -h <broker> -u <user> -P <pass> \
  -t "home/plug-001/command" -m "ON"
