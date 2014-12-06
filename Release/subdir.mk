################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ActiveSocket.cpp \
../ListenerSocket.cpp \
../client.cpp \
../main.cpp 

OBJS += \
./ActiveSocket.o \
./ListenerSocket.o \
./client.o \
./main.o 

CPP_DEPS += \
./ActiveSocket.d \
./ListenerSocket.d \
./client.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


