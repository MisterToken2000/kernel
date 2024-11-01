#ifndef STDO_H
#define STDO_H
#define NEW kprint_newline()

#include "standart_lib.h"
/* print method */
void print(const char *str) /* (println) */
{
    unsigned int i = 0;
    while (str[i] != '\0')
    {
	    vidptr[current_loc++] = str[i++];
	    vidptr[current_loc++] = 0x07; // 0x07 -> color: white text, black background
    	if (current_loc >= SCREENSIZE)
        {
		    scroll_screen();
	    }
    }
    NEW; // new line
}

#endif