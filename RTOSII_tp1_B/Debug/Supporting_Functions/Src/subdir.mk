################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Supporting_Functions/Src/supporting_Functions.c 

OBJS += \
./Supporting_Functions/Src/supporting_Functions.o 

C_DEPS += \
./Supporting_Functions/Src/supporting_Functions.d 


# Each subdirectory must supply rules for building sources it contributes
Supporting_Functions/Src/%.o Supporting_Functions/Src/%.su Supporting_Functions/Src/%.cyclo: ../Supporting_Functions/Src/%.c Supporting_Functions/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_B/src2/hal/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_B/src2/app/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_B/src2/lib/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../App/Inc -I../Supporting_Functions/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Supporting_Functions-2f-Src

clean-Supporting_Functions-2f-Src:
	-$(RM) ./Supporting_Functions/Src/supporting_Functions.cyclo ./Supporting_Functions/Src/supporting_Functions.d ./Supporting_Functions/Src/supporting_Functions.o ./Supporting_Functions/Src/supporting_Functions.su

.PHONY: clean-Supporting_Functions-2f-Src

