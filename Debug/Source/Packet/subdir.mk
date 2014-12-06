################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Packet/Packet.cpp \
../Source/Packet/broadcastPacket.cpp \
../Source/Packet/groupPacket.cpp \
../Source/Packet/incomingPacket.cpp \
../Source/Packet/loginPacket.cpp \
../Source/Packet/logoutPacket.cpp \
../Source/Packet/packetParser.cpp \
../Source/Packet/packetReceiver.cpp \
../Source/Packet/registerPacket.cpp \
../Source/Packet/sendPacket.cpp 

OBJS += \
./Source/Packet/Packet.o \
./Source/Packet/broadcastPacket.o \
./Source/Packet/groupPacket.o \
./Source/Packet/incomingPacket.o \
./Source/Packet/loginPacket.o \
./Source/Packet/logoutPacket.o \
./Source/Packet/packetParser.o \
./Source/Packet/packetReceiver.o \
./Source/Packet/registerPacket.o \
./Source/Packet/sendPacket.o 

CPP_DEPS += \
./Source/Packet/Packet.d \
./Source/Packet/broadcastPacket.d \
./Source/Packet/groupPacket.d \
./Source/Packet/incomingPacket.d \
./Source/Packet/loginPacket.d \
./Source/Packet/logoutPacket.d \
./Source/Packet/packetParser.d \
./Source/Packet/packetReceiver.d \
./Source/Packet/registerPacket.d \
./Source/Packet/sendPacket.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Packet/%.o: ../Source/Packet/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


