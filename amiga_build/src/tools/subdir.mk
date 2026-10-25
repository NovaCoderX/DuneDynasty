################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tools/coord.c \
../src/tools/encoded_index.c \
../src/tools/orientation.c \
../src/tools/random_general.c \
../src/tools/random_lcg.c \
../src/tools/random_starport.c \
../src/tools/random_xorshift.c 

C_DEPS += \
./src/tools/coord.d \
./src/tools/encoded_index.d \
./src/tools/orientation.d \
./src/tools/random_general.d \
./src/tools/random_lcg.d \
./src/tools/random_starport.d \
./src/tools/random_xorshift.d 

OBJS += \
./src/tools/coord.o \
./src/tools/encoded_index.o \
./src/tools/orientation.o \
./src/tools/random_general.o \
./src/tools/random_lcg.o \
./src/tools/random_starport.o \
./src/tools/random_xorshift.o 


# Each subdirectory must supply rules for building sources it contributes
src/tools/%.o: ../src/tools/%.c src/tools/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I/opt/amiga/include/allegro5/platform -I"/home/nova/Development/eclipse-workspace/DuneDynasty/include" -I"/home/nova/Development/eclipse-workspace/DuneDynasty/src" -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-tools

clean-src-2f-tools:
	-$(RM) ./src/tools/coord.d ./src/tools/coord.o ./src/tools/encoded_index.d ./src/tools/encoded_index.o ./src/tools/orientation.d ./src/tools/orientation.o ./src/tools/random_general.d ./src/tools/random_general.o ./src/tools/random_lcg.d ./src/tools/random_lcg.o ./src/tools/random_starport.d ./src/tools/random_starport.o ./src/tools/random_xorshift.d ./src/tools/random_xorshift.o

.PHONY: clean-src-2f-tools

