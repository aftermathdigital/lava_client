#include <stdio.h>
#include <pthread.h>
#include "lavalib.h"

#define CRUCIBLE_ID 0

int lava_fd = -1;

void *thread_one_proc(void *_){
    printf("[+] Thread one running...\n");
    for(;;){
        add_pebble(
            lava_fd,
            CRUCIBLE_ID,
            0,
            1,
            1);
        assess_value(
            CRUCIBLE_ID,
            0
        );
        remove_pebble(
            lava_fd,
            CRUCIBLE_ID,
            0);
    }
    return NULL;
}

void *thread_two_proc(void *_){
    printf("[+] Thread two running...\n");
    for(;;){
        add_pebble(
            lava_fd,
            CRUCIBLE_ID,
            0,
            1,
            1);
        assess_value(
            CRUCIBLE_ID,
            0
        );
        remove_pebble(
            lava_fd,
            CRUCIBLE_ID,
            0);
    }
    return NULL;
}


int main(int argc, char *argv[]){
    long ret = -1;
    pthread_t tids[2] = {-1,-1}; 

    lava_fd = get_handle();

    //if(lava_fd < 0){
    //    printf("[!] Invalid lava_fd handle!\n");
    //    return -1;
    //}

    ret = new_crucible(
        lava_fd,
        CRUCIBLE_ID,
        0xff,
        0
    );

    ret = pthread_create(&(tids[0]), NULL, &thread_one_proc, NULL);
    ret = pthread_create(&(tids[1]), NULL, &thread_two_proc, NULL);

    pthread_join(tids[0], NULL);
    pthread_join(tids[0], NULL);

    close_handle(lava_fd);
    
    return 0;
}