################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src2/tasks/src/task_button.c \
../src2/tasks/src/task_led.c 

OBJS += \
./src2/tasks/src/task_button.o \
./src2/tasks/src/task_led.o 

C_DEPS += \
./src2/tasks/src/task_button.d \
./src2/tasks/src/task_led.d 


# Each subdirectory must supply rules for building sources it contributes
src2/tasks/src/%.o src2/tasks/src/%.su src2/tasks/src/%.cyclo: ../src2/tasks/src/%.c src2/tasks/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../App/Inc -I../Supporting_Functions/Inc -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_prueba/src2/app/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_prueba/src2/lib/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/Ejercicios/RTOSII_tp1_prueba/src2/hal/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src2-2f-tasks-2f-src

clean-src2-2f-tasks-2f-src:
	-$(RM) ./src2/tasks/src/task_button.cyclo ./src2/tasks/src/task_button.d ./src2/tasks/src/task_button.o ./src2/tasks/src/task_button.su ./src2/tasks/src/task_led.cyclo ./src2/tasks/src/task_led.d ./src2/tasks/src/task_led.o ./src2/tasks/src/task_led.su

.PHONY: clean-src2-2f-tasks-2f-src

