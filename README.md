# coqos-virtio-rtc-driver-linux

This is the out-of-tree variant of the `virtio_rtc` driver. The other
variant is the Linux kernel in-tree driver available since v6.16. The
out-of-tree driver is also compatible with older kernel versions.

Kernels older than v6.9 require multiple backports for cross
timestamping support.

If the older kernel has these backports, compile with

    CFLAGS_MODULE=-DVIRTIO_RTC_HAVE_CROSS_DEPS
