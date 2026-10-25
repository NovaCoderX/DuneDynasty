################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/table/actioninfo.c \
../src/table/animation.c \
../src/table/explosion.c \
../src/table/fileinfo.c \
../src/table/houseanimation.c \
../src/table/houseinfo.c \
../src/table/landscapeinfo.c \
../src/table/locale.c \
../src/table/movementtype.c \
../src/table/selectiontype.c \
../src/table/sound.c \
../src/table/structureinfo.c \
../src/table/teamaction.c \
../src/table/tilediff.c \
../src/table/unitinfo.c \
../src/table/widget.c \
../src/table/widgetinfo.c \
../src/table/windowdesc.c 

C_DEPS += \
./src/table/actioninfo.d \
./src/table/animation.d \
./src/table/explosion.d \
./src/table/fileinfo.d \
./src/table/houseanimation.d \
./src/table/houseinfo.d \
./src/table/landscapeinfo.d \
./src/table/locale.d \
./src/table/movementtype.d \
./src/table/selectiontype.d \
./src/table/sound.d \
./src/table/structureinfo.d \
./src/table/teamaction.d \
./src/table/tilediff.d \
./src/table/unitinfo.d \
./src/table/widget.d \
./src/table/widgetinfo.d \
./src/table/windowdesc.d 

OBJS += \
./src/table/actioninfo.o \
./src/table/animation.o \
./src/table/explosion.o \
./src/table/fileinfo.o \
./src/table/houseanimation.o \
./src/table/houseinfo.o \
./src/table/landscapeinfo.o \
./src/table/locale.o \
./src/table/movementtype.o \
./src/table/selectiontype.o \
./src/table/sound.o \
./src/table/structureinfo.o \
./src/table/teamaction.o \
./src/table/tilediff.o \
./src/table/unitinfo.o \
./src/table/widget.o \
./src/table/widgetinfo.o \
./src/table/windowdesc.o 


# Each subdirectory must supply rules for building sources it contributes
src/table/%.o: ../src/table/%.c src/table/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I/opt/amiga/include/allegro5/platform -I"/home/nova/Development/eclipse-workspace/DuneDynasty/include" -I"/home/nova/Development/eclipse-workspace/DuneDynasty/src" -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-table

clean-src-2f-table:
	-$(RM) ./src/table/actioninfo.d ./src/table/actioninfo.o ./src/table/animation.d ./src/table/animation.o ./src/table/explosion.d ./src/table/explosion.o ./src/table/fileinfo.d ./src/table/fileinfo.o ./src/table/houseanimation.d ./src/table/houseanimation.o ./src/table/houseinfo.d ./src/table/houseinfo.o ./src/table/landscapeinfo.d ./src/table/landscapeinfo.o ./src/table/locale.d ./src/table/locale.o ./src/table/movementtype.d ./src/table/movementtype.o ./src/table/selectiontype.d ./src/table/selectiontype.o ./src/table/sound.d ./src/table/sound.o ./src/table/structureinfo.d ./src/table/structureinfo.o ./src/table/teamaction.d ./src/table/teamaction.o ./src/table/tilediff.d ./src/table/tilediff.o ./src/table/unitinfo.d ./src/table/unitinfo.o ./src/table/widget.d ./src/table/widget.o ./src/table/widgetinfo.d ./src/table/widgetinfo.o ./src/table/windowdesc.d ./src/table/windowdesc.o

.PHONY: clean-src-2f-table

