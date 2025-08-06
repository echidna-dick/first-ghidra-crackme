#include <stdio.h>
#include <string.h>

int main() {
    char password[20];
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(password, "echidna") == 0) {
        printf("Access granted!\n");
    } else {
        printf("Access denied!\n");
    }

    return 0;
}
