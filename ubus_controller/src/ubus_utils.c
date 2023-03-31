#include "ubus_utils.h"

static const struct blobmsg_policy usb_controller_policy[] = {
    [USB_CONTROLLER_NAME] = { .name = "name", .type = BLOBMSG_TYPE_STRING },
    [USB_CONTROLLER_PIN] = { .name = "pin", .type = BLOBMSG_TYPE_INT32 },
};

static const struct ubus_method usb_controller_methods[] = {
    UBUS_METHOD_NOARG("get", usb_controller_get),
    UBUS_METHOD("on", usb_controller_on, usb_controller_policy),
    UBUS_METHOD("off", usb_controller_off, usb_controller_policy),
};

static struct ubus_object_type usb_controller_object_type =
    UBUS_OBJECT_TYPE("usb_controller", usb_controller_methods);

static struct ubus_object usb_controller_object = {
    .name = "usb_controller",
    .type = &usb_controller_object_type,
    .methods = usb_controller_methods,
    .n_methods = ARRAY_SIZE(usb_controller_methods),
};

int start_ubus(struct ubus_context *ctx)
{
    uloop_init();
    ctx = ubus_connect(NULL);
    if (ctx == NULL) {
        log_event(LOG_ERR, "Failed to connect to ubus");
        return 1;
    }
    ubus_add_uloop(ctx);
    ubus_add_object(ctx, &usb_controller_object);
    uloop_run();
	uloop_done();
    return 0;
}

int controller_helper(char *name, char *action, int pin, struct ubus_context *ctx, struct ubus_request_data *req)
{
    struct sp_port *port;
    int buffer_s = 30;
    char buffer[buffer_s];
    snprintf(buffer, buffer_s, "{\"action\": \"%s\", \"pin\": %d}", action, pin);
    int size = strlen(buffer);
    unsigned int timeout = 2000;
    int ret;
    struct blob_buf b = {};
    blob_buf_init(&b, 0);
    
    if (sp_get_port_by_name(name, &port) != 0) {
        blobmsg_add_string(&b, "response", "Could not open port");
    } else {
        sp_open(port, SP_MODE_READ_WRITE);
        sp_set_baudrate(port, 9600);
        sp_blocking_write(port, buffer, size, timeout);
        char response[200];
        int bytes_read = sp_blocking_read(port, response, 200, timeout);
        log_event(LOG_ERR, response);
        blobmsg_add_json_from_string(&b, response);
    }
    ret = ubus_send_reply(ctx, req, b.head);
    blob_buf_free(&b);
    sp_free_port(port);
    return ret;
}

static int usb_controller_get(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg)
{
	struct blob_buf b = {};
	blob_buf_init(&b, 0);
    struct USB_device *list = NULL;
    get_usb_ports(&list);

    void *array = blobmsg_open_array(&b, "usb_devices");
    struct USB_device *temp = list;
    while (temp != NULL) {
        void *table = blobmsg_open_table(&b, "");
        blobmsg_add_string(&b, "port_name", temp->port_name);
        char buffer[6];
        sprintf(buffer, "%04X", temp->vid);
        blobmsg_add_string(&b, "vid", buffer);
        sprintf(buffer, "%04X", temp->pid);
        blobmsg_add_string(&b, "pid", buffer);
        blobmsg_close_table(&b, table);
        temp = temp->next;
    }
    blobmsg_close_array(&b, array);
	int ret = ubus_send_reply(ctx, req, b.head);
    llist_remove_all(&list);
	blob_buf_free(&b);
	return ret;
}

static int usb_controller_on(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg)
{
    struct blob_attr *tb[__USB_CONTROLLER_MAX];

    blobmsg_parse(usb_controller_policy, __USB_CONTROLLER_MAX, tb, blob_data(msg), blob_len(msg));
    if (!tb[USB_CONTROLLER_NAME] || !tb[USB_CONTROLLER_PIN])
		return UBUS_STATUS_INVALID_ARGUMENT;

    char *name = blobmsg_get_string(tb[USB_CONTROLLER_NAME]);
    int pin = blobmsg_get_u32(tb[USB_CONTROLLER_PIN]);

	return controller_helper(name, "on", pin, ctx, req);
}

static int usb_controller_off(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg)
{
    struct blob_attr *tb[__USB_CONTROLLER_MAX];

    blobmsg_parse(usb_controller_policy, __USB_CONTROLLER_MAX, tb, blob_data(msg), blob_len(msg));
    if (!tb[USB_CONTROLLER_NAME] || !tb[USB_CONTROLLER_PIN])
		return UBUS_STATUS_INVALID_ARGUMENT;

    char *name = blobmsg_get_string(tb[USB_CONTROLLER_NAME]);
    int pin = blobmsg_get_u32(tb[USB_CONTROLLER_PIN]);

	return controller_helper(name, "off", pin, ctx, req);
}
