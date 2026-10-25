################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/audio/allegro_mad.c \
../src/audio/audio.c \
../src/audio/midi_alsa.c \
../src/audio/midi_none.c \
../src/audio/midi_osx.c \
../src/audio/midi_win32.c \
../src/audio/mt32mpu.c 

C_DEPS += \
./src/audio/allegro_mad.d \
./src/audio/audio.d \
./src/audio/midi_alsa.d \
./src/audio/midi_none.d \
./src/audio/midi_osx.d \
./src/audio/midi_win32.d \
./src/audio/mt32mpu.d 

OBJS += \
./src/audio/allegro_mad.o \
./src/audio/audio.o \
./src/audio/midi_alsa.o \
./src/audio/midi_none.o \
./src/audio/midi_osx.o \
./src/audio/midi_win32.o \
./src/audio/mt32mpu.o 


# Each subdirectory must supply rules for building sources it contributes
src/audio/%.o: ../src/audio/%.c src/audio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I/opt/amiga/include/allegro5/platform -I"/home/nova/Development/eclipse-workspace/DuneDynasty/include" -I"/home/nova/Development/eclipse-workspace/DuneDynasty/src" -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-audio

clean-src-2f-audio:
	-$(RM) ./src/audio/allegro_mad.d ./src/audio/allegro_mad.o ./src/audio/audio.d ./src/audio/audio.o ./src/audio/midi_alsa.d ./src/audio/midi_alsa.o ./src/audio/midi_none.d ./src/audio/midi_none.o ./src/audio/midi_osx.d ./src/audio/midi_osx.o ./src/audio/midi_win32.d ./src/audio/midi_win32.o ./src/audio/mt32mpu.d ./src/audio/mt32mpu.o

.PHONY: clean-src-2f-audio

