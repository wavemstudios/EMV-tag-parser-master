CC=gcc -g -DDEBUG

all:executable

debug: CC = gcc -g -DDEBUG
debug: executable

arm_build: CC = arm-linux-gcc
arm_build: executable

executable: main.c
	$(CC) main.c tlv.c hashtable.c emvTagList.c -o tlv-tag-parser
	
.PHONY: clean
clean:
	rm tlv-tag-parser