ifeq ($(ENABLE_VENDOR_CUTTLEFISH), true)
# Build virtio-rtc kernel driver

PRODUCT_PACKAGES += virtio_rtc.ko
endif # ENABLE_VENDOR_CUTTLEFISH
