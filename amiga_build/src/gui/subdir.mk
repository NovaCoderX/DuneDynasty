################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/gui/editbox.c \
../src/gui/font.c \
../src/gui/gui.c \
../src/gui/mentat.c \
../src/gui/security.c \
../src/gui/viewport.c \
../src/gui/widget.c \
../src/gui/widget_click.c \
../src/gui/widget_draw.c 

C_DEPS += \
./src/gui/editbox.d \
./src/gui/font.d \
./src/gui/gui.d \
./src/gui/mentat.d \
./src/gui/security.d \
./src/gui/viewport.d \
./src/gui/widget.d \
./src/gui/widget_click.d \
./src/gui/widget_draw.d 

OBJS += \
./src/gui/editbox.o \
./src/gui/font.o \
./src/gui/gui.o \
./src/gui/mentat.o \
./src/gui/security.o \
./src/gui/viewport.o \
./src/gui/widget.o \
./src/gui/widget_click.o \
./src/gui/widget_draw.o 


# Each subdirectory must supply rules for building sources it contributes
src/gui/%.o: ../src/gui/%.c src/gui/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I/opt/amiga/include/allegro5/platform -I"/home/nova/Development/eclipse-workspace/DuneDynasty/include" -I"/home/nova/Development/eclipse-workspace/DuneDynasty/src" -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-gui

clean-src-2f-gui:
	-$(RM) ./src/gui/editbox.d ./src/gui/editbox.o ./src/gui/font.d ./src/gui/font.o ./src/gui/gui.d ./src/gui/gui.o ./src/gui/mentat.d ./src/gui/mentat.o ./src/gui/security.d ./src/gui/security.o ./src/gui/viewport.d ./src/gui/viewport.o ./src/gui/widget.d ./src/gui/widget.o ./src/gui/widget_click.d ./src/gui/widget_click.o ./src/gui/widget_draw.d ./src/gui/widget_draw.o

.PHONY: clean-src-2f-gui

