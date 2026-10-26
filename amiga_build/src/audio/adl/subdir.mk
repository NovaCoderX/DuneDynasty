################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/audio/adl/fmopl.cpp \
../src/audio/adl/opl_dosbox.cpp \
../src/audio/adl/opl_mame.cpp \
../src/audio/adl/sound_adlib.cpp 

CPP_DEPS += \
./src/audio/adl/fmopl.d \
./src/audio/adl/opl_dosbox.d \
./src/audio/adl/opl_mame.d \
./src/audio/adl/sound_adlib.d 

OBJS += \
./src/audio/adl/fmopl.o \
./src/audio/adl/opl_dosbox.o \
./src/audio/adl/opl_mame.o \
./src/audio/adl/sound_adlib.o 


# Each subdirectory must supply rules for building sources it contributes
src/audio/adl/%.o: ../src/audio/adl/%.cpp src/audio/adl/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	m68k-amigaos-g++ -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-audio-2f-adl

clean-src-2f-audio-2f-adl:
	-$(RM) ./src/audio/adl/fmopl.d ./src/audio/adl/fmopl.o ./src/audio/adl/opl_dosbox.d ./src/audio/adl/opl_dosbox.o ./src/audio/adl/opl_mame.d ./src/audio/adl/opl_mame.o ./src/audio/adl/sound_adlib.d ./src/audio/adl/sound_adlib.o

.PHONY: clean-src-2f-audio-2f-adl

