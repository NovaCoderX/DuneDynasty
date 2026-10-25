################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/timer/timer.c \
../src/timer/timer_a5.c 

C_DEPS += \
./src/timer/timer.d \
./src/timer/timer_a5.d 

OBJS += \
./src/timer/timer.o \
./src/timer/timer_a5.o 


# Each subdirectory must supply rules for building sources it contributes
src/timer/%.o: ../src/timer/%.c src/timer/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I/opt/amiga/include/allegro5/platform -I"/home/nova/Development/eclipse-workspace/DuneDynasty/include" -I"/home/nova/Development/eclipse-workspace/DuneDynasty/src" -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-timer

clean-src-2f-timer:
	-$(RM) ./src/timer/timer.d ./src/timer/timer.o ./src/timer/timer_a5.d ./src/timer/timer_a5.o

.PHONY: clean-src-2f-timer

