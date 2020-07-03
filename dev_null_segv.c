#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/current.h>
#include <asm/uaccess.h>
#include <asm/siginfo.h>
#include <linux/kmod.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

#define DRIVER_NAME "DEV_NULL_SEGV"
#define DRIVER_MAJOR 62

struct task_struct *task = NULL;

static int open(struct inode *inode, struct file *file) {
  task = get_current();
  return 0;
}

static int release(struct inode *inode, struct file *file) {
  task = NULL;
  return 0;
}

static ssize_t dummy_read(struct file *file, char __user *buf, size_t count,
                          loff_t *f_pos) {
  if(task != NULL){
    struct kernel_siginfo sig_info;
    memset(&sig_info, 0, sizeof(struct kernel_siginfo));
    sig_info.si_signo = SIGSEGV;
    sig_info.si_code = SI_QUEUE;
    sig_info.si_int = 1;
    send_sig_info(SIGSEGV, &sig_info, task);
  }
  return 0;
}

static ssize_t write(struct file *file, const char __user *buf, size_t count,
                     loff_t *f_pos) {
  if(task != NULL){
    struct kernel_siginfo sig_info;
    memset(&sig_info, 0, sizeof(struct kernel_siginfo));
    sig_info.si_signo = SIGSEGV;
    sig_info.si_code = SI_QUEUE;
    sig_info.si_int = 1;
    send_sig_info(SIGSEGV, &sig_info, task);
  }
  return 0;
}

struct file_operations fops = {
    .open = open,
    .release = release,
    .read = dummy_read,
    .write = write,
};

static int dev_null_segv_init(void) {
  printk(KERN_INFO "Starting dev_null_segv\n");
  register_chrdev(DRIVER_MAJOR, DRIVER_NAME, &fops);
  return 0;
}

static void dev_null_segv_exit(void) {
  printk(KERN_INFO "Removing dev_null_segv\n");
  unregister_chrdev(DRIVER_MAJOR, DRIVER_NAME);
}

module_init(dev_null_segv_init);
module_exit(dev_null_segv_exit);
MODULE_LICENSE("MIT");
