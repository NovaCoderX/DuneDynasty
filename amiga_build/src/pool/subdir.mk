################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/pool/house.c \
../src/pool/structure.c \
../src/pool/team.c \
../src/pool/unit.c 

C_DEPS += \
./src/pool/house.d \
./src/pool/structure.d \
./src/pool/team.d \
./src/pool/unit.d 

OBJS += \
./src/pool/house.o \
./src/pool/structure.o \
./src/pool/team.o \
./src/pool/unit.o 


# Each subdirectory must supply rules for building sources it contributes
src/pool/%.o: ../src/pool/%.c src/pool/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-pool

clean-src-2f-pool:
	-$(RM) ./src/pool/house.d ./src/pool/house.o ./src/pool/structure.d ./src/pool/structure.o ./src/pool/team.d ./src/pool/team.o ./src/pool/unit.d ./src/pool/unit.o

.PHONY: clean-src-2f-pool

