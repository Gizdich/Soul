CC = arm-none-eabi-gcc
MACHINE = cortex-m4
TARGET = ti/tm4c123g6hpm
INCLUDE = -Icommon/include -Itargets/$(TARGET)/include
CFLAGS = -g3 -c -mcpu=$(MACHINE) -mthumb -std=c99 -Wall -O0 $(INCLUDE)
BUILD_PATH = build
OBJECT_PATH = $(BUILD_PATH)/objects
LDFLAGS = -nostdlib -T targets/$(TARGET)/linkerScript.ld -Wl,-Map=$(BUILD_PATH)/soul.map
OBJECT_FILES = $(OBJECT_PATH)/kernel.o $(OBJECT_PATH)/kernelAsm.o $(OBJECT_PATH)/clock.o $(OBJECT_PATH)/startup.o $(OBJECT_PATH)/main.o

all: $(OBJECT_FILES) $(BUILD_PATH)/soul.elf

$(OBJECT_PATH)/kernel.o: common/kernel.c | $(OBJECT_PATH)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECT_PATH)/kernelAsm.o: targets/$(TARGET)/kernelAsm.s | $(OBJECT_PATH)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECT_PATH)/clock.o: targets/$(TARGET)/clock.c | $(OBJECT_PATH)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECT_PATH)/startup.o: targets/$(TARGET)/startup.c | $(OBJECT_PATH)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECT_PATH)/main.o: main.c | $(OBJECT_PATH)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_PATH)/soul.elf: $(OBJECT_FILES) | $(BUILD_PATH)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJECT_PATH):
	mkdir -p $@

clean:
	rm -rf $(BUILD_PATH)

load:
	openocd -f board/ti_ek-tm4c123gxl.cfg -c "init"

connect:
	arm-none-eabi-gdb $(BUILD_PATH)/soul.elf