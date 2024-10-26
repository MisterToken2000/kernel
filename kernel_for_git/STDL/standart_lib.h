#ifndef STANDART_LIB_H 
#define STANDART_LIB_H

/*
* Welcome to the STDL!
* STDL(STanDart_Lib_h) writed with C programming language by Maxim Bugaev
*/


#include <stddef.h>

/* Defines */
#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES
#define MAX_LINE 256
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define CAPS_LOCK 0x3A
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E
#define TAB_KEY_CODE 0x09
#define ALT_KEY_CODE 0x38

/* prototypes */
void scroll_screen();
void kprint_newline(); 

/* current cursor location */
unsigned int current_loc = 0;
/* video memory begins at address 0xb8000 */
char *vidptr = (char*)0xb8000;

void print_string(const char *str, unsigned int row, unsigned int col) {
    char *vidptr = (char*)0xb8000; // video mem
    unsigned int i = 0;

    // start pos
    unsigned int pos = (row * 80 + col) * 2;

    // print string
    while (str[i] != '\0') {
        vidptr[pos] = str[i];       // Symbol
        vidptr[pos + 1] = 0x07;     // Text color
        i++;
        pos += 2;
    }
}

/* for NOP */
void delay(int seconds) {
    long long ticks = seconds * 10000000; // Примерное количество тактов для задержки
    while (ticks > 0) {
        asm volatile("nop"); // Пустая операция, чтобы занять процессор (No OPeration)
        ticks--;
    }
}

/* Kernel Print (kprint) */
void kprint(const char *str)
{
        unsigned int i = 0;
        while (str[i] != '\0') {
                vidptr[current_loc++] = str[i++];
                vidptr[current_loc++] = 0x07; /* color: white text, black background */
                if (current_loc >= SCREENSIZE) {
                    scroll_screen();
                }
        }
}

void rprint(const char *str)
{
    unsigned int i = 0;
    while (str[i] != '\0') {
        vidptr[current_loc++] = str[i++];
        vidptr[current_loc++] = 0x04; /* color: red text, black background */
        if (current_loc >= SCREENSIZE) {
            scroll_screen();
        }
    }
}

void bprint(const char *str)
{
    unsigned int i = 0;
    while (str[i] != '\0') {
    	vidptr[current_loc++] = str[i++];
	vidptr[current_loc++] = 0x01; /* color: blue text, black background */
	if (current_loc >= SCREENSIZE) {
		scroll_screen();
	}
    }
}

void white_text_blue_background(const char *str)
{
	unsigned int i = 0;
	while (str[i] != '\0'){
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = 0x07; /* color: white text, balck background */
		if (current_loc >= SCREENSIZE) {
			scroll_screen();
		}
	}
}

void blue(); /* prototype (pointer) */

/*
* OH NOOOOOOOOOOOOOOOOO!
*/

void madness(void){
	const char *errs[] = {
		"ERROR::kernel panic",
		"Errs::code::0x5D0-0xE4-ox34",
		"Kernel::panic::code::0x5D0-0xE4-0x34",
		"stop::code::0x05D0-0xE4-0x34",
		"fatal::error::code::0xD5D0-0xE4-0x34",
	};

		delay(2);
		white_text_blue_background(errs[0]);
		kprint_newline();
		white_text_blue_background(errs[1]);
		kprint_newline();
		delay(1);
		white_text_blue_background(errs[2]);
		kprint_newline();
		white_text_blue_background(errs[3]);
		kprint_newline();
		white_text_blue_background(errs[4]);
		kprint_newline();
		delay(2);
		for (int i = 0; i < 2; i++) {
			white_text_blue_background("hlt kernel");
			kprint_newline();
			kprint("hlt::kernel::code::0x5D0-0xE4-0x34");
			kprint_newline();
			white_text_blue_background("Kernel::stop::code::0x5D0-0xE4-0x34");
			kprint_newline();
			white_text_blue_background(errs[2]);
			kprint_newline();
		}
}

void blue(void){
	unsigned int i = 0;
        while (i < SCREENSIZE) {
                vidptr[i++] = ' ';
                vidptr[i++] = 0x7F; /* color: grey background */
        }
        
	current_loc = 0;
}

/*
* BRUH, HUH! this is a grey_screen 
*/

void blue_screen(void)
{
	blue();
	kprint("the system is trying to cope with the error");
	kprint_newline();
	delay(1);
	kprint("fatal kernel error");
	kprint_newline();
	kprint("ERR: kernel panic");
	kprint_newline();
	delay(5);
	kprint("the kernel is trying to cope with error and panic");
	delay(5);
	madness();
	delay(15);
	kprint_newline();
	kprint("cli");
	delay(3);
	blue();
	delay(2);
	madness();
	delay(4);
	white_text_blue_background("the system is trying to cope with the error");
        kprint_newline();
        delay(1);
        white_text_blue_background("fatal kernel error");
        kprint_newline();
        white_text_blue_background("ERR: kernel panic");
        kprint_newline();
      	delay(2);
        white_text_blue_background("the kernel is trying to cope with error and panic");
        delay(2);
        madness();
        delay(15);
        kprint_newline();
        delay(3);
	blue();
	asm volatile("cli");
	kprint("");
	kprint_newline();
	white_text_blue_background("*** KERNEL PANIC ***");
kprint_newline();
white_text_blue_background("An unexpected error has occurred, and the system has been halted to prevent damage.");
kprint_newline();
white_text_blue_background("");
kprint_newline();
white_text_blue_background("Error Code: 0x5D0-0xE4-0x34");
kprint_newline();
white_text_blue_background("Description: Critical system failure");
kprint_newline();
white_text_blue_background("");
kprint_newline();
white_text_blue_background("Possible Causes:");
kprint_newline();
kprint("");
kprint_newline();
white_text_blue_background(" - Fatal error");
kprint_newline();
white_text_blue_background("");
kprint_newline();
white_text_blue_background("Please restart your computer");
kprint_newline();
white_text_blue_background("");
kprint_newline();
white_text_blue_background("System halted.");
kprint_newline();
kprint("");
	kprint_newline();
	kprint("hlt keyboard driver");
	kprint_newline();
	kprint("");
	kprint_newline();
	while (1) { asm volatile("hlt"); } /* Stop all processes */
}

/* panic method */

/*
* !!! PANIC METHOD !!!
* BRUH?
* HUH!
* <<< PANIC METHOD >>>
* YEEEES?
* FURTHER ASSISTANCE??
*/

void panic(const char *error_code) {
	blue();
	        white_text_blue_background("*** KERNEL PANIC ***");
kprint_newline();
white_text_blue_background("An unexpected error has occurred, and the system has been halted to prevent damage.");
kprint_newline();
white_text_blue_background("");
kprint_newline();
white_text_blue_background("Error code: ");
white_text_blue_background(error_code);
kprint_newline();
white_text_blue_background("Description: Critical system failure");
kprint_newline();
white_text_blue_background("");
kprint_newline();
white_text_blue_background("Possible Causes:");
kprint_newline();
kprint("");
kprint_newline();
white_text_blue_background(" - Fatal error");
kprint_newline();
white_text_blue_background("");
kprint_newline();
white_text_blue_background("Please restart your computer");
kprint_newline();
white_text_blue_background("");
kprint_newline();
white_text_blue_background("System halted.");
kprint_newline();
kprint("");
        kprint_newline();
	kprint("hlt keyboard driver");
        kprint_newline();
	kprint("hlt keyboard_handler_main");
	kprint_newline();
	kprint("hlt check_command");
	kprint_newline();
	kprint("hlt read_port, write_port");
	kprint_newline();
	kprint("");
	kprint_newline();
        while (1) {asm volatile("hlt");} // Huh
}

void fprint(const char *str)
{
    unsigned int i = 0;
    while (str[i] != '\0') {
	vidptr[current_loc++] = str[i++];
	vidptr[current_loc++] = 0xF0;
    	if (current_loc >= SCREENSIZE) {
		scroll_screen();
	}
    }
}

void wprint(const char *str)
{
    unsigned int i = 0;
    while (str[i] != '\0') {
    	vidptr[current_loc++] = str[i++];
	vidptr[current_loc++] = 0x70;
	if (current_loc >= SCREENSIZE) {
		scroll_screen();
	}
    }
}

/*
* method blue_background_print() for blue_screen -_-
*/

void blue_background_print(const char *str){
    unsigned int i = 0;
    while (str[i] != '\0') {
    	vidptr[current_loc++] = str[i++];
	vidptr[current_loc++] = 0x10; /* color: white text, blue background */
	if (current_loc >= SCREENSIZE) {
		scroll_screen();
	}
    }
}

void red_background_print(const char *str)
{
    unsigned int i = 0;
    while (str[i] != '\0') {
    	vidptr[current_loc++] = str[i++];
	vidptr[current_loc++] = 0x40; /* color: red text 100% */
	if (current_loc >= SCREENSIZE) {
		scroll_screen();
	}
    }
}

/* For new lines */
void kprint_newline(void)
{
        unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
        current_loc = current_loc + (line_size - current_loc % (line_size));
        if (current_loc >= SCREENSIZE) {
            scroll_screen();
        }
}


void clear_screen(void)
{
        unsigned int i = 0;
        while (i < SCREENSIZE) {
                vidptr[i++] = ' ';
                vidptr[i++] = 0x07; /* color: black background 100% */
        }
        current_loc = 0;
}

void remove_first_n_chars(char *str, int n)
{
	int i = 0;
	while (str[i + n] != '\0') {
		str[i] = str[i + n];
		i++;
	}
	str[i] = '\0';
}
/* VERY SUPER METHOD */
int starts_with(const char *str, const char *prefix)
{
	while (*prefix) {
		if (*prefix++ != *str++) {
			return 1;
		}
	}
	return 0;
}


/*
* BRUH
*/
void copy_string(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0'; // Не забываем про нулевой терминатор
}

/*
* yEEEEE
*/
void scroll_screen(void)
{
        unsigned int i = 0;
        for (i = 0; i < (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i++) {
                vidptr[i] = vidptr[i + COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT];
        }
        for (i = (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i < LINES * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i += 2) {
                vidptr[i] = ' ';
         	vidptr[i + 1] = 0x07;
			/*
			* 0x07 == WHITE TEXT, BLUE... OH NO! BLACK BACKGROUND
			*/
	}
        current_loc = (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT;
}

/*
* BRO! NO!
*/
void scroll_blue(void) {
	unsigned int i = 0;
	for (i = 0; i < (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i++) {
		vidptr[i] = vidptr[i + COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT];
	}
	for (i = (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i < LINES * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i += 2) {
		vidptr[i] = ' ';
		vidptr[i + 1] = 0x7F;
	}
}

/* WHAT A FU.. FOX THEY? */
void what(void) {
	unsigned int i = 0;
        for (i = 0; i < (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i++) {
                vidptr[i] = vidptr[i + COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT];
        }
        for (i = (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i < LINES * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i += 2) {
                vidptr[i] = ' ';
                vidptr[i + 1] = 0x1F;
        }
        current_loc = (LINES - 1) * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT;	
}
/* WHAT? THIS IS A HEBREW 
* שלום!
*/
int my_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

/* love */
void pushinkafetch(char name[100]) {
kprint_newline();
kprint("##**##############**############%%===++=");
kprint_newline();
kprint("*###################*+***+++++*+**++++++");
kprint_newline();
kprint("****##%#*#****++***++++===+===++=++++===");
kprint_newline();
kprint("%#***#%#*+==++====+++====+++===-====----");
kprint_newline();
kprint("%@#****+===++====+++==+++==+===---------");
kprint_newline();
kprint("+*=--======+*====+*==+==++=======----=*+");
kprint_newline();
kprint("++=--======+*+=*+=*+=*=-=++=--====----=+");
kprint_newline();
kprint("*%*=======-=++==*+*#+*+=-===-======+=--=");
kprint_newline();
kprint("@@#=====++=+++==+**%#**===+***###*+=====");
kprint_newline();
kprint("@#=-=*########*****###***#%%@@@@%%##*=--");
kprint("    ");
rprint("Name");
kprint(": ");
kprint(name);
kprint_newline();
kprint("%+==##%%%@@@@@%%##****###%@@@@@@%%%##*=-");
kprint("    ");
rprint("OS"); 
kprint(": PushinkaOS KNU/Kernel 1.0.7");
kprint_newline();
kprint("#*+*###%%%@@@@@@%#*##**##@@@@@%%%%####++");
kprint("    ");
rprint("Kernel");
kprint(": 1.0.7-KNU/Kernel");
kprint_newline();
kprint("*++*#####%%%@@%@@#*****#%%%%%%%%%%%%%*-=");
kprint("    ");
rprint("Shell");
kprint(": pushinka shell");
kprint_newline();
kprint("+==+#%%%%%%%%%%%%#**+++#%%%%%%%%%%%%*===");
kprint_newline();
kprint("++++*#%%%%%%%%%%****+++**##%%%%%%%#+=++=");
kprint_newline();
kprint("*+++***##%%%%##+==*#****+==+*****++++===");
kprint_newline();
kprint("###*+++++++++=======*##=================");
kprint_newline();
kprint("####**++++++++=======**+===============+");
kprint_newline();
kprint("####*++++++=++++=====++=================");
kprint_newline();
kprint("#####++++===========-===----------------");
kprint_newline();
kprint("#####*+++++===--------------------------");
kprint_newline();
kprint("##*##**++============-------------------");
kprint_newline();
kprint("###*##*++======+++=++========----==-----");
kprint_newline();
kprint("#*#****+++==========++===++*+==---------");
kprint_newline();
kprint("**+****+++============---==++++==------=");
kprint_newline();
kprint("****#*+*++=====================+++==-=++");
kprint_newline();
kprint("*##****+*+===============+=====--==----=");
kprint_newline();
kprint("###**+**+++=====================--------");
kprint_newline();
kprint("*****+++++=======================-----==");
kprint_newline();
}

void lock_session(void) {
    blue();
    kprint_newline();
    kprint("");
kprint_newline();
kprint("SESSION LOCKED");
kprint_newline();
kprint("");
kprint_newline();
kprint("This session has been locked.");
kprint_newline();
kprint("");
kprint_newline();
kprint("Further assistance?");
kprint_newline();
    while (1) {
        asm volatile ("cli");
        asm volatile ("hlt");
    }
}

size_t my_strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

#endif