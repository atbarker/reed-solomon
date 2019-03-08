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

static int __init km_template_init(void){
    uint8_t parity[10];
    uint8_t data[16] = {0x40, 0xd2, 0x75, 0x47, 0x76, 0x17, 0x32, 0x06, 0x27, 0x26, 0x96, 0xc6, 0xc6, 0x96, 0x70, 0xec};
    uint8_t corrupted_data[16];
    uint8_t output[26];
    uint8_t errors[1] = {0};
    int i;

    printk(KERN_INFO "Inserting kernel module\n");

    //get_random_bytes(data, 223);
    print_hex_dump(KERN_DEBUG, "encoding:", DUMP_PREFIX_OFFSET, 20, 1, (void*)data, 16, true);
    print_hex_dump(KERN_DEBUG, "parity:", DUMP_PREFIX_OFFSET, 20, 1, (void*)parity, 10, true);
    
    rs_init(10);

    memset(output, 0, 26);

    encode(data, 16, parity, 10);

    memcpy(corrupted_data, data, 16);
    corrupted_data[0] = 0;

    decode(corrupted_data, parity, 16, 10, output, errors, 1);
    print_hex_dump(KERN_DEBUG, "decoded:", DUMP_PREFIX_OFFSET, 20, 1, (void*)corrupted_data, 16, true);

    for(i = 0; i < 16; i++){
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
