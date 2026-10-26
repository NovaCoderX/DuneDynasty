################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/audio/audio_a5.cpp 

C_SRCS += \
../src/audio/audio.c \
../src/audio/midi_camd.c \
../src/audio/mt32mpu.c 

CPP_DEPS += \
./src/audio/audio_a5.d 

C_DEPS += \
./src/audio/audio.d \
./src/audio/midi_camd.d \
./src/audio/mt32mpu.d 

OBJS += \
./src/audio/audio.o \
./src/audio/audio_a5.o \
./src/audio/midi_camd.o \
./src/audio/mt32mpu.o 


# Each subdirectory must supply rules for building sources it contributes
src/audio/%.o: ../src/audio/%.c src/audio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/audio/%.o: ../src/audio/%.cpp src/audio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	m68k-amigaos-g++ -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-audio

clean-src-2f-audio:
	-$(RM) ./src/audio/audio.d ./src/audio/audio.o ./src/audio/audio_a5.d ./src/audio/audio_a5.o ./src/audio/midi_camd.d ./src/audio/midi_camd.o ./src/audio/mt32mpu.d ./src/audio/mt32mpu.o

.PHONY: clean-src-2f-audio

