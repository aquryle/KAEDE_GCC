################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LINKER_SCRIPT += \
../generate/linker_script.ld 

S_UPPER_SRCS += \
../generate/start.S 

C_SRCS += \
../generate/hwinit.c \
../generate/inthandler.c \
../generate/vects.c 

C_DEPS += \
./generate/hwinit.d \
./generate/inthandler.d \
./generate/vects.d 

OBJS += \
./generate/hwinit.o \
./generate/inthandler.o \
./generate/start.o \
./generate/vects.o 

S_UPPER_DEPS += \
./generate/start.d 


# Each subdirectory must supply rules for building sources it contributes
generate/%.o: ../generate/%.c
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -g2 -Wstack-usage=100 -mcpu=rx64m -misa=v2 -mlittle-endian-data -I"C:/Users/sata/develop/Renesas/e2_kaede/KAEDE_GCC/generate" -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -g2 -Wstack-usage=100 -mcpu=rx64m -misa=v2 -mlittle-endian-data -I"C:/Users/sata/develop/Renesas/e2_kaede/KAEDE_GCC/generate" -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	@rx-elf-gcc @"$@.in"
generate/%.o: ../generate/%.S
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -g2 -Wstack-usage=100 -mcpu=rx64m -misa=v2 -mlittle-endian-data -x assembler-with-cpp -Wa,--gdwarf2 -I"C:/Users/sata/develop/Renesas/e2_kaede/KAEDE_GCC/src" -Wa,-adlhn="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c "$<" -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -g2 -Wstack-usage=100 -mcpu=rx64m -misa=v2 -mlittle-endian-data -x assembler-with-cpp -Wa,--gdwarf2 -I"C:/Users/sata/develop/Renesas/e2_kaede/KAEDE_GCC/src" -Wa,-adlhn="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c "$<" -o "$@"'

	@rx-elf-gcc @"$@.in"

