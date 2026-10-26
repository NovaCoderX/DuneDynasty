################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/input/input_a5.c \
../src/input/input_dd.c \
../src/input/mouse_dd.c 

C_DEPS += \
./src/input/input_a5.d \
./src/input/input_dd.d \
./src/input/mouse_dd.d 

OBJS += \
./src/input/input_a5.o \
./src/input/input_dd.o \
./src/input/mouse_dd.o 


# Each subdirectory must supply rules for building sources it contributes
src/input/%.o: ../src/input/%.c src/input/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-input

clean-src-2f-input:
	-$(RM) ./src/input/input_a5.d ./src/input/input_a5.o ./src/input/input_dd.d ./src/input/input_dd.o ./src/input/mouse_dd.d ./src/input/mouse_dd.o

.PHONY: clean-src-2f-input

