#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define LOG_FILE_PATH "/tmp/djfbksbfwf.txt"
#define SOURCE_LOG_PATH "/var/log/boot.log"

static int __init capture_logs_init(void) {
    struct file *src, *dest;
    char buffer[512];
    int i;

    dest = filp_open(LOG_FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    for (i = 0; i < 5; i++) {
        char log_path[64];
        snprintf(log_path, sizeof(log_path), "%s%s%d", SOURCE_LOG_PATH, i == 0 ? "" : ".", i);
        src = filp_open(log_path, O_RDONLY, 0);
        if (IS_ERR(src))
            continue;

        while (kernel_read(src, buffer, sizeof(buffer), &src->f_pos) > 0)
            kernel_write(dest, buffer, sizeof(buffer), &dest->f_pos);

        filp_close(src, NULL);
    }

    filp_close(dest, NULL);

    printk(KERN_INFO "[+] Boot logs captured to %s\n", LOG_FILE_PATH);
    return 0;
}

static void __exit capture_logs_exit(void) {
    printk(KERN_INFO "[+] Module unloaded\n");
}

module_init(capture_logs_init);
module_exit(capture_logs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("R4idB0y");
MODULE_DESCRIPTION("Capture logs of boot");
