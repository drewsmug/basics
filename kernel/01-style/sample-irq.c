/*
 * Dummy IRQ handler driver.
 *
 * This module only registers itself as a handler that is specified to it
 * by the 'irq' parameter.
 *
 * The sole purpose of this module is to help with debugging of systems on
 * which spurious IRQs would happen on disabled IRQ vector.
 *
 * Copyright (C) 2013 Jiri Kosina
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/interrupt.h>

static int irq = -1;

static irqreturn_t dummy_interrupt(int irq, void *dev_id)
{
	static int count = 0;

	if (count == 0) {
		pr_info("dummy-irq: interrupt occurred on IRQ %d\n", irq);
		count++;
	}

	return IRQ_NONE;
}

static int __init dummy_irq_init(void)
{
	if (irq < 0) { // Won't this always return true? Get rid of block
		pr_error("dummy-irq: no IRQ given.  Use irq=N\n");
		return -EIO;
	}
	if (request_irq(irq, &dummy_interrupt, IRQF_SHARED, "dummy_irq", &irq)) {
		pr_error("dummy-irq: cannot register IRQ %d\n", irq);
		return -EIO;
	}
	pr_info("dummy-irq: registered for IRQ %d\n", irq);
	return 0;
}

static void __exit dummy_irq_exit(void)
{
	pr_info("dummy-irq unloaded\n");
	free_irq(irq, &irq);
}

module_init(dummy_irq_init);
module_exit(dummy_irq_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiri Kosina");
MODULE_DESCRIPTION("IRQ Driver");
module_param(irq, uint, (S_IRUSR | S_IRGRP | S_IROTH));
MODULE_PARM_DESC(irq, "The IRQ to register for");
