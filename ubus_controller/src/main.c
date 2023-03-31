#include <stdio.h>
#include <stdlib.h>

#include "ubus_utils.h"

int main(int argc, char **argv)
{
    struct ubus_context *ctx;
    int ret = 1;
    if (start_ubus(ctx) == 0){
        ret = 0;
        ubus_free(ctx);
    }
	return ret;
}
