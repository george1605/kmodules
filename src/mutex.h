#include <linux/module.h>
#include <linux/fcntl.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

struct lock
{
  int locked;
  int cpu;
  void* res;
};

static struct lock* initlock()
{
  struct lock* u = kmalloc(sizeof(struct lock),GFP_USER);
  u->cpu = 0;
  u->lock = 0;
  return u;
}

static void acquire(struct lock* l)
{
  l->locked = 1;
}

static void release(struct lock* l)
{
  l->locked = 0; 
}

static void __init mutexinit()
{
  
}

static void __exit mutexclose()
{
  
}

module_init(mutexinit);
module_exit(mutexclose);
MODULE_LICENSE("GPL");
