################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../ActiveSocket.o \
../Condition.o \
../ListenerSocket.o \
../Mutex.o \
../ReceiverThread.o \
../SenderThread.o \
../SendingThread.o \
../Server.o \
../Socket.o \
../Thread.o \
../User.o \
../UserService.o \
../server.o 

CPP_SRCS += \
../Server.cpp \
../client.cpp \
../server.cpp 

OBJS += \
./Server.o \
./client.o \
./server.o 

CPP_DEPS += \
./Server.d \
./client.d \
./server.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


