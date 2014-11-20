/*
 * (C) Copyright 2011
 * IONICS-EMS Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/* IONICS Board Model: STRATUS
 * Description: The ff are the required settings during u-boot level.
 * 
 * =====================================================================
 *    MPP#      DEVICE         LABEL             STATUS        REMARKS
 * =====================================================================    
 *     40        LED      led1/power             enabled 
 *     44        LED      led2/wireless          enabled
 *     39        LED      led3/zwave/zigbee      enabled
 *     36        LED      led4/status            blink
 *     21        USB      port 1                 enabled 
 *     32        USB      port 2                 enabled
 *     48        WIFI     power down             disabled
 *     49        WIFI     host wake-up           disabled
 *     42        WIFI     MAC wake-up            disabled
 *
 */


#include <common.h>
#include <command.h>

#define GPIO_DATA_OUT_REGISTER 			0xf1010100
#define GPIO_DATA_OUT_EN_CTRL_REGISTER 		0xf1010104
#define GPIO_BLINK_EN_REGISTER 			0xf1010108
#define GPIO_HIGH_DATA_OUT_REGISTER 		0xf1010140
#define GPIO_HIGH_DATA_OUT_EN_CTRL_REGISTER 	0xf1010144
#define GPIO_HIGH_BLINK_EN_REGISTER 		0xf1010148


void mode_select ( int mode ) 
{

   	switch ( mode ) {

   	case 0:
         	*((ulong *) GPIO_HIGH_BLINK_EN_REGISTER) = 0x00000010;
         	break;
   	case 1:
         	*((ulong *) GPIO_HIGH_BLINK_EN_REGISTER) = 0x00000100;
         	break;
   	case 2:
         	*((ulong *) GPIO_HIGH_BLINK_EN_REGISTER) = 0x00000000;
         	*((ulong *) GPIO_HIGH_DATA_OUT_REGISTER) = 0xffffffff;
         	break;
   	}

}

void led_test ( int led_number ) 
{

        *((ulong *) GPIO_HIGH_BLINK_EN_REGISTER) = 0x00000000;

   	switch ( led_number ) {

        /* led 1 */
   	case 0:
                /* turn-on */
         	*((ulong *) GPIO_HIGH_DATA_OUT_REGISTER) = 0xfffffeff; 
         	break;
   	case 1:
                /* turn-off */
         	*((ulong *) GPIO_HIGH_DATA_OUT_REGISTER) = 0xffffffff;
         	break;
   	case 2:
                /* blink */
         	*((ulong *) GPIO_HIGH_BLINK_EN_REGISTER) = 0x00000100;
         	break;

        /* led 2 */
   	case 3:
                /* turn-on */
         	*((ulong *) GPIO_HIGH_DATA_OUT_REGISTER) = 0xffffefff; 
         	break;
   	case 4:
                /* turn-off */
         	*((ulong *) GPIO_HIGH_DATA_OUT_REGISTER) = 0xffffffff;
         	break;
   	case 5:
                /* blink */
         	*((ulong *) GPIO_HIGH_BLINK_EN_REGISTER) = 0x00001000;
         	break;

        /* led 3 */
   	case 6:
                /* turn-on */
         	*((ulong *) GPIO_HIGH_DATA_OUT_REGISTER) = 0xffffff7f; 
         	break;
   	case 7:
                /* turn-off */
         	*((ulong *) GPIO_HIGH_DATA_OUT_REGISTER) = 0xffffffff;
         	break;
   	case 8:
                /* blink */
         	*((ulong *) GPIO_HIGH_BLINK_EN_REGISTER) = 0x00000080;
         	break;

        /* led 4 */
   	case 9:
                /* turn-on */
         	*((ulong *) GPIO_HIGH_DATA_OUT_REGISTER) = 0xffffffef; 
         	break;
   	case 10:
                /* turn-off */
         	*((ulong *) GPIO_HIGH_DATA_OUT_REGISTER) = 0xffffffff;
         	break;
   	case 11:
                /* blink */
         	*((ulong *) GPIO_HIGH_BLINK_EN_REGISTER) = 0x00000010;
         	break;
   	}

}


int init_ionics ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

 	*((ulong *) GPIO_DATA_OUT_REGISTER) 			= 0xffdfffff; // MPP 0-31
   	*((ulong *) GPIO_DATA_OUT_EN_CTRL_REGISTER) 		= 0x00000000; // high Z state
   	*((ulong *) GPIO_BLINK_EN_REGISTER) 			= 0x00000000; // blink state
   	*((ulong *) GPIO_HIGH_DATA_OUT_REGISTER) 		= 0xffffee6e; // MPP 32-63
   	*((ulong *) GPIO_HIGH_DATA_OUT_EN_CTRL_REGISTER) 	= 0x00000000; // high Z state
   	*((ulong *) GPIO_HIGH_BLINK_EN_REGISTER) 		= 0x00000000; // blink state


	if (argc < 2)
		return cmd_usage(cmdtp);

        /* mode selection */
        if (strncmp(argv[1], "mode", 5) == 0) {
                       
                if (strncmp(argv[2], "bootup", 5) == 0)
                      mode_select(0);

               	else if (strncmp(argv[2], "flashing", 5) == 0)
                      mode_select(1);

               	else if (strncmp(argv[2], "shutdown", 5) == 0)
                      mode_select(2);
              
                else {
                      printf("\nbootup    -  predefined GPIO config for booting-up");
                      printf("\nflashing  -  predefined GPIO config for flashing\n\n");
                }
        }

        
        /* led test */
        else if (strncmp(argv[1], "led", 5) == 0) {
                       
                if (strncmp(argv[2], "1", 5) == 0) {

                       if (strncmp(argv[3], "on", 5) == 0)
                           led_test(0);

                       else if (strncmp(argv[3], "off", 5) == 0)
                           led_test(1);

                       else if (strncmp(argv[3], "blink", 5) == 0)
                           led_test(2);
                      
                       else
                           printf("\nled <number> on/off/blink\n\n");
                }

                else if (strncmp(argv[2], "2", 5) == 0) {

                       if (strncmp(argv[3], "on", 5) == 0)
                           led_test(3);

                       else if (strncmp(argv[3], "off", 5) == 0)
                           led_test(4);

                       else if (strncmp(argv[3], "blink", 5) == 0)
                           led_test(5);

                       else
                           printf("\nled <number> on/off/blink\n\n");
                }

                else if (strncmp(argv[2], "3", 5) == 0) {

                       if (strncmp(argv[3], "on", 5) == 0)
                           led_test(6);

                       else if (strncmp(argv[3], "off", 5) == 0)
                           led_test(7);

                       else if (strncmp(argv[3], "blink", 5) == 0)
                           led_test(8);

                       else
                           printf("\nled <number> on/off/blink\n\n");
                }

                else if (strncmp(argv[2], "4", 5) == 0) {

                       if (strncmp(argv[3], "on", 5) == 0)
                           led_test(9);

                       else if (strncmp(argv[3], "off", 5) == 0)
                           led_test(10);

                       else if (strncmp(argv[3], "blink", 5) == 0)
                           led_test(11);

                       else
                           printf("\nled <number> on/off/blink\n\n");
                }

                else
                      printf("\nled <number> on/off/blink\n\n");

        }


   	return(0);
}

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	init_ionics,	5,	1,	init_ionics,
	"Initialize IONICS board specific settings",
	"\nmode <name>          - Predefined configuration"
        "\nled  <number>        - LED Test\n\n"
);









