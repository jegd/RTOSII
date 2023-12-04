################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src2/lib/src/delayAntibloqueo.c \
../src2/lib/src/eboard.c \
../src2/lib/src/eringbuffer.c \
../src2/lib/src/euart.c 

OBJS += \
./src2/lib/src/delayAntibloqueo.o \
./src2/lib/src/eboard.o \
./src2/lib/src/eringbuffer.o \
./src2/lib/src/euart.o 

C_DEPS += \
./src2/lib/src/delayAntibloqueo.d \
./src2/lib/src/eboard.d \
./src2/lib/src/eringbuffer.d \
./src2/lib/src/euart.d 


# Each subdirectory must supply rules for building sources it contributes
src2/lib/src/%.o src2/lib/src/%.su src2/lib/src/%.cyclo: ../src2/lib/src/%.c src2/lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_B/src2/hal/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_B/src2/app/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_B/src2/lib/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../App/Inc -I../Supporting_Functions/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src2-2f-lib-2f-src

clean-src2-2f-lib-2f-src:
	-$(RM) ./src2/lib/src/delayAntibloqueo.cyclo ./src2/lib/src/delayAntibloqueo.d ./src2/lib/src/delayAntibloqueo.o ./src2/lib/src/delayAntibloqueo.su ./src2/lib/src/eboard.cyclo ./src2/lib/src/eboard.d ./src2/lib/src/eboard.o ./src2/lib/src/eboard.su ./src2/lib/src/eringbuffer.cyclo ./src2/lib/src/eringbuffer.d ./src2/lib/src/eringbuffer.o ./src2/lib/src/eringbuffer.su ./src2/lib/src/euart.cyclo ./src2/lib/src/euart.d ./src2/lib/src/euart.o ./src2/lib/src/euart.su

.PHONY: clean-src2-2f-lib-2f-src

