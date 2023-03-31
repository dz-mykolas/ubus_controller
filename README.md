# ubus_controller
ubus call usb_controller on '{"name":"/dev/ttyUSB0","pin":16}'
ubus call usb_controller get
ubus -v list usb_controller
opkg install ubus_controller_1.0.0-1_arm_cortex-a7_neon-vfpv4.ipk -force-reinstall
