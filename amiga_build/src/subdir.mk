################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ai.c \
../src/animation.c \
../src/binheap.c \
../src/buildqueue.c \
../src/common_a5.c \
../src/config_a5.c \
../src/cutscene.c \
../src/enhancement.c \
../src/explosion.c \
../src/file.c \
../src/gfx.c \
../src/house.c \
../src/ini.c \
../src/load.c \
../src/map.c \
../src/object.c \
../src/opendune.c \
../src/save.c \
../src/scenario.c \
../src/shape.c \
../src/sprites.c \
../src/string.c \
../src/structure.c \
../src/team.c \
../src/tile.c \
../src/unit.c \
../src/wsa.c 

C_DEPS += \
./src/ai.d \
./src/animation.d \
./src/binheap.d \
./src/buildqueue.d \
./src/common_a5.d \
./src/config_a5.d \
./src/cutscene.d \
./src/enhancement.d \
./src/explosion.d \
./src/file.d \
./src/gfx.d \
./src/house.d \
./src/ini.d \
./src/load.d \
./src/map.d \
./src/object.d \
./src/opendune.d \
./src/save.d \
./src/scenario.d \
./src/shape.d \
./src/sprites.d \
./src/string.d \
./src/structure.d \
./src/team.d \
./src/tile.d \
./src/unit.d \
./src/wsa.d 

OBJS += \
./src/ai.o \
./src/animation.o \
./src/binheap.o \
./src/buildqueue.o \
./src/common_a5.o \
./src/config_a5.o \
./src/cutscene.o \
./src/enhancement.o \
./src/explosion.o \
./src/file.o \
./src/gfx.o \
./src/house.o \
./src/ini.o \
./src/load.o \
./src/map.o \
./src/object.o \
./src/opendune.o \
./src/save.o \
./src/scenario.o \
./src/shape.o \
./src/sprites.o \
./src/string.o \
./src/structure.o \
./src/team.o \
./src/tile.o \
./src/unit.o \
./src/wsa.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/ai.d ./src/ai.o ./src/animation.d ./src/animation.o ./src/binheap.d ./src/binheap.o ./src/buildqueue.d ./src/buildqueue.o ./src/common_a5.d ./src/common_a5.o ./src/config_a5.d ./src/config_a5.o ./src/cutscene.d ./src/cutscene.o ./src/enhancement.d ./src/enhancement.o ./src/explosion.d ./src/explosion.o ./src/file.d ./src/file.o ./src/gfx.d ./src/gfx.o ./src/house.d ./src/house.o ./src/ini.d ./src/ini.o ./src/load.d ./src/load.o ./src/map.d ./src/map.o ./src/object.d ./src/object.o ./src/opendune.d ./src/opendune.o ./src/save.d ./src/save.o ./src/scenario.d ./src/scenario.o ./src/shape.d ./src/shape.o ./src/sprites.d ./src/sprites.o ./src/string.d ./src/string.o ./src/structure.d ./src/structure.o ./src/team.d ./src/team.o ./src/tile.d ./src/tile.o ./src/unit.d ./src/unit.o ./src/wsa.d ./src/wsa.o

.PHONY: clean-src

