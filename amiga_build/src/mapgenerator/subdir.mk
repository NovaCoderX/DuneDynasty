################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/mapgenerator/skirmish.c 

C_DEPS += \
./src/mapgenerator/skirmish.d 

OBJS += \
./src/mapgenerator/skirmish.o 


# Each subdirectory must supply rules for building sources it contributes
src/mapgenerator/%.o: ../src/mapgenerator/%.c src/mapgenerator/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I/opt/amiga/include/allegro5/platform -I"/home/nova/Development/eclipse-workspace/DuneDynasty/include" -I"/home/nova/Development/eclipse-workspace/DuneDynasty/src" -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-mapgenerator

clean-src-2f-mapgenerator:
	-$(RM) ./src/mapgenerator/skirmish.d ./src/mapgenerator/skirmish.o

.PHONY: clean-src-2f-mapgenerator

