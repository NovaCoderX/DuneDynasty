################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/video/subdir.mk
-include src/tools/subdir.mk
-include src/timer/subdir.mk
-include src/table/subdir.mk
-include src/script/subdir.mk
-include src/saveload/subdir.mk
-include src/pool/subdir.mk
-include src/os/subdir.mk
-include src/newui/subdir.mk
-include src/mapgenerator/subdir.mk
-include src/input/subdir.mk
-include src/gui/subdir.mk
-include src/crashlog/subdir.mk
-include src/codec/subdir.mk
-include src/audio/audlib/subdir.mk
-include src/audio/adl/subdir.mk
-include src/audio/subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := DuneDynasty
BUILD_ARTIFACT_EXTENSION :=
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: DuneDynasty

# Tool invocations
DuneDynasty: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	m68k-amigaos-g++ -L../allegro5_wrapper/lib -s -noixemul -o "DuneDynasty" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) DuneDynasty
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
