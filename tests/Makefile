.SUFFIXES:

# <summary>
# Path Variables
# </summary>
LOCAL := $(shell pwd)
BUILD := $(LOCAL)/../../..

# <summary>
# Compiling flags.
# </summary>
include $(BUILD)/Scripts/config.mk
include $(BUILD)/Scripts/functions.mk
include $(BUILD)/Scripts/rules.mk

# <summary>
# 
# </summary>
define test

  $(call msg,"Test",$1)

  @$(CC) -O3 $(CFLAGS) $(LDFLAGS) -o $1 $2

endef

CFLAGS += -I.
CFLAGS += -I./..
CFLAGS += -I./../include

# <summary>
# Linking flags for Target
# </summary>
LDFLAGS += -Wl,--whole-archive
LDFLAGS += $(LOCAL)/../libsystem.a
LDFLAGS += -Wl,--no-whole-archive

# <summary>
# Target (all)
# </summary>
all: $(OBJS)
	$(call test,perms,perms.c)
	$(call test,death,death.c)
	$(call test,nullpointer,nullpointer.c)
	$(call test,exception,exception.c)
	$(call test,settings,settings.c)
	$(call test,task,task.c)
	$(call test,task2,task2.c)
	$(call test,process,process1.c)
	$(call test,mount,mount.c)
	$(call test,file1,file1.c)
	$(call test,stack,stack.c)
	$(call test,res1,res1.c)
	$(call test,string,string.c)
	$(call test,hotplug,hotplug.c)
	$(call test,pointer,pointer.c)
	$(call test,lock,lock.c)

# <summary>
# Cleaning
# </summary>
clean:
	@echo "\tCleaning tests"
	@rm -f kernel
	@rm -f filewatch1
	@rm -f input
	@rm -f drives
	@rm -f disks
	@rm -f msg
	@rm -f hash
	@rm -f socket1
	@rm -f process1
	@rm -f file1
	@rm -f dir1
	@rm -f res1

