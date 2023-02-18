#include <stdio.h>
#include "lavalib.h"

int main(int argc, char *argv[]){
    int lava_fd = -1;

    lava_fd = get_handle();
    
    if(lava_fd < 0){
        printf("[!] Invalid lava_fd handle!\n");
        return -1;
    }

    close_handle(lava_fd);
    
    return 0;
}