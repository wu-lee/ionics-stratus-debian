obj-$(CONFIG_LIBERTAS_UAP) += uap8xxx.o

uap8xxx-y += uap_main.o uap_sdio_mmc.o
uap8xxx-$(CONFIG_PROC_FS) += uap_proc.o uap_debug.o

EXTRA_CFLAGS += -DFPNUM='"52"' -DPXA3XX_DMA_ALIGN -DDEBUG_LEVEL1
