// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Provides cross-timestamp params for Arm.
 *
 * Copyright (C) 2022-2023 OpenSynergy GmbH
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 */

#if 1
/*
 * For the out-of-tree driver, this file's content can only build if the
 * below header or the integrator defines VIRTIO_RTC_HAVE_CROSS_DEPS.
 */
#include "virtio_rtc_internal.h"
#endif

#ifdef VIRTIO_RTC_HAVE_CROSS_DEPS

#include <linux/clocksource_ids.h>

#include "include/uapi/linux/virtio_rtc.h"

#include "virtio_rtc_internal.h"

/* see header for doc */

int viortc_hw_xtstamp_params(u8 *hw_counter, enum clocksource_ids *cs_id)
{
	*hw_counter = VIRTIO_RTC_COUNTER_ARM_VCT;
	*cs_id = CSID_ARM_ARCH_COUNTER;

	return 0;
}

#endif /* VIRTIO_RTC_HAVE_CROSS_DEPS */
