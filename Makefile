# Replace the Project name
PROJECT = Blink

# Source code related information
SOURCE  = ./src/
INCLUDE = ./inc/
LINKER_SCRIPT = ./.msc/scatter.ld

# Part specific information
PART    ?= TM4C123GH6PM
TARGET  ?= TM4C123_RB1
CFLAGS  ?= -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -ffunction-sections -fdata-sections -std=c99 -g -Os -Wall 
LDFLAGS ?= --gc-sections

# Flags
LIBGCC  := ${shell arm-none-eabi-gcc ${CFLAGS} -print-libgcc-file-name}
LIBC    := ${shell arm-none-eabi-gcc ${CFLAGS} -print-file-name=libc.a}
LIBM    := ${shell arm-none-eabi-gcc ${CFLAGS} -print-file-name=libm.a}

.PHONY: all clean

all: $(PROJECT).axf

clean:
	@echo "Cleaning the Source code ..."
	@rm -rf ./*/*.d ./*/*.o *.axf
	@echo "Done! :) "

$(PROJECT).axf: $(patsubst %.c, %.o, $(wildcard $(SOURCE)*.c))
	@echo "Compiling the source ..."
	@arm-none-eabi-ld ${LDFLAGS} -T $(LINKER_SCRIPT) --entry ResetIntHandler -o $@ $^ ${LIBGCC} ${LIBC} ${LIBM}
	@echo "Doing some house keeping ..."
	@rm -rf ./*/*.d ./*/*.o
	@echo "Generated Output: ./$(PROJECT).axf"
	@echo "Done! :)"

-include $(wildcard *.d)

%.o: %.c
	@arm-none-eabi-gcc ${CFLAGS} -I$(INCLUDE) -Dgcc -DPART_${PART} -DTARGET_IS_${TARGET} -DUART_BUFFERED -MD -c -o $@ $<

