gcc -m32 -c main.c -o main.o
nasm -f elf32 boot.asm -o boot.o
ld -m elf_i386 -T link.ld -o kernel boot.o main.o
qemu-system-x86_64 -kernel kernel
