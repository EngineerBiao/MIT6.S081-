CONFIG_AC97:=$(findstring y,$(CONFIG_AC97)y)
CONFIG_AHCI:=$(findstring y,$(CONFIG_AHCI)y)
CONFIG_AHCI_ICH9:=$(findstring y,$(CONFIG_AHCI_ICH9)y)
CONFIG_ATI_VGA:=$(findstring y,$(CONFIG_ATI_VGA)y)
CONFIG_BITBANG_I2C:=$(findstring y,$(CONFIG_BITBANG_I2C)y)
CONFIG_BOCHS_DISPLAY:=$(findstring y,$(CONFIG_BOCHS_DISPLAY)y)
CONFIG_CADENCE:=$(findstring y,$(CONFIG_CADENCE)y)
CONFIG_CAN_BUS:=$(findstring y,$(CONFIG_CAN_BUS)y)
CONFIG_CAN_PCI:=$(findstring y,$(CONFIG_CAN_PCI)y)
CONFIG_CAN_SJA1000:=$(findstring y,$(CONFIG_CAN_SJA1000)y)
CONFIG_DDC:=$(findstring y,$(CONFIG_DDC)y)
CONFIG_E1000E_PCI_EXPRESS:=$(findstring y,$(CONFIG_E1000E_PCI_EXPRESS)y)
CONFIG_E1000_PCI:=$(findstring y,$(CONFIG_E1000_PCI)y)
CONFIG_EDID:=$(findstring y,$(CONFIG_EDID)y)
CONFIG_EDU:=$(findstring y,$(CONFIG_EDU)y)
CONFIG_EEPRO100_PCI:=$(findstring y,$(CONFIG_EEPRO100_PCI)y)
CONFIG_ES1370:=$(findstring y,$(CONFIG_ES1370)y)
CONFIG_ESP:=$(findstring y,$(CONFIG_ESP)y)
CONFIG_ESP_PCI:=$(findstring y,$(CONFIG_ESP_PCI)y)
CONFIG_GENERIC_LOADER:=$(findstring y,$(CONFIG_GENERIC_LOADER)y)
CONFIG_GOLDFISH_RTC:=$(findstring y,$(CONFIG_GOLDFISH_RTC)y)
CONFIG_HART:=$(findstring y,$(CONFIG_HART)y)
CONFIG_HDA:=$(findstring y,$(CONFIG_HDA)y)
CONFIG_HTIF:=$(findstring y,$(CONFIG_HTIF)y)
CONFIG_I2C:=$(findstring y,$(CONFIG_I2C)y)
CONFIG_I82801B11:=$(findstring y,$(CONFIG_I82801B11)y)
CONFIG_IDE_CORE:=$(findstring y,$(CONFIG_IDE_CORE)y)
CONFIG_IDE_QDEV:=$(findstring y,$(CONFIG_IDE_QDEV)y)
CONFIG_IMX_USBPHY:=$(findstring y,$(CONFIG_IMX_USBPHY)y)
CONFIG_IOH3420:=$(findstring y,$(CONFIG_IOH3420)y)
CONFIG_IPACK:=$(findstring y,$(CONFIG_IPACK)y)
CONFIG_IVSHMEM_DEVICE:=$(findstring y,$(CONFIG_IVSHMEM_DEVICE)y)
CONFIG_LSI_SCSI_PCI:=$(findstring y,$(CONFIG_LSI_SCSI_PCI)y)
CONFIG_MEGASAS_SCSI_PCI:=$(findstring y,$(CONFIG_MEGASAS_SCSI_PCI)y)
CONFIG_MPTSAS_SCSI_PCI:=$(findstring y,$(CONFIG_MPTSAS_SCSI_PCI)y)
CONFIG_MSI_NONBROKEN:=$(findstring y,$(CONFIG_MSI_NONBROKEN)y)
CONFIG_NE2000_COMMON:=$(findstring y,$(CONFIG_NE2000_COMMON)y)
CONFIG_NE2000_PCI:=$(findstring y,$(CONFIG_NE2000_PCI)y)
CONFIG_NMC93XX_EEPROM:=$(findstring y,$(CONFIG_NMC93XX_EEPROM)y)
CONFIG_NVME_PCI:=$(findstring y,$(CONFIG_NVME_PCI)y)
CONFIG_PCI:=$(findstring y,$(CONFIG_PCI)y)
CONFIG_PCI_DEVICES:=$(findstring y,$(CONFIG_PCI_DEVICES)y)
CONFIG_PCIE_PORT:=$(findstring y,$(CONFIG_PCIE_PORT)y)
CONFIG_PCI_EXPRESS:=$(findstring y,$(CONFIG_PCI_EXPRESS)y)
CONFIG_PCI_EXPRESS_GENERIC_BRIDGE:=$(findstring y,$(CONFIG_PCI_EXPRESS_GENERIC_BRIDGE)y)
CONFIG_PCI_TESTDEV:=$(findstring y,$(CONFIG_PCI_TESTDEV)y)
CONFIG_PCNET_COMMON:=$(findstring y,$(CONFIG_PCNET_COMMON)y)
CONFIG_PCNET_PCI:=$(findstring y,$(CONFIG_PCNET_PCI)y)
CONFIG_PFLASH_CFI01:=$(findstring y,$(CONFIG_PFLASH_CFI01)y)
CONFIG_RISCV_VIRT:=$(findstring y,$(CONFIG_RISCV_VIRT)y)
CONFIG_ROCKER:=$(findstring y,$(CONFIG_ROCKER)y)
CONFIG_RTL8139_PCI:=$(findstring y,$(CONFIG_RTL8139_PCI)y)
CONFIG_SCSI:=$(findstring y,$(CONFIG_SCSI)y)
CONFIG_SD:=$(findstring y,$(CONFIG_SD)y)
CONFIG_SDHCI:=$(findstring y,$(CONFIG_SDHCI)y)
CONFIG_SDHCI_PCI:=$(findstring y,$(CONFIG_SDHCI_PCI)y)
CONFIG_SERIAL:=$(findstring y,$(CONFIG_SERIAL)y)
CONFIG_SERIAL_PCI:=$(findstring y,$(CONFIG_SERIAL_PCI)y)
CONFIG_SERIAL_PCI_MULTI:=$(findstring y,$(CONFIG_SERIAL_PCI_MULTI)y)
CONFIG_SIFIVE:=$(findstring y,$(CONFIG_SIFIVE)y)
CONFIG_SIFIVE_E:=$(findstring y,$(CONFIG_SIFIVE_E)y)
CONFIG_SIFIVE_U:=$(findstring y,$(CONFIG_SIFIVE_U)y)
CONFIG_SPIKE:=$(findstring y,$(CONFIG_SPIKE)y)
CONFIG_TEST_DEVICES:=$(findstring y,$(CONFIG_TEST_DEVICES)y)
CONFIG_TULIP:=$(findstring y,$(CONFIG_TULIP)y)
CONFIG_UNIMP:=$(findstring y,$(CONFIG_UNIMP)y)
CONFIG_USB:=$(findstring y,$(CONFIG_USB)y)
CONFIG_USB_AUDIO:=$(findstring y,$(CONFIG_USB_AUDIO)y)
CONFIG_USB_EHCI:=$(findstring y,$(CONFIG_USB_EHCI)y)
CONFIG_USB_EHCI_PCI:=$(findstring y,$(CONFIG_USB_EHCI_PCI)y)
CONFIG_USB_NETWORK:=$(findstring y,$(CONFIG_USB_NETWORK)y)
CONFIG_USB_OHCI:=$(findstring y,$(CONFIG_USB_OHCI)y)
CONFIG_USB_OHCI_PCI:=$(findstring y,$(CONFIG_USB_OHCI_PCI)y)
CONFIG_USB_SERIAL:=$(findstring y,$(CONFIG_USB_SERIAL)y)
CONFIG_USB_SMARTCARD:=$(findstring y,$(CONFIG_USB_SMARTCARD)y)
CONFIG_USB_STORAGE_BOT:=$(findstring y,$(CONFIG_USB_STORAGE_BOT)y)
CONFIG_USB_STORAGE_MTP:=$(findstring y,$(CONFIG_USB_STORAGE_MTP)y)
CONFIG_USB_STORAGE_UAS:=$(findstring y,$(CONFIG_USB_STORAGE_UAS)y)
CONFIG_USB_TABLET_WACOM:=$(findstring y,$(CONFIG_USB_TABLET_WACOM)y)
CONFIG_USB_UHCI:=$(findstring y,$(CONFIG_USB_UHCI)y)
CONFIG_USB_XHCI:=$(findstring y,$(CONFIG_USB_XHCI)y)
CONFIG_USB_XHCI_NEC:=$(findstring y,$(CONFIG_USB_XHCI_NEC)y)
CONFIG_VFIO:=$(findstring y,$(CONFIG_VFIO)y)
CONFIG_VFIO_PCI:=$(findstring y,$(CONFIG_VFIO_PCI)y)
CONFIG_VGA:=$(findstring y,$(CONFIG_VGA)y)
CONFIG_VGA_CIRRUS:=$(findstring y,$(CONFIG_VGA_CIRRUS)y)
CONFIG_VGA_PCI:=$(findstring y,$(CONFIG_VGA_PCI)y)
CONFIG_VHOST:=$(findstring y,$(CONFIG_VHOST)y)
CONFIG_VHOST_USER_BLK:=$(findstring y,$(CONFIG_VHOST_USER_BLK)y)
CONFIG_VHOST_USER_GPU:=$(findstring y,$(CONFIG_VHOST_USER_GPU)y)
CONFIG_VHOST_USER_INPUT:=$(findstring y,$(CONFIG_VHOST_USER_INPUT)y)
CONFIG_VHOST_USER_SCSI:=$(findstring y,$(CONFIG_VHOST_USER_SCSI)y)
CONFIG_VIRTIO:=$(findstring y,$(CONFIG_VIRTIO)y)
CONFIG_VIRTIO_BALLOON:=$(findstring y,$(CONFIG_VIRTIO_BALLOON)y)
CONFIG_VIRTIO_BLK:=$(findstring y,$(CONFIG_VIRTIO_BLK)y)
CONFIG_VIRTIO_CRYPTO:=$(findstring y,$(CONFIG_VIRTIO_CRYPTO)y)
CONFIG_VIRTIO_GPU:=$(findstring y,$(CONFIG_VIRTIO_GPU)y)
CONFIG_VIRTIO_INPUT:=$(findstring y,$(CONFIG_VIRTIO_INPUT)y)
CONFIG_VIRTIO_INPUT_HOST:=$(findstring y,$(CONFIG_VIRTIO_INPUT_HOST)y)
CONFIG_VIRTIO_IOMMU:=$(findstring y,$(CONFIG_VIRTIO_IOMMU)y)
CONFIG_VIRTIO_MMIO:=$(findstring y,$(CONFIG_VIRTIO_MMIO)y)
CONFIG_VIRTIO_NET:=$(findstring y,$(CONFIG_VIRTIO_NET)y)
CONFIG_VIRTIO_PCI:=$(findstring y,$(CONFIG_VIRTIO_PCI)y)
CONFIG_VIRTIO_RNG:=$(findstring y,$(CONFIG_VIRTIO_RNG)y)
CONFIG_VIRTIO_SCSI:=$(findstring y,$(CONFIG_VIRTIO_SCSI)y)
CONFIG_VIRTIO_SERIAL:=$(findstring y,$(CONFIG_VIRTIO_SERIAL)y)
CONFIG_VMWARE_VGA:=$(findstring y,$(CONFIG_VMWARE_VGA)y)
CONFIG_VMW_PVSCSI_SCSI_PCI:=$(findstring y,$(CONFIG_VMW_PVSCSI_SCSI_PCI)y)
CONFIG_VMXNET3_PCI:=$(findstring y,$(CONFIG_VMXNET3_PCI)y)
CONFIG_WDT_IB6300ESB:=$(findstring y,$(CONFIG_WDT_IB6300ESB)y)
CONFIG_XIO3130:=$(findstring y,$(CONFIG_XIO3130)y)
