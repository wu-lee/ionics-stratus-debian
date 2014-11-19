/*
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
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
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#ifndef _CONFIG_SHEEVAPLUG_H
#define _CONFIG_SHEEVAPLUG_H

/*
 * Version number information
 */
#define CONFIG_IDENT_STRING	"\nIONICS-PlugComputer STRATUS B0"

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131	1	/* CPU Core subversion */
#define CONFIG_KIRKWOOD		1	/* SOC Family Name */
#define CONFIG_KW88F6281	1	/* SOC Name */
#define CONFIG_MACH_SHEEVAPLUG		/* Machine type */
#define CONFIG_SKIP_LOWLEVEL_INIT	/* disable board lowlevel_init */

/*
 * Commands configuration
 */
#define CONFIG_SYS_NO_FLASH		/* Declare no flash (NOR/SPI) */
#include <config_cmd_default.h>
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ENV
#define CONFIG_CMD_MII
#define CONFIG_CMD_NAND
#define CONFIG_CMD_PING
#define CONFIG_CMD_USB
/*
 * mv-common.h should be defined after CMD configs since it used them
 * to enable certain macros
 */
#include "mv-common.h"

/*
 *  Environment variables configurations
 */
#ifdef CONFIG_CMD_NAND
#define CONFIG_ENV_IS_IN_NAND		1
#define CONFIG_ENV_SECT_SIZE		0x20000	/* 128k */
#else
#define CONFIG_ENV_IS_NOWHERE		1	/* if env in SDRAM */
#endif
/*
 * max 4k env size is enough, but in case of nand
 * it has to be rounded to sector size
 */
#define CONFIG_ENV_SIZE			0x20000	/* 128k */
#define CONFIG_ENV_ADDR			0x60000
#define CONFIG_ENV_OFFSET		0x60000	/* env starts here */

/*
 * Default environment variables
 */
#define CONFIG_BOOTCOMMAND		"run bootcmd"

#define CONFIG_MTDPARTS			"mtdparts=orion_nand:1m@0m(u-boot),4m@1m(kernel),5m@5m(pluginfo),-(rootfs)"

#define CONFIG_EXTRA_ENV_SETTINGS	"mtdids=nand0=orion_nand\0" \
	"mtdparts=mtdparts=orion_nand:1m@0m(u-boot),4m@1m(kernel),5m@5m(pluginfo),-(rootfs)\0" \
	"nand_kernel=nand read 0x800000 0x100000 0x400000\0" \
	"set_ubi_bootargs=setenv bootargs $(ubi_bootargs) $(mtdparts) root=ubi0:rootfs\0" \
	"ubi_bootargs=console=ttyS0,115200 rootfstype=ubifs ubi.mtd=3 ro noswap\0" \
	"ubi_initrd=ubi part pluginfo; ubifsmount pluginfo; ubifsload 0x1200000 initrd.usr\0" \
	"ubi_boot=init_ionics mode bootup ; run nand_kernel ; run set_ubi_bootargs ; bootm 0x800000\0" \
	"ubi_bootcmd=setenv bootcmd $(ubi_boot); saveenv\0" \
	"load_initrd_mfg=usb start; fatload usb 0 0x800000 uImage; fatload usb 0 0x1200000 initrd.mfg\0" \
	"load_initrd_usr=usb start; fatload usb 0 0x800000 uImage; run ubi_initrd\0" \
	"reflash_mfg=init_ionics mode flashing ; run load_initrd_mfg ; setenv bootargs console=ttyS0,115200 $(mtdparts); bootm 0x800000 0x1200000\0" \
	"reflash_usr=init_ionics mode flashing ; run load_initrd_usr ; setenv bootargs console=ttyS0,115200 $(mtdparts); bootm 0x800000 0x1200000\0" \
	"bootcmd=run ubi_bootcmd; run reflash_mfg\0" \
        "ethaddr=00:26:db:00:00:00\0" \
	"ionicsplug_part=xxxxxxxxxx\0" \
	"ionicsplug_serial=xxxxxxxxxx\0" \
	"ionicsplug_model=xxxxxxxxxx\0" \
	"ionicsplug_board=xxxxxxxxxx\0" \
	"ionicsplug_firmware=xxxxxxxxxx\0"

/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS	{1, 0}	/* enable port 0 only */
#define CONFIG_PHY_BASE_ADR	0
#endif /* CONFIG_CMD_NET */

/*
 * File system
 */
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_MTD_DEVICE               /* needed for mtdparts commands */
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_MTDPARTS
#define CONFIG_LZO

#endif /* _CONFIG_SHEEVAPLUG_H */
