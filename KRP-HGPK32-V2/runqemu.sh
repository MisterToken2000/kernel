gcc -m32 -c main.c -o main.o
# gcc -m32 -c STDL/debug.c -o debug.o
nasm -f elf32 boot.asm -o boot.o
ld -m elf_i386 -T link.ld -o kernel boot.o main.o # debug.o
qemu-system-x86_64 -kernel kernel
