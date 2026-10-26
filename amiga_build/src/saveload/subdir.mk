################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/saveload/house.c \
../src/saveload/info.c \
../src/saveload/map.c \
../src/saveload/object.c \
../src/saveload/saveload.c \
../src/saveload/scenario.c \
../src/saveload/scriptengine.c \
../src/saveload/structure.c \
../src/saveload/team.c \
../src/saveload/unit.c 

C_DEPS += \
./src/saveload/house.d \
./src/saveload/info.d \
./src/saveload/map.d \
./src/saveload/object.d \
./src/saveload/saveload.d \
./src/saveload/scenario.d \
./src/saveload/scriptengine.d \
./src/saveload/structure.d \
./src/saveload/team.d \
./src/saveload/unit.d 

OBJS += \
./src/saveload/house.o \
./src/saveload/info.o \
./src/saveload/map.o \
./src/saveload/object.o \
./src/saveload/saveload.o \
./src/saveload/scenario.o \
./src/saveload/scriptengine.o \
./src/saveload/structure.o \
./src/saveload/team.o \
./src/saveload/unit.o 


# Each subdirectory must supply rules for building sources it contributes
src/saveload/%.o: ../src/saveload/%.c src/saveload/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-saveload

clean-src-2f-saveload:
	-$(RM) ./src/saveload/house.d ./src/saveload/house.o ./src/saveload/info.d ./src/saveload/info.o ./src/saveload/map.d ./src/saveload/map.o ./src/saveload/object.d ./src/saveload/object.o ./src/saveload/saveload.d ./src/saveload/saveload.o ./src/saveload/scenario.d ./src/saveload/scenario.o ./src/saveload/scriptengine.d ./src/saveload/scriptengine.o ./src/saveload/structure.d ./src/saveload/structure.o ./src/saveload/team.d ./src/saveload/team.o ./src/saveload/unit.d ./src/saveload/unit.o

.PHONY: clean-src-2f-saveload

