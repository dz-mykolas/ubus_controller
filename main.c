#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libserialport.h>

/* PORT INFO */
struct USB_device {
    char port_name[20];
    int vid;
    int pid;
    struct USB_device *next;
};

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
        printf("Failed to get ports!\n");
        return NULL;
    }

    int count = 0;
    for (int i = 0; port_list[i] != NULL; i++) {
        struct sp_port *port = port_list[i];
        enum sp_transport transport = sp_get_port_transport(port);
        if (transport == SP_TRANSPORT_USB) {
            char *port_name = sp_get_port_name(port);
            /* Display USB vendor and product IDs. */
		    int usb_vid, usb_pid;
		    sp_get_port_usb_vid_pid(port, &usb_vid, &usb_pid);
            struct USB_device *d = NULL;
            d = create_node(port_name, usb_vid, usb_pid);
            llist_add_end(list, d);
        }
    }
}

int main(int argc, char **argv)
{
    struct USB_device *list = NULL;
    get_usb_ports(&list);
    int i = 1;
    printf("Serial port info:\n");
    // change to while
    for (struct USB_device *temp = list; temp != NULL; temp = temp->next) {
        printf("{ %d\n", i);
        printf("  PORT: %s\n", temp->port_name);
        printf("   VID: %04X\n", temp->vid);
        printf("   PID: %04X\n", temp->pid);
        printf("}\n");
        i++;
    }
	return 0;
}