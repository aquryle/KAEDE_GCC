################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../peripheral/SCI7.c 

C_DEPS += \
./peripheral/SCI7.d 

OBJS += \
./peripheral/SCI7.o 


# Each subdirectory must supply rules for building sources it contributes
peripheral/%.o: ../peripheral/%.c
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -g2 -Wstack-usage=100 -mcpu=rx64m -misa=v2 -mlittle-endian-data -I"C:/Users/sata/develop/Renesas/e2_kaede/KAEDE_GCC/generate" -I"C:/Users/sata/develop/Renesas/e2_kaede/KAEDE_GCC/peripheral" -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -g2 -Wstack-usage=100 -mcpu=rx64m -misa=v2 -mlittle-endian-data -I"C:/Users/sata/develop/Renesas/e2_kaede/KAEDE_GCC/generate" -I"C:/Users/sata/develop/Renesas/e2_kaede/KAEDE_GCC/peripheral" -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	@rx-elf-gcc @"$@.in"

