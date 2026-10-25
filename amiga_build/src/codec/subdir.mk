################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/codec/format40.c \
../src/codec/format80.c 

C_DEPS += \
./src/codec/format40.d \
./src/codec/format80.d 

OBJS += \
./src/codec/format40.o \
./src/codec/format80.o 


# Each subdirectory must supply rules for building sources it contributes
src/codec/%.o: ../src/codec/%.c src/codec/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I/opt/amiga/include/allegro5/platform -I"/home/nova/Development/eclipse-workspace/DuneDynasty/include" -I"/home/nova/Development/eclipse-workspace/DuneDynasty/src" -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-codec

clean-src-2f-codec:
	-$(RM) ./src/codec/format40.d ./src/codec/format40.o ./src/codec/format80.d ./src/codec/format80.o

.PHONY: clean-src-2f-codec

