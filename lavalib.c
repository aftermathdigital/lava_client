#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdint.h>

#define printf(...) {}

int get_handle() {
    int lava_fd = -1;
    printf("[+] Opening handle to lava module\n");
    lava_fd = open("/dev/lava", O_RDWR);
    printf("[+] lava_fd = %i\n", lava_fd);
    return lava_fd;
}

void close_handle(int fd) {
    printf("[+] Closing lava_fd handle\n");
    close(fd);
}

long new_crucible(int fd, uint16_t id, uint8_t capacity, uint8_t valuer){
    uint32_t input =    ((uint32_t)id << 16) |
                        ((uint32_t)capacity << 8) |
                        valuer;

    printf("[+] Creating new crucible\n\tid: %x capacity: %x valuer: %x\n", id, capacity, valuer);
    long ret = ioctl(fd, 0xa4a4a4a4, input);
    printf("[+] new_crucible returned %ld\n", ret);
    return ret;
}

long add_pebble(int fd, uint16_t crucible_id, uint16_t pebble_id, uint16_t size, uint16_t lustre){
    uint64_t input =    ((uint64_t)crucible_id << 48) |
                        ((uint64_t)pebble_id << 32) |
                        ((uint64_t)size << 16) |
                        lustre;

    printf("[+] Adding pebble\n\tcrucible_id: %x pebble_id: %x size: %x lustre %x\n",
        crucible_id, pebble_id, size, lustre);
    long ret = ioctl(fd, 0xb6b6b6b6, input);
    printf("[+] add_pebble returned %ld\n", ret);
    return ret;
}

long remove_pebble(int fd, uint16_t crucible_id, uint16_t pebble_id){
    uint32_t input =    ((uint32_t)crucible_id << 16) |
                        pebble_id;
    printf("[+] Removing pebble\n\tcrucible_id: %x pebble_id: %x\n",
        crucible_id, pebble_id);
    long ret = ioctl(fd, 0xc1c1c1c1, input);
    printf("[+] remove_pebble returned %ld\n", ret);
    return ret;
}

long assess_value(int fd, uint16_t id){
    printf("[+] Assessing value\n\tid: %x\n", id);
    long ret = ioctl(fd, 0xd9d9d9d9, id);
    printf("[+] assess_value returned %ld\n", ret);
    return ret;
}

long incinerate(int fd, uint16_t id){
    printf("[+] Incinerating\n\tid: %x\n", id);
    long ret = ioctl(fd, 0xe7e7e7e7, id);
    printf("[+] incinerate returned %ld\n", ret);
    return ret;
}