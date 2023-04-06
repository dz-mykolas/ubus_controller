#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <libserialport.h>
#include <string.h>

#define CH340_VENDOR 0x1A86
#define CH340_PRODUCT 0x7523
#define CP2102_VENDOR 0X10C4
#define CP2102_PRODUCT 0xEA60

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
int check_compatible(int vid, int pid);
void *get_usb_ports(struct USB_device **list);
