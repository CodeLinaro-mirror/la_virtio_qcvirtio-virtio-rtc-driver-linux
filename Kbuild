#
# Kbuild for the virtio-rtc driver
#

# During development, to turn-off treating warning as error, pass
# `CFLAGS_MODULE=-Wno-error` to make as an argument or environment variable.
ccflags-y += -Werror

ccflags-$(CONFIG_PTP_1588_CLOCK) += -DCONFIG_VIRTIO_RTC_PTP=1
ifeq ($(CONFIG_PTP_1588_CLOCK),m)
ccflags-y += -DCONFIG_VIRTIO_RTC_PTP=1
endif
ccflags-$(CONFIG_RTC_CLASS) += -DCONFIG_VIRTIO_RTC_CLASS=1

virtio_rtc-y := virtio_rtc_driver.o
virtio_rtc-$(CONFIG_PTP_1588_CLOCK) += virtio_rtc_ptp.o
ifeq ($(CONFIG_ARM_ARCH_TIMER),y)
virtio_rtc-$(CONFIG_PTP_1588_CLOCK) += virtio_rtc_arm.o
endif
virtio_rtc-$(CONFIG_RTC_CLASS) += virtio_rtc_class.o

obj-m := virtio_rtc.o
