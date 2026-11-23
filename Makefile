HOSTCC ?= gcc
HFLAGS   = -std=gnu11 -Wall -Wextra -g -O0 -DUNIT_TEST -Iinclude -Iunity
HOST_SRC = $(filter-out src/startup.c src/main.c,$(wildcard src/*.c))
SUPPORT  = unity/unity.c

# To add new test script, run make build/"test_name" in root
build/test_%: test/test_%.c $(HOST_SRC) $(SUPPORT) $(wildcard include/*.h test/*.h)
	@mkdir -p build
	@$(HOSTCC) $(HFLAGS) -o $@ test/test_$*.c $(HOST_SRC) $(SUPPORT) -lm
# Run test, make sure the test script is in tests.active and type make test-active
test-active:
	@set -e; for t in $$(grep -v '^[[:space:]]*#' tests.active | grep -v '^[[:space:]]*$$'); do \
	  $(MAKE) --no-print-directory build/$$t; ./build/$$t; done

CROSS = arm-none-eabi-
CPU = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

RTOS_DIR  := rtos/FreeRTOS-Kernel
RTOS_PORT := $(RTOS_DIR)/portable/GCC/ARM_CM4F
RTOS_HEAP := $(RTOS_DIR)/portable/MemMang/heap_4.c
RTOS_SRC  := $(RTOS_DIR)/tasks.c \
						 $(RTOS_DIR)/list.c \
						 $(RTOS_DIR)/queue.c \
						 $(RTOS_DIR)/timers.c \
						 $(RTOS_DIR)/event_groups.c \
						 $(RTOS_DIR)/stream_buffer.c \
						 $(RTOS_PORT)/port.c \
						 $(RTOS_HEAP)
RTOS_INC := -Irtos/config -I$(RTOS_DIR)/include -I$(RTOS_PORT)

CFLAGS = $(CPU) -Os -g -std=gnu11 -Wall -Wextra -ffreestanding -fno-tree-loop-distribute-patterns -ffunction-sections -fdata-sections -Iinclude $(RTOS_INC)
LDFLAGS = $(CPU) -nostdlib --specs=nano.specs -T stm32f401.ld -Wl,-Map=build/firmware.map -Wl,--gc-sections
FW_SRC = $(wildcard src/*.c) $(RTOS_SRC)

build/firmware.elf: $(FW_SRC) $(wildcard include/*.h rtos/config/*.h) stm32f401.ld
	@mkdir -p build
	$(CROSS)gcc $(CFLAGS) $(FW_SRC) $(LDFLAGS) -Wl,--start-group -lc -lgcc -Wl,--end-group -o $@

build/firmware.bin: build/firmware.elf
	$(CROSS)objcopy -O binary $< $@

firmware: build/firmware.elf build/firmware.bin
size: build/firmware.elf
	$(CROSS)size $<

flash: build/firmware.elf
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/firmware.elf verify reset exit"

.PHONY: gdb
gdb: build/firmware.elf
	arm-none-eabi-gdb -q \
		-ex "target extended-remote :3333" \
		-ex "monitor reset halt" \
		-ex "load" \
		build/firmware.elf

.PHONY: t test-active test-all firmware size flash clean
clean:
	rm -rf build
