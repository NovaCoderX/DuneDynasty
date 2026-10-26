################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/newui/actionpanel.c \
../src/newui/halloffame.c \
../src/newui/mentat.c \
../src/newui/menu.c \
../src/newui/menubar.c \
../src/newui/savemenu.c \
../src/newui/scrollbar.c \
../src/newui/slider.c \
../src/newui/strategicmap.c \
../src/newui/viewport.c 

C_DEPS += \
./src/newui/actionpanel.d \
./src/newui/halloffame.d \
./src/newui/mentat.d \
./src/newui/menu.d \
./src/newui/menubar.d \
./src/newui/savemenu.d \
./src/newui/scrollbar.d \
./src/newui/slider.d \
./src/newui/strategicmap.d \
./src/newui/viewport.d 

OBJS += \
./src/newui/actionpanel.o \
./src/newui/halloffame.o \
./src/newui/mentat.o \
./src/newui/menu.o \
./src/newui/menubar.o \
./src/newui/savemenu.o \
./src/newui/scrollbar.o \
./src/newui/slider.o \
./src/newui/strategicmap.o \
./src/newui/viewport.o 


# Each subdirectory must supply rules for building sources it contributes
src/newui/%.o: ../src/newui/%.c src/newui/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-newui

clean-src-2f-newui:
	-$(RM) ./src/newui/actionpanel.d ./src/newui/actionpanel.o ./src/newui/halloffame.d ./src/newui/halloffame.o ./src/newui/mentat.d ./src/newui/mentat.o ./src/newui/menu.d ./src/newui/menu.o ./src/newui/menubar.d ./src/newui/menubar.o ./src/newui/savemenu.d ./src/newui/savemenu.o ./src/newui/scrollbar.d ./src/newui/scrollbar.o ./src/newui/slider.d ./src/newui/slider.o ./src/newui/strategicmap.d ./src/newui/strategicmap.o ./src/newui/viewport.d ./src/newui/viewport.o

.PHONY: clean-src-2f-newui

