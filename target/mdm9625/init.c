/*
 * Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <debug.h>
#include <board.h>
#include <platform.h>
#include <target.h>
#include <smem.h>
#include <baseband.h>
#include <lib/ptable.h>
#include <qpic_nand.h>

static struct ptable flash_ptable;

/* NANDc BAM pipe numbers */
#define DATA_CONSUMER_PIPE                            0
#define DATA_PRODUCER_PIPE                            1
#define CMD_PIPE                                      2

struct qpic_nand_init_config config;
/* init */
void target_init(void)
{
	dprintf(INFO, "target_init()\n");

	config.pipes.read_pipe = DATA_PRODUCER_PIPE;
	config.pipes.write_pipe = DATA_CONSUMER_PIPE;
	config.pipes.cmd_pipe = CMD_PIPE;

	config.bam_base = MSM_NAND_BAM_BASE;
	config.nand_base = MSM_NAND_BASE;

	qpic_nand_init(&config);

	/* Below lines are to be removed once the bootchain is available */

	ptable_init(&flash_ptable);

	flash_set_ptable(&flash_ptable);

	/* Add boot ptn..until the bootchain adds it */
	ptable_add(&flash_ptable, "boot", 0x347, 0x52, 0, TYPE_APPS_PARTITION, PERM_WRITEABLE);
}

/* reboot */
void reboot_device(unsigned reboot_reason)
{
	dprintf(CRITICAL, "Rebooting failed\n");
	return;
}

/* Check if we need to trigger fastboot */
int fastboot_trigger(void)
{
	return 0;
}

/* Create ATAGs for this target */
unsigned* target_atag_mem(unsigned* ptr)
{
	return ptr;
}

/* mach type */
unsigned board_machtype(void)
{
	//return board_target_id();
}

/* Identify the current target */
void target_detect(struct board_data *board)
{
}

/* Identify the baseband being used */
void target_baseband_detect(struct board_data *board)
{

}
