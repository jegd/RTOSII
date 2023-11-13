################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src2/app/src/OA_BTN.c \
../src2/app/src/OA_LEDS.c \
../src2/app/src/app.c 

OBJS += \
./src2/app/src/OA_BTN.o \
./src2/app/src/OA_LEDS.o \
./src2/app/src/app.o 

C_DEPS += \
./src2/app/src/OA_BTN.d \
./src2/app/src/OA_LEDS.d \
./src2/app/src/app.d 


# Each subdirectory must supply rules for building sources it contributes
src2/app/src/%.o src2/app/src/%.su src2/app/src/%.cyclo: ../src2/app/src/%.c src2/app/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_prueba2/src2/hal/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_prueba2/src2/app/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_prueba2/src2/lib/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../App/Inc -I../Supporting_Functions/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src2-2f-app-2f-src

clean-src2-2f-app-2f-src:
	-$(RM) ./src2/app/src/OA_BTN.cyclo ./src2/app/src/OA_BTN.d ./src2/app/src/OA_BTN.o ./src2/app/src/OA_BTN.su ./src2/app/src/OA_LEDS.cyclo ./src2/app/src/OA_LEDS.d ./src2/app/src/OA_LEDS.o ./src2/app/src/OA_LEDS.su ./src2/app/src/app.cyclo ./src2/app/src/app.d ./src2/app/src/app.o ./src2/app/src/app.su

.PHONY: clean-src2-2f-app-2f-src

