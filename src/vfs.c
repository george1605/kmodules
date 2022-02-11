#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/slab.h>
#include <linux/fcntl.h>
#include <asm/io.h>

struct vfile {
  int ports[3];
  char* mem;
  char* path;
  unsigned mode;
};

static void vmemcpy(char* x,char* y,int bytes)
{
    int a;
    for(a = 0;a < bytes && x[a] != 0;a++)
	x[a] = y[a];
}

static void mwrite(struct vfile u,char* ptr,int size)
{
  if(u.mode != O_RDWR && !(u.mode & O_WRONLY)) return;
  if(u.mem == 0)
    outsl(u.ports[0],ptr,size);
  else
    vmemcpy(u.mem,ptr,size);
}

static char* mread(struct vfile u,int size)
{
  char* i = kmalloc(size,GFP_USER);
  if(u.mode != O_RDWR && !(u.mode & O_RDONLY)) return (char*)0;
  if(u.mem == 0)
    insl(u.ports[0],i,size);
  else
    vmemcpy(i,u.mem,size);
  return i;
}

static void* pgalloc(void)
{
  return kmalloc(4096,GFP_USER);
}

static void pgfree(void* u)
{
  if(u == 0) return;
  kfree(u);
}

static int __init hello_start(void)
{
 struct vfile x;
 x.ports[0] = 0x60;
 x.mode = O_RDWR;
 char* u = mread(x,5);
 printk(KERN_INFO "Reading I/O address 0x60: %s\n",u);
 kfree(u);
 return 0;
}

static void __exit hello_end(void)
{
 printk(KERN_INFO "Exiting module!\n");
}

module_init(hello_start);
module_exit(hello_end);
