#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

int len, temp, a, b;

char *msg, operand;

int read_proc(struct file *filp, char *buf, size_t count, loff_t *offp)
{
	if (count>temp)	{
	  count = temp;
	}
	temp = temp - count;
	sprintf(msg, "%d\n", a);
	copy_to_user(buf, msg, count);
	if (count == 0) {
	  temp = len;
        }
	return count;
}


int write_a(struct file *filp, const char *buf, size_t count, loff_t *offp)
{
	copy_from_user(msg, buf, count);
	len = count;
	temp = len;
        long tmp;
	kstrtol(msg, 10, &tmp);
	a = tmp + 5;
	return count;
}


struct file_operations result_fops = {
  read: read_proc
};

struct file_operations a_fops = {
  write: write_a
};

/*struct file_operations b_fops = {
  read: read_proc
};

struct file_operations operand_fops = {
  read: read_proc
};*/

void create_new_proc_entry(void)
{
	proc_create("result", 0666, NULL, &result_fops);
	proc_create("a", 0666, NULL, &a_fops);
	msg = kmalloc(GFP_KERNEL, 100 * sizeof(char));
}


int proc_init(void) {
	create_new_proc_entry();
	return 0;
}

void proc_cleanup(void) {
	remove_proc_entry("hello", NULL);
}

MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);
