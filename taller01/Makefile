COMPILER := nasm
FLAGS := -f elf64 -g -F DWARF

# make program_name
%:
	$(eval TARGET := $@)
	$(COMPILER) $(FLAGS) -o $(TARGET).o $(TARGET).asm
	ld -o $(TARGET) $(TARGET).o
	./$(TARGET)

# make clean TARGET=program_name
TARGET := program_name
clean: 
	rm -f *.o $(TARGET)
