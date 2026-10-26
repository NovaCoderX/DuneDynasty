################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/crashlog/crashlog_none.c 

C_DEPS += \
./src/crashlog/crashlog_none.d 

OBJS += \
./src/crashlog/crashlog_none.o 


# Each subdirectory must supply rules for building sources it contributes
src/crashlog/%.o: ../src/crashlog/%.c src/crashlog/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-crashlog

clean-src-2f-crashlog:
	-$(RM) ./src/crashlog/crashlog_none.d ./src/crashlog/crashlog_none.o

.PHONY: clean-src-2f-crashlog

