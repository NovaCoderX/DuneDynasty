################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/script/general.c \
../src/script/script.c \
../src/script/structure.c \
../src/script/team.c \
../src/script/unit.c 

C_DEPS += \
./src/script/general.d \
./src/script/script.d \
./src/script/structure.d \
./src/script/team.d \
./src/script/unit.d 

OBJS += \
./src/script/general.o \
./src/script/script.o \
./src/script/structure.o \
./src/script/team.o \
./src/script/unit.o 


# Each subdirectory must supply rules for building sources it contributes
src/script/%.o: ../src/script/%.c src/script/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-script

clean-src-2f-script:
	-$(RM) ./src/script/general.d ./src/script/general.o ./src/script/script.d ./src/script/script.o ./src/script/structure.d ./src/script/structure.o ./src/script/team.d ./src/script/team.o ./src/script/unit.d ./src/script/unit.o

.PHONY: clean-src-2f-script

