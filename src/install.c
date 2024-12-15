#include "install.h"
#include <stdio.h>
#include <stdlib.h>

void install_package(const char *package) {
    char command[256];
    snprintf(command, sizeof(command), "sudo apt install -y %s", package);
    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Failed to install package: %s\n", package);
    }
}
