/*
 * Copyright (c) 2008 Intel Corporation
 * Author: Matthew Wilcox <willy@linux.intel.com>
 *
 * Distributed under the terms of the GNU GPL, version 2
 *
 * Please see kernel/semaphore.c for documentation of these functions
 */
#ifndef __LINUX_SEMAPHORE_H
#define __LINUX_SEMAPHORE_H

#include <linux/list.h>
#include <linux/spinlock.h>

/* Please don't access any members of this structure directly */
struct semaphore {
	spinlock_t		lock;
	unsigned int		count;
	struct list_head	wait_list;
};

struct newsem {
	spinlock_t		lock;
	unsigned int	count;
	unsigned long long 		timestamp;			// The last time of taking Last one
	struct list_head 	running_list;
	struct list_head	wait_list;
};

#define __NEWSEMAPHORE_INITIALIZER(name, n, now_time)				\
{									\
	.lock		= __SPIN_LOCK_UNLOCKED((name).lock),		\
	.count		= n,						\
	.timestamp  = now_time,					\
	.wait_list	= LIST_HEAD_INIT((name).wait_list),		\
	.running_list	= LIST_HEAD_INIT((name).running_list),		\
}

static inline void newsema_init(struct newsem *sem, int val, unsigned long long now_time)
{
	static struct lock_class_key __key;
	*sem = (struct newsem) __NEWSEMAPHORE_INITIALIZER(*sem, val, now_time);
	lockdep_init_map(&sem->lock.dep_map, "newsem->lock", &__key, 0);
}

#define __SEMAPHORE_INITIALIZER(name, n)				\
{									\
	.lock		= __SPIN_LOCK_UNLOCKED((name).lock),		\
	.count		= n,						\
	.wait_list	= LIST_HEAD_INIT((name).wait_list),		\
}

#define DECLARE_MUTEX(name)	\
	struct semaphore name = __SEMAPHORE_INITIALIZER(name, 1)

static inline void sema_init(struct semaphore *sem, int val)
{
	static struct lock_class_key __key;
	*sem = (struct semaphore) __SEMAPHORE_INITIALIZER(*sem, val);
	lockdep_init_map(&sem->lock.dep_map, "semaphore->lock", &__key, 0);
}

#define init_MUTEX(sem)		sema_init(sem, 1)
#define init_MUTEX_LOCKED(sem)	sema_init(sem, 0)

extern void down(struct semaphore *sem);
extern int __must_check down_interruptible(struct semaphore *sem);
extern int __must_check down_killable(struct semaphore *sem);
extern int __must_check down_trylock(struct semaphore *sem);
extern int __must_check down_timeout(struct semaphore *sem, long jiffies);
extern void up(struct semaphore *sem);



extern void __down_common_new(struct newsem *sem);
extern void __up_new(struct newsem *sem);

#endif /* __LINUX_SEMAPHORE_H */
