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
    uint8_t parity[32];
    uint8_t data[223];
    uint8_t corrupted_data[223];
    uint8_t output[255];
    uint8_t errors[1] = {0};
    int i;

    printk(KERN_INFO "Inserting kernel module\n");

    get_random_bytes(data, 223);
    
    rs_init(32);

    encode(data, 223, parity, 32);

    memcpy(corrupted_data, data, 223);
    corrupted_data[0] = 0;

    decode(corrupted_data, parity, 223, 32, output, errors, 1);

    for(i = 0; i < 223; i++){
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
