.SUFFIXES:
.PHONY: tests

# <summary>
# Path Variables
# </summary>
LOCAL := $(shell pwd)
BUILD := $(LOCAL)/../..

# <summary>
# Build scripts.
# </summary>
include $(BUILD)/Scripts/config.mk
include $(BUILD)/Scripts/functions.mk
include $(BUILD)/Scripts/rules.mk

# <summary>
# Compile flags
# </summary>
CFLAGS += -I.
CFLAGS += -I./include
CFLAGS += -I./source/private
CFLAGS += -I./source
#CFLAGS += -Wno-unused-variable
#CFLAGS += -Wno-unused-function
CFLAGS += -D_GNU_SOURCE
CFLAGS += -DDEBUG
CFLAGS += -Wall
CFLAGS += -O3
#CFLAGS += -g

# <summary>
# Linking flags
# </summary>

# <summary>
# Source Objects
# </summary>
OBJS += source/core/cpu.o
OBJS += source/core/crc32.o
OBJS += source/core/user.o
OBJS += source/core/group.o
OBJS += source/core/process.o
OBJS += source/core/shutdown.o
OBJS += source/core/string.o
OBJS += source/core/env.o

OBJS += source/arch/arch-x86.o
OBJS += source/arch/task-x86.o
OBJS += source/arch/arch-x86_64.o

OBJS += source/kernel/proc.o
OBJS += source/kernel/fence.o
OBJS += source/kernel/async.o
OBJS += source/kernel/common.o
OBJS += source/kernel/permission.o
OBJS += source/kernel/boot.o
OBJS += source/kernel/reboot.o
OBJS += source/kernel/process.o
OBJS += source/kernel/memory.o
OBJS += source/kernel/mutex.o
OBJS += source/kernel/wait.o
OBJS += source/kernel/notify.o
OBJS += source/kernel/task.o
OBJS += source/kernel/lock.o

OBJS += source/ipc/exception.o
OBJS += source/ipc/interface.o
#OBJS += source/ipc/dispatch.o
#OBJS += source/ipc/binder.o
#OBJS += source/ipc/ole.o

OBJS += source/events/dispatch.o
OBJS += source/events/pointer.o
OBJS += source/events/view.o

OBJS += source/io/match.o
OBJS += source/io/memory.o
OBJS += source/io/resources.o
#OBJS += source/io/attributes.o
OBJS += source/io/directory.o
OBJS += source/io/content.o
OBJS += source/io/mapping.o
OBJS += source/io/handle.o
OBJS += source/io/mount.o
OBJS += source/io/file.o
OBJS += source/io/link.o

OBJS += source/crypt/md5.o
OBJS += source/crypt/uuid.o
OBJS += source/crypt/hash.o

OBJS += source/private/framework.o
OBJS += source/private/main.o

OBJS += source/memory/virtual.o
OBJS += source/memory/task.o


OBJS += source/settings/read.o
OBJS += source/settings/write.o
OBJS += source/settings/settings.o

# <summary>
# Target (all)
# </summary>
all: $(OBJS)
	$(call link_static,libsystem.a,$(OBJS))
	$(call link_shared,libsystem.so,$(OBJS))
#	$(OD) -d --disassembler-options=intel clone.o
	$(RD) -d /System/Libraries/libc.so
	$(RD) -d libsystem.so

tests:
	@echo "Build tests"
	@$(MAKE) -C tests

# <summary>
# Cleaning
# </summary>
clean:
	@echo "\tCleaning libsystem"
	@rm -f libsystem.so
	@rm -f libsystem.a
	@rm -f $(OBJS)

