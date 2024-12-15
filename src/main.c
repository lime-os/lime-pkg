#include "search.h"
#include "menu.h"
#include "install.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3 || strcmp(argv[1], "install") != 0) {
        printf("Usage: pkg install <package-name>\n");
        return 1;
    }

    char **results;
    int result_count;
    search_package(argv[2], &results, &result_count);

    if (!results || result_count == 0) {
        printf("No packages found for '%s'.\n", argv[2]);
        return 1;
    }

    int choice = interactive_menu(results, result_count);
    printf("Selected package: %s\n", results[choice]);

    install_package(results[choice]);

    for (int i = 0; i < result_count; i++) {
        free(results[i]);
    }
    free(results);

    return 0;
}
