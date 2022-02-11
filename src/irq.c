#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

typedef irqreturn_t(*handler)(int, void*, struct pt_regs*);
static void* devid;

static void setirq(int x,handler u)
{
  request_irq(x,u,SA_INTERRUPT,"short",NULL);
}

static void freeirq(int x)
{
  free(x,devid);
}

static void __init startirq()
{
  
}

static void __exit stopirq()
{
  
}

module_init(startirq);
module_exit(stopirq);
