################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/video/prim_a5.c \
../src/video/video_a5.c 

C_DEPS += \
./src/video/prim_a5.d \
./src/video/video_a5.d 

OBJS += \
./src/video/prim_a5.o \
./src/video/video_a5.o 


# Each subdirectory must supply rules for building sources it contributes
src/video/%.o: ../src/video/%.c src/video/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	m68k-amigaos-gcc -DNDEBUG -I../include -I../allegro5_wrapper/include -O2 -fno-optimize-sibling-calls -Wall -c -fmessage-length=0 -m68060 -noixemul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-video

clean-src-2f-video:
	-$(RM) ./src/video/prim_a5.d ./src/video/prim_a5.o ./src/video/video_a5.d ./src/video/video_a5.o

.PHONY: clean-src-2f-video

