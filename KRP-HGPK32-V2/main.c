#include "STDL/standart_lib.h" // STD
#include "KLIB/keyboard_map.h" // BLA BLA BLA, Keyboard LIBrary
#include "FS/filesystem"
#include "STDL/debug.h"
#include "STDL/stdo.h"
/*                ^
*                 |
*                 
*                 i
*/

/*
*                 ^
*                 |
*                 |
*
*       HAHAHEHHHAHAHAHAHAHA
*/

    //////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////
  //////Welcome To The 1.0.7-KNU/kernel/////////////////////////////////
 //////////////////////////////////////////////////////////////////////
/* #define MISTER maxim///////////////////////////////////////////////
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*///////////////////////////////////////////////////////////////////////////////

#define caley kprint("[@local_user] ");
#define rooted print("rooted?");
/* love externs */
extern void keyboard_handler(void); // <- real. in kernel.asm(boot)
extern char read_port(unsigned short port); // kernel.asm (boot)
extern void write_port(unsigned short port, unsigned char data); // OK?
extern void load_idt(unsigned long *idt_ptr);
extern void start(void);
void keyboard_handler_main();

/* buffer for storing input characters */
char input_buffer[1024]; /*
if (my_strlen(input_buffer) >= 512) {
        print("why?");
} else {
        print("GOOD!");
}
*/

unsigned int input_index = 0;

struct IDT_entry {
        unsigned short int offset_lowerbits;
        unsigned short int selector;
        unsigned char zero;
        unsigned char type_attr;
        unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void)
{
        unsigned long keyboard_address;
        unsigned long idt_address;
        unsigned long idt_ptr[2];

        /* populate IDT entry of keyboard's interrupt */
        keyboard_address = (unsigned long)keyboard_handler;
        IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
        IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
        IDT[0x21].zero = 0;
        IDT[0x21].type_attr = INTERRUPT_GATE;
        IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

        /*     Ports
        *        PIC1   PIC2
        *Command 0x20   0xA0
        *Data    0x21   0xA1
        */

        /* ICW1 - begin initialization */
        write_port(0x20 , 0x11);
        write_port(0xA0 , 0x11);

        /* ICW2 - remap offset address of IDT */
        /*
        * In x86 protected mode, we have to remap the PICs beyond 0x20 because
        * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
        */
        write_port(0x21 , 0x20);
        write_port(0xA1 , 0x28);

        /* ICW3 - setup cascading */
        write_port(0x21 , 0x00);
        write_port(0xA1 , 0x00);

        /* ICW4 - environment info */
        write_port(0x21 , 0x01);
        write_port(0xA1 , 0x01);
        /* Initialization finished */

        /* mask interrupts */
        write_port(0x21 , 0xff);
        write_port(0xA1 , 0xff);

        /* fill the IDT descriptor */
        idt_address = (unsigned long)IDT ;
        idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
        idt_ptr[1] = idt_address >> 16 ;

        load_idt(idt_ptr);
}

void kb_init(void)
{
        // 0xFD is 11111101 - enables only IRQ1 (keyboard)
        write_port(0x21 , 0xFD);
}



void check_command(const char *input, int su) {
    char name[100];
    char name_i[100] = "yes";
    if (my_strcmp(input, "help") == 0) /* if (my_strcmp(input, "52") == 0) 
    {
        print("SIGMA"); 
    } */
    {
        /* kprint_newline();
	kprint("");
	kprint_newline();
        kprint("Available commands:");
        kprint_newline();
        kprint("help - show this help message");
	kprint_newline();
	kprint("bits - show kernel bits");
        kprint_newline();
	kprint("cls - clear the screen");
	kprint_newline();
	kprint("info - detailed system information");
	kprint_newline();
	kprint("reset - simple reset");
	kprint_newline();
	kprint("--name <name> - change name");
	kprint_newline();
	kprint("print <text> - simple print text");
	kprint_newline();
        kprint("--user - whoami");
        kprint_newline(); */
        kprint_newline();
        print("available commands:");
        print("help - show this help message");
        print("bits - show kernel bits");
        print("cls, clear - clear screen");
        print("info - detailed system information");
        print("--name <name> - change name");
        print("print <text> - print text");
        print("--user -- whoami");
        print("reboot - reboot kernel");
    }
    else if (my_strcmp(input, "myt") == 0)
    {
        if (su == 0)
        {
                NEW;
                print("user");
        }
        else if (su == 1)
        {
                NEW;
                print("super user");
        }
    }
    else if (my_strcmp(input, "bits") == 0)
    {
    	kprint_newline();
	kprint("");
	kprint_newline();
	kprint("bits: 32");
	kprint_newline();
    }
    else if (my_strcmp(input, "reboot") == 0)
    {
        input_index = 0;
        start();
    }
    else if (my_strcmp(input, "cls") == 0)
    {
    	clear_screen();
    }
    else if (my_strcmp(input, "clear") == 0)
    {
        clear_screen();
    }
    else if (my_strcmp(input, "info") == 0) 
    {
kprint_newline();
kprint("");
kprint_newline();
kprint("Kernel Version: 1.1.2");
kprint_newline();
kprint("Architecture: 32-bit");
kprint_newline();
kprint("Supported Processors: x86_64");
kprint_newline();
kprint("Supported Devices: Intel and AMD network cards, NVIDIA and AMD GPUs, SATA and NVMe storage devices");
kprint_newline();
kprint_newline();
    }
    else if (my_strcmp(input, "") == 0){}
    else if (starts_with(input, "--name") == 0)
    {
	copy_string(name, input);
    	remove_first_n_chars(name, 6);
	kprint_newline();
	kprint("");
	if (starts_with(name, " ") == 0)
	{
			remove_first_n_chars(name, 1);
	}
	kprint(name);
	kprint_newline();

    }
    else if (my_strcmp(input, "--user") == 0)
    {
    	kprint_newline();
	kprint(name);
	kprint_newline();
    }
    /* else if (my_strcmp(input, "pes") == 0)
    {
        
        kprint_newline();
        kprint("nec 6ugew MauoHe3?");
        kprint_newline();
    } */
    else if (starts_with(input, "print") == 0)
    {
    	char text[1024];
	copy_string(text, input);
	remove_first_n_chars(text, 5);
	if (starts_with(text, " ") == 0)
	{
		remove_first_n_chars(text, 1);
	}
	kprint_newline();
	kprint(text);
	kprint_newline();
    }/*
    else if (my_strcmp(input, "greyscreen") == 0)
    {
	kprint_newline();
	kprint("ERR");
	kprint_newline();
	blue_screen();
    }
        else if (starts_with(input, "calc") == 0){
    	char code [100];
	copy_string(code ,input);
	remove_first_n_chars(code, 4);
	while (starts_with(code, " ") == 0)
	{
		remove_first_n_chars(code, 1);
	}
	

    }*/
    else if (my_strcmp(input, "panic") == 0)
    {
    	panic("0x7DD");
    }
    else if (my_strcmp(input, "pushinkafetch") == 0)
    {
        clear_screen();
        pushinkafetch(name);
    }
    else if (my_strcmp(input, "--locksess") == 0)
    {
        if (su == 1)
        {
                lock_session();
        }
        else if (su == 0)
        {
                NEW;
                rooted; // print("rooted?");
        }
    }
    else if (starts_with(input, "su") == 0)
    {
        remove_first_n_chars(input, 2);
        while (starts_with(input, " ") == 0)
        {
                remove_first_n_chars(input, 1);
        }
        check_command(input, 1);
    }
    else if (my_strcmp(input, "docmd") == 0)
    {
        if (su == 1)
        {
                NEW;
                print("sudocmd");
        }
        else
        {
                NEW;
                print("rooted?");
        }
    }
    else
    {
	kprint_newline();
	kprint("");
        kprint_newline();
	rprint("unknown command: ");
	rprint(input);
	kprint_newline();
    }
}

void keyboard_handler_main(void)
{
        unsigned char status;
        char keycode;
        /* write EOI */
        write_port(0x20, 0x20);
        status = read_port(KEYBOARD_STATUS_PORT);
        /* Lowest bit of status will be set if buffer is not empty */
        if (status & 0x01) {
                keycode = read_port(KEYBOARD_DATA_PORT);
                if (keycode < 0) return;

                // Получение символа из карты клавиатуры
                char ch = keyboard_map[(unsigned char)keycode];
                if (ch != 0)
                {
                        if (keycode == ENTER_KEY_CODE)
                        {
                                // Обработка нажатия Enter
                                input_buffer[input_index] = '\0'; // Завершение строки
                                check_command(input_buffer, 0); // Проверка команды
                                input_index = 0; // Сброс индекса
                                kprint_newline();
                                caley;
                        }
                        else if (keycode == BACKSPACE_KEY_CODE)
                        {
                                // Обработка нажатия Backspace
                                if (input_index > 0)
                                {
                                  	input_index--;
                                        current_loc -= 2;
                                        vidptr[current_loc] = ' ';
                                        vidptr[current_loc + 1] = 0x07;
                                }
                        }
                        else if (keycode == TAB_KEY_CODE)
                        {
                                for (int i = 0; i < 4; i++)
                                {
                                        char space = ' ';
                                        vidptr[current_loc++] = space; // Запись пробела в видеопамять
                                        input_buffer[input_index++] = space; // Запись пробела в буфер
                                        vidptr[current_loc++] = 0x07; // Установка атрибута цвета
                                }
                        }
                        else if (keycode == ALT_KEY_CODE)
                        {
                                input_index = 0;
                                start();
                        }
                        else
                        {
                                if (input_index > 256) {
                                        /*
                                        * I added this because when the index of characters in the buffer becomes greater than 512 or whatever (I don’t remember), the kernel freezes and a reboot is required
                                        * Further assistance?
                                        */
                                        kprint_newline();
                                        print("");
                                        print("buffer > 256 chars");
                                        print("");
                                        input_index = 0;
                                        caley;
                                }
                                // Запись символа в видеопамять
                                vidptr[current_loc++] = ch;
                                vidptr[current_loc++] = 0x07;
                                if (current_loc >= SCREENSIZE) {
                                    scroll_screen();
                                }

                                // Запись символа в буфер
                                input_buffer[input_index++] = ch;
                        }
                }
        }
}
        
void kmain(void)
{
        clear_screen();
        DEBUGNEWL("SDBUG: exec clear_screen(); from __#include \"STDL/standart_lib.h\"");
        // perform_post();
        DEBUGNEWL("INCLUDELIB_H: __#include \"STDL/debug.h\"");
        DEBUGNEWL("INCLUDELIB_H: __#include \"STDL/stdandart_lib.h\"");
        DEBUGNEWL("INCLUDELIB_H: __#include \"STDL/stdo.h\"");
        DEBUGNEWL("SYS32: KRP-HGPK32: boot");
        DEBUGNEWL("SYS32: KRP-HGPK32: init");
        DEBUGNEWL("BOOT32: boot: bootable!");
        DEBUGNEWL("IDT: idt: idt init...");
        DEBUGNEWL("SDBUG: exec idt_init(); in main.c");
        idt_init();
        DEBUGNEWL("KB: kb_init: kb init...");
        DEBUGNEWL("SDBUG: exec kb_init(); in main.c");
        // kprint_newline();
        kb_init();
	// fprint("                                 KNU kernel                                     ");
        // kprint_newline();
	// kprint("ru: BBeqiTe help, 4to6y nolu4uT cnicok kommanq");
	// kprint_newline();
        // print("");
	// kprint_newline();
        DEBUGNEWL("SDBUG: enter help to get list of commands");
        // kprint_newline();
	// kprint_newline();
        print("");
        caley;
        while (1);
}
