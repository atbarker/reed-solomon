#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/time.h>
#include <linux/types.h>
#include "rs.h"

MODULE_LICENSE("MIT");
MODULE_AUTHOR("AUSTEN BARKER");

#define DATA_SIZE 223
#define PARITY_SIZE 32

static int __init km_template_init(void){
    uint8_t parity[PARITY_SIZE];
    uint8_t data[DATA_SIZE];
    //uint8_t data[16] = {0x40, 0xd2, 0x75, 0x47, 0x76, 0x17, 0x32, 0x06, 0x27, 0x26, 0x96, 0xc6, 0xc6, 0x96, 0x70, 0xec};
    uint8_t corrupted_data[DATA_SIZE];
    uint8_t output[DATA_SIZE + PARITY_SIZE];
    uint8_t errors[1] = {0};
    int i;
    struct timespec timespec1, timespec2;

    printk(KERN_INFO "Inserting kernel module\n");

    get_random_bytes(data, DATA_SIZE);
    //print_hex_dump(KERN_DEBUG, "encoding:", DUMP_PREFIX_OFFSET, 20, 1, (void*)data, DATA_SIZE, true);
    //print_hex_dump(KERN_DEBUG, "parity:", DUMP_PREFIX_OFFSET, 20, 1, (void*)parity, PARITY_SIZE, true);
    
    rs_init(PARITY_SIZE);

    memset(output, 0, DATA_SIZE + PARITY_SIZE);

    getnstimeofday(&timespec1);
    encode(data, DATA_SIZE, parity, PARITY_SIZE);
    getnstimeofday(&timespec2);
    printk(KERN_INFO "\n Encode took: %ld nanoseconds",
(timespec2.tv_sec - timespec1.tv_sec) * 1000000000 + (timespec2.tv_nsec - timespec1.tv_nsec));

    memcpy(corrupted_data, data, DATA_SIZE);
    corrupted_data[0] = 0;

    getnstimeofday(&timespec1);
    decode(corrupted_data, parity, DATA_SIZE, PARITY_SIZE, output, errors, 1);
    getnstimeofday(&timespec2);
    printk(KERN_INFO "\n Decode took: %ld nanoseconds",
(timespec2.tv_sec - timespec1.tv_sec) * 1000000000 + (timespec2.tv_nsec - timespec1.tv_nsec));

    print_hex_dump(KERN_DEBUG, "decoded:", DUMP_PREFIX_OFFSET, 20, 1, (void*)output, DATA_SIZE + PARITY_SIZE, true);

    for(i = 0; i < DATA_SIZE; i++){
        if(output[i] != data[i]){
            printk(KERN_INFO "Decode failed at character %d\n", i);
	    goto exit;
	}
    }
    printk(KERN_INFO "Decode completed successfully \n");
exit:
    return 0;
}

static void __exit km_template_exit(void){
    printk(KERN_INFO "Removing kernel module\n");
}

module_init(km_template_init);
module_exit(km_template_exit);
