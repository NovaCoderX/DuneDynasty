################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/audio/audlib/audlib_a5.c 

C_DEPS += \
./src/audio/audlib/audlib_a5.d 

OBJS += \
./src/audio/audlib/audlib_a5.o 


# Each subdirectory must supply rules for building sources it contributes
src/audio/audlib/%.o: ../src/audio/audlib/%.c src/audio/audlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-audio-2f-audlib

clean-src-2f-audio-2f-audlib:
	-$(RM) ./src/audio/audlib/audlib_a5.d ./src/audio/audlib/audlib_a5.o

.PHONY: clean-src-2f-audio-2f-audlib

