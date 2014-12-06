################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Thread/Condition.cpp \
../Source/Thread/Mutex.cpp \
../Source/Thread/ReceiverThread.cpp \
../Source/Thread/SenderThread.cpp \
../Source/Thread/Thread.cpp \
../Source/Thread/ThreadFactory.cpp 

OBJS += \
./Source/Thread/Condition.o \
./Source/Thread/Mutex.o \
./Source/Thread/ReceiverThread.o \
./Source/Thread/SenderThread.o \
./Source/Thread/Thread.o \
./Source/Thread/ThreadFactory.o 

CPP_DEPS += \
./Source/Thread/Condition.d \
./Source/Thread/Mutex.d \
./Source/Thread/ReceiverThread.d \
./Source/Thread/SenderThread.d \
./Source/Thread/Thread.d \
./Source/Thread/ThreadFactory.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Thread/%.o: ../Source/Thread/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


