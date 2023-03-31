#include "task_utils.h"

void log_event(int type, char *log)
{
	setlogmask(LOG_UPTO(LOG_NOTICE));
	openlog("ubus_usb_controller", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);
	char buffer[500];
	snprintf(buffer, 500, "%s", log);
	syslog(type, "%s", buffer);
	closelog();
}

struct USB_device *create_node(char *port_name, int vid, int pid)
{
    struct USB_device *d = (struct USB_device *) malloc(sizeof(struct USB_device));
    if (d == NULL) {
        return NULL;
    }
    strcpy(d->port_name, port_name);
    d->vid = vid;
    d->pid = pid;
    d->next = NULL;

    return d;
}

void llist_add_end(struct USB_device **list, struct USB_device *d)
{
    struct USB_device *temp = *list;
    if (temp == NULL) {
        *list = d;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = d;
}

void llist_remove_all(struct USB_device **list)
{
    struct USB_device *head = *list;
    while (head != NULL) {
        struct USB_device *temp;
        temp = head;
        head = head->next;
        free(temp);
    }
    *list = NULL;
}

void *get_usb_ports(struct USB_device **list)
{
    struct sp_port **port_list;
    enum sp_return result = sp_list_ports(&port_list);
    if (result != SP_OK) {
        log_event(LOG_ERR, "Failed to get ports");
        sp_free_port_list(port_list);
        return NULL;
    }

    int count = 0;
    for (int i = 0; port_list[i] != NULL; i++) {
        struct sp_port *port = port_list[i];
        enum sp_transport transport = sp_get_port_transport(port);
        if (transport == SP_TRANSPORT_USB) {
            char *port_name = sp_get_port_name(port);
		    int usb_vid, usb_pid;
		    sp_get_port_usb_vid_pid(port, &usb_vid, &usb_pid);
            struct USB_device *d = NULL;
            d = create_node(port_name, usb_vid, usb_pid);
            llist_add_end(list, d);
        }
    }
    sp_free_port_list(port_list);
}
