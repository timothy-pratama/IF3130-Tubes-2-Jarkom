################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/User/Group.cpp \
../Source/User/GroupService.cpp \
../Source/User/User.cpp \
../Source/User/UserService.cpp 

OBJS += \
./Source/User/Group.o \
./Source/User/GroupService.o \
./Source/User/User.o \
./Source/User/UserService.o 

CPP_DEPS += \
./Source/User/Group.d \
./Source/User/GroupService.d \
./Source/User/User.d \
./Source/User/UserService.d 


# Each subdirectory must supply rules for building sources it contributes
Source/User/%.o: ../Source/User/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


