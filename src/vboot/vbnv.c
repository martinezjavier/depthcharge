/*
 * Copyright 2015 Google Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <libpayload.h>
#include <vboot_api.h>
#include <vboot_nvstorage.h>

#include "vboot/vbnv.h"

uint32_t vbnv_read(uint32_t flag)
{
	uint32_t val;
	VbNvContext context;

	VbExNvStorageRead(context.raw);
	VbNvSetup(&context);

	VbNvGet(&context, flag, &val);

	VbNvTeardown(&context);
	if (context.raw_changed)
		VbExNvStorageWrite(context.raw);

	return val;
}

void vbnv_write(uint32_t flag, uint32_t val)
{
	VbNvContext context;

	VbExNvStorageRead(context.raw);
	VbNvSetup(&context);

	VbNvSet(&context, flag, val);

	VbNvTeardown(&context);
	if (context.raw_changed)
		VbExNvStorageWrite(context.raw);
}


