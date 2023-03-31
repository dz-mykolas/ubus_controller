<!-- USAGE EXAMPLES -->
## Usage
List available functions for this program
```sh
ubus -v list usb_controller
```
Get connected USB devices
```sh
ubus call usb_controller get
```
Turn on device example
```sh
ubus call usb_controller 'function' '{"name":"device_port","pin":pin_on_device}'
ubus call usb_controller on '{"name":"/dev/ttyUSB0","pin":16}'
```
