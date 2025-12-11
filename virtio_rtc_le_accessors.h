/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 *
 * This file has code copied from
 * https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/include/linux/virtio_config.h
 *
 * Backported from Linux kernel commits
 * e598960ff5e5 (virtio_config: LE config space accessors)
 * and
 * c84f91e26222 (virtio_config: fix up warnings on parisc)
 */

#ifndef _VIRTIO_RTC_LE_ACCESSORS_H_
#define _VIRTIO_RTC_LE_ACCESSORS_H_

/*
 * Nothing virtio-specific about these, but let's worry about generalizing
 * these later.
 */
#define virtio_le_to_cpu(x)                    \
	_Generic((x), __u8                     \
		 : (u8)(x), __le16             \
		 : (u16)le16_to_cpu(x), __le32 \
		 : (u32)le32_to_cpu(x), __le64 \
		 : (u64)le64_to_cpu(x))

#define virtio_cpu_to_le(x, m)            \
	_Generic((m), __u8                \
		 : (x), __le16            \
		 : cpu_to_le16(x), __le32 \
		 : cpu_to_le32(x), __le64 \
		 : cpu_to_le64(x))

/* LE (e.g. modern) Config space accessors. */
#define virtio_cread_le(vdev, structname, member, ptr)                       \
	do {                                                                 \
		typeof(((structname *)0)->member) virtio_cread_v;            \
                                                                             \
		might_sleep();                                               \
		/* Sanity check: must match the member's type */             \
		typecheck(typeof(virtio_le_to_cpu(virtio_cread_v)), *(ptr)); \
                                                                             \
		switch (sizeof(virtio_cread_v)) {                            \
		case 1:                                                      \
		case 2:                                                      \
		case 4:                                                      \
			vdev->config->get((vdev),                            \
					  offsetof(structname, member),      \
					  &virtio_cread_v,                   \
					  sizeof(virtio_cread_v));           \
			break;                                               \
		default:                                                     \
			__virtio_cread_many((vdev),                          \
					    offsetof(structname, member),    \
					    &virtio_cread_v, 1,              \
					    sizeof(virtio_cread_v));         \
			break;                                               \
		}                                                            \
		*(ptr) = virtio_le_to_cpu(virtio_cread_v);                   \
	} while (0)

#define virtio_cwrite_le(vdev, structname, member, ptr)                       \
	do {                                                                  \
		typeof(((structname *)0)->member) virtio_cwrite_v =           \
			virtio_cpu_to_le(*(ptr), ((structname *)0)->member);  \
                                                                              \
		might_sleep();                                                \
		/* Sanity check: must match the member's type */              \
		typecheck(typeof(virtio_le_to_cpu(virtio_cwrite_v)), *(ptr)); \
                                                                              \
		vdev->config->set((vdev), offsetof(structname, member),       \
				  &virtio_cwrite_v, sizeof(virtio_cwrite_v)); \
	} while (0)

#endif /* _VIRTIO_RTC_LE_ACCESSORS_H_ */
