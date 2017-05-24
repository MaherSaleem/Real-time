################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Globals.c \
../src/MessageQ.c \
../src/connection.c \
../src/main.c \
../src/our_GET.c \
../src/semafors.c \
../src/server_signals.c \
../src/setup_configrations.c \
../src/sharedMemory.c \
../src/worker.c 

OBJS += \
./src/Globals.o \
./src/MessageQ.o \
./src/connection.o \
./src/main.o \
./src/our_GET.o \
./src/semafors.o \
./src/server_signals.o \
./src/setup_configrations.o \
./src/sharedMemory.o \
./src/worker.o 

C_DEPS += \
./src/Globals.d \
./src/MessageQ.d \
./src/connection.d \
./src/main.d \
./src/our_GET.d \
./src/semafors.d \
./src/server_signals.d \
./src/setup_configrations.d \
./src/sharedMemory.d \
./src/worker.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


