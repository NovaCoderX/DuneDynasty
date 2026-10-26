################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/os/amiga_main.c \
../src/os/endian.c \
../src/os/error.c 

C_DEPS += \
./src/os/amiga_main.d \
./src/os/endian.d \
./src/os/error.d 

OBJS += \
./src/os/amiga_main.o \
./src/os/endian.o \
./src/os/error.o 


# Each subdirectory must supply rules for building sources it contributes
src/os/%.o: ../src/os/%.c src/os/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-os

clean-src-2f-os:
	-$(RM) ./src/os/amiga_main.d ./src/os/amiga_main.o ./src/os/endian.d ./src/os/endian.o ./src/os/error.d ./src/os/error.o

.PHONY: clean-src-2f-os

