/*
 * This file is part of the libjaylink project.
 *
 * Copyright (C) 2021 Marc Schink <dev@zapb.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>

#include "libjaylink.h"
#include "libjaylink-internal.h"

/**
 * @file
 *
 * Renesas’ single-wire debug interface (FINE) functions.
 */

/** @cond PRIVATE */
#define CMD_FINE_IO 0xe0

/**
 * Perform a FINE I/O operation.
 *
 * @note This function must only be used if the #JAYLINK_TIF_FINE interface is
 *       available and selected.
 *
 * TODO: Parameter documentation
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR_IO Input/output error.
 * @retval JAYLINK_ERR_DEV_NO_MEMORY Not enough memory on the device to perform
 *                                   the operation.
 * @retval JAYLINK_ERR_DEV Unspecified device error.
 * @retval JAYLINK_ERR Other error conditions.
 *
 * @see jaylink_select_interface()
 * @see jaylink_set_speed()
 *
 * @since 0.2.0
 */
JAYLINK_API int jaylink_fine_io(struct jaylink_device_handle *devh,
		const uint8_t *out, uint8_t *in, uint32_t out_length,
		uint32_t in_length, uint32_t other_param)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[13];

	if (!devh || !out || !in)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;

	ret = transport_start_write_read(devh, 13 + out_length, 4 + in_length,
		true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %s",
			jaylink_strerror(ret));
		return ret;
	}

	buf[0] = CMD_FINE_IO;
	buffer_set_u32(buf, out_length, 1);
	buffer_set_u32(buf, in_length, 5);
	buffer_set_u32(buf, other_param, 9);

	ret = transport_write(devh, buf, 13);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %s",
			jaylink_strerror(ret));
		return ret;
	}

	ret = transport_write(devh, out, out_length);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %s",
			jaylink_strerror(ret));
		return ret;
	}

	ret = transport_read(devh, in, in_length);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %s",
			jaylink_strerror(ret));
		return ret;
	}

	ret = transport_read(devh, buf, 4);
	uint32_t status = buffer_get_u32(buf, 0);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %s",
			jaylink_strerror(ret));
		return ret;
	}

	/* TODO: Handle status. */
	(void)status;

	return JAYLINK_OK;
}
