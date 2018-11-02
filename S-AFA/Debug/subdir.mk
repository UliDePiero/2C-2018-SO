################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Consola.c \
../PCP.c \
../PLP.c \
../S-AFA.c 

OBJS += \
./Consola.o \
./PCP.o \
./PLP.o \
./S-AFA.o 

C_DEPS += \
./Consola.d \
./PCP.d \
./PLP.d \
./S-AFA.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/workspace/tp-2018-2c-Intel-y-Gentes/BiblioConexiones" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


