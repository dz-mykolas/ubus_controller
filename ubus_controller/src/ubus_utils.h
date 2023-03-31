#include <stdlib.h>
#include <stdio.h>
#include <libubus.h>
#include <libubox/blobmsg_json.h>
#include <syslog.h>
#include <string.h>

#include "task_utils.h"

enum {
    USB_CONTROLLER_NAME,
    USB_CONTROLLER_PIN,
    __USB_CONTROLLER_MAX,
};

int start_ubus(struct ubus_context *ctx);

static int usb_controller_get(struct ubus_context *ctx, struct ubus_object *obj,
            struct ubus_request_data *req, const char *method,
            struct blob_attr *msg);
static int usb_controller_on(struct ubus_context *ctx, struct ubus_object *obj,
            struct ubus_request_data *req, const char *method,
            struct blob_attr *msg);
static int usb_controller_off(struct ubus_context *ctx, struct ubus_object *obj,
            struct ubus_request_data *req, const char *method,
            struct blob_attr *msg);
static int controller_helper(char *name, char *action, int pin, struct ubus_context *ctx,
            struct ubus_request_data *req);
