#ifndef MYSYSCALL_H
#define MYSYSCALL_H

#include <linux/syscalls.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/rcupdate.h>
#include <linux/fdtable.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/dcache.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/time.h>


asmlinkage long sys_newsem_init(struct newsem* instance, int n);
asmlinkage long sys_newsem_wait(struct newsem* instance);
asmlinkage long sys_newsem_signal(struct newsem* instance);

#endif
