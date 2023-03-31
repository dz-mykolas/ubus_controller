#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <libserialport.h>
#include <string.h>

struct USB_device {
    char port_name[20];
    int vid;
    int pid;
    struct USB_device *next;
};

void log_event(int type, char *log);
struct USB_device *create_node(char *port_name, int vid, int pid);
void llist_add_end(struct USB_device **list, struct USB_device *d);
void llist_remove_all(struct USB_device **list);
void *get_usb_ports(struct USB_device **list);
