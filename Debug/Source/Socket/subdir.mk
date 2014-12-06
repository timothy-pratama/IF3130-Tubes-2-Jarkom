################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Socket/ActiveSocket.cpp \
../Source/Socket/ListenerSocket.cpp \
../Source/Socket/Socket.cpp 

OBJS += \
./Source/Socket/ActiveSocket.o \
./Source/Socket/ListenerSocket.o \
./Source/Socket/Socket.o 

CPP_DEPS += \
./Source/Socket/ActiveSocket.d \
./Source/Socket/ListenerSocket.d \
./Source/Socket/Socket.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Socket/%.o: ../Source/Socket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


