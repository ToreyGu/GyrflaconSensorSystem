/*!
 *****************************************************************************
  @file:  adi_console_menu.c

  @brief: A simple console menu manager handler

  @details: A way to define using arrays of structs a set of menus that can
  	  	  	be displayed to a user, easily, with all user interaction handled
  	  	  	by the library, leaving only the implementation of the menu actions
  	  	  	to be done by the library user.
 -----------------------------------------------------------------------------
Copyright (c) 2019 Analog Devices, Inc.  All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
	and/or other materials provided with the distribution.
  - Modified versions of the software must be conspicuously marked as such.
  - This software is licensed solely and exclusively for use with processors/
    products manufactured by or for Analog Devices, Inc.
  - This software may not be combined or merged with other code in any manner
    that would cause the software to become subject to terms and conditions
	which differ from those listed here.
  - Neither the name of Analog Devices, Inc. nor the names of its contributors
    may be used to endorse or promote products derived from this software without
    specific prior written permission.
  - The use of this software may or may not infringe the patent rights of one
    or more patent holders.  This license does not release you from the
	requirement that you obtain separate licenses from these patent holders
	to use this software.

THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES, INC. AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-
INFRINGEMENT, TITLE, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ANALOG DEVICES, INC. OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, PUNITIVE OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, DAMAGES ARISING OUT OF
CLAIMS OF INTELLECTUAL PROPERTY RIGHTS INFRINGEMENT; PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

20180927-7CBSD SLA

*****************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "adi_console_menu.h"


/*!
 * @brief      displays the text of a console menu
 *
 * @details
 */
static void adi_display_console_menu(const console_menu * menu)
{
	adi_clear_console();

	/*
	 * Display the menu title and  menuItems
	 * The shortcutKey is used to display '[A]' before the dispayText
	 */
	printf("\r\n\r\n\t%s\r\n\t", menu->title);
	// show an underline to distinguish title from item
	for (uint8_t i = 0; i < strlen(menu->title); i++)
	{
		putchar('=');
	}
	// Extend underline past end of string, and then new line
	printf("==\r\n");

	// NOTE No check is made if the shortcutKey is valid or unique
	for (uint8_t i = 0; i < menu->itemCount; i ++)
	{
		if (menu->items[i].shortcutKey == '\00')
			{
				// No shortcut key defined, insert a blank line
				printf("\r\n");
			} else {
				printf("\t[%c] %s\r\n", toupper(menu->items[i].shortcutKey),
									  menu->items[i].displayText);
			}
	}
	if (menu->enableEscapeKey)
	{
	    printf("\r\n\t[ESC] Exit Menu\r\n");
	}

	printf("\r\n\tPlease make a selection.\r\n");

}


/*!
 * @brief      Display a consoleMenu and handle User interaction
 *
 * @details    This displays the menuItems defined by the console menu, and
 * 			    handles all user interaction for the menu.
 */
int32_t adi_do_console_menu(const console_menu * menu)
{
    int32_t itemSelected = MENU_ESCAPED;
	bool enableKeyScan = true;

    adi_display_console_menu(menu);

	/*
	 *  Loop waiting for valid user input. menuItem index is returned if
	 *  user presses a valid menu option.
	 */
	do {
		char keyPressed = toupper(getchar());

		if (menu->enableEscapeKey)
		{
			if (keyPressed == ESCAPE_KEY_CODE)
			{
				itemSelected = MENU_ESCAPED;
				enableKeyScan = false;
				break;
		    }
		}

		for (uint8_t i = 0; i < menu->itemCount; i ++)
		{
			if (toupper(menu->items[i].shortcutKey) == keyPressed)
			{
				itemSelected = i;

				// If the menuAction function pointer is not NULL, call the action
				if (menu->items[i].menuAction != NULL)
				{
					switch (menu->items[i].menuAction())
					{
						case MENU_DONE:
						{
							enableKeyScan = false;
							break;
						}
						case MENU_CONTINUE:
						default:
						{
							enableKeyScan = true;
							adi_display_console_menu(menu);
							break;
						}
					}
				}
				break;
			}
		}
    } while (enableKeyScan);

	return (itemSelected);
}


/*!
 * @brief      Clears the console terminal
 *
 * @details    Clears the console terminal using VT100 escape code, or can be changed to
 *             output blank lines if serial link doesn't support VT100.
 */
void adi_clear_console(void)
{
	/*
	 * clear console and move cursor to home location, followed by move to home location.
	 *  Dedicated call to move home is because sometimes first move home doesn't work
	 *  \r\n required to flush the uart buffer.
	 */
	printf("\x1B[2J\x1B[H\r\n");

	/*
	 * if Vt100 is not supported, this can be enabled instead
	 */
//    for (uint8_t = 0; i < 100; i++)
//    	printf("\r\n\r");
}



/*!
 * @brief      waits for any key to be pressed, and displays a prompt to the user
 *
 * @details
 */
void adi_press_any_key_to_continue(void)
{
    printf("\r\nPress any key to continue...\r\n");
	getchar();
}
