HOSTCC ?= gcc 
HFLAGS   = -std=gnu11 -Wall -Wextra -g -O0 -DUNIT_TEST -Iinclude -Iunity
HOST_SRC = $(filter-out src/startup.c src/main.c,$(wildcard src/*.c))
SUPPORT  = unity/unity.c

build/test_%: test/test_%.c $(HOST_SRC) $(SUPPORT) $(wildcard include/*.h test/*.h)
	@mkdir -p build
	@$(HOSTCC) $(HFLAGS) -o $@ test/test_$*.c $(HOST_SRC) $(SUPPORT) -lm
test-active:
	@set -e; for t in $$(grep -v '^[[:space:]]*#' tests.active | grep -v '^[[:space:]]*$$'); do \
	  $(MAKE) --no-print-directory build/$$t; ./build/$$t; done

CROSS = arm-none-eabi-
CPU = -mcpu=cortex-m4 -mthumb
CFLAGS = $(CPU) -Os -g -std=gnu11 -Wall -Wextra -ffreestanding -fno-tree-loop-distribute-patterns -ffunction-sections -fdata-sections -Iinclude
LDFLAGS = $(CPU) -nostdlib -T stm32f401.ld -Wl,-Map=build/firmware.map -Wl,--gc-sections
FW_SRC = $(wildcard src/*.c)

build/firmware.elf: $(FW_SRC) $(wildcard include/*.h) stm32f401.ld 
	@mkdir -p build
	$(CROSS)gcc $(CFLAGS) $(FW_SRC) $(LDFLAGS) -lgcc -o $@

build/firmware.bin: build/firmware.elf 
	$(CROSS)objcopy -O binary $< $@

firmware: build/firmware.elf build/firmware.bin
size: build/firmware.elf
	$(CROSS)size $<

flash: build/firmware.elf 
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/firmware.elf verify reset exit"

.PHONY: t test-active test-all firmware size flash clean
clean:
	rm -rf build
