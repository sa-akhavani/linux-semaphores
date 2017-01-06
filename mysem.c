#include "mysem.h"

asmlinkage long sys_newsem_init(struct newsem* instance, int n)	// 340
{
	struct timespec ts;
	getnstimeofday(&ts);
	printk("noroozi :D\n%ld", ts.tv_nsec);
	newsema_init(instance, n, ts.tv_nsec);
	return 0;
}

asmlinkage long sys_newsem_wait(struct newsem* instance) 	// 341
{
	__down_common_new(instance);
	return 0;
}


asmlinkage long sys_newsem_signal(struct newsem* instance) // System call number is: 337
{
	__up_new(instance);
	return 0;
}
