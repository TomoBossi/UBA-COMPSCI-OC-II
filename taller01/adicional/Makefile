sumador64:
	nasm -f elf64 -g -F DWARF sumador64.asm
	nasm -f elf64 -g -F DWARF print_uint64.asm
	ld -o sumador64 sumador64.o print_uint64.o
	./sumador64

sumador8:
	nasm -f elf64 -g -F DWARF sumador8.asm
	ld -o sumador8 sumador8.o
	./sumador8

clean:
	rm -f *.o
	rm -f sumador64
	rm -f sumador8

.PHONY: clean sumador64 sumador8
