#ifndef DEBUG_H
#define DEBUG_H
#include "standart_lib.h"

void DEBUG(const char *str)
{
    kprint("__#DEBUG");
    unsigned int i = 0;
    while (str[i] != '\0')
    {
        vidptr[current_loc++] = str[i++];
        vidptr[current_loc++] = 0x07;
        if (current_loc >= SCREENSIZE)
        {
            scroll_screen();
        }
    }
}

void DEBUGNEWL(const char *str)
{
    kprint("__#DEBUG");
    unsigned int i = 0;
    while (str[i] != '\0')
    {
        vidptr[current_loc++] = str[i++];
        vidptr[current_loc++] = 0x07;
        if (current_loc >= SCREENSIZE)
        {
            scroll_screen();
        }
    }
    kprint_newline();
}

void DEBUGNEWLEXTR(const char *str)
{
    kprint("__#DEBUGEXTR");
    unsigned int i = 0;
    while (str[i] != '\0')
    {
        vidptr[current_loc++] = str[i++];
        vidptr[current_loc++] = 0x07;
        if (current_loc >= SCREENSIZE)
        {
            scroll_screen();
        }
    }
    kprint_newline();
}

void DEBUGEXTR(const char *str)
{
    kprint("__#DEBUGEXTR");
    unsigned int i = 0;
    while (str[i] != '\0')
    {
        vidptr[current_loc++] = str[i++];
        vidptr[current_loc++] = 0x07;
        if (current_loc >= SCREENSIZE)
        {
            scroll_screen();
        }
    }
}

#endif