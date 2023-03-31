<!-- ABOUT THE PROJECT -->
## About The Project

Here's a blank template to get started: To avoid retyping too much info. Do a search and replace with your text editor for the following: `github_username`, `repo_name`, `twitter_handle`, `linkedin_username`, `email_client`, `email`, `project_title`, `project_description`

<p align="right">(<a href="#readme-top">back to top</a>)</p>


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
