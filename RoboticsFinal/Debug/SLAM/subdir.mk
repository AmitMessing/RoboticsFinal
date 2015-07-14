################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SLAM/LocalizationManager.cpp \
../SLAM/Map.cpp \
../SLAM/MapUtilities.cpp \
../SLAM/Particle.cpp 

OBJS += \
./SLAM/LocalizationManager.o \
./SLAM/Map.o \
./SLAM/MapUtilities.o \
./SLAM/Particle.o 

CPP_DEPS += \
./SLAM/LocalizationManager.d \
./SLAM/Map.d \
./SLAM/MapUtilities.d \
./SLAM/Particle.d 


# Each subdirectory must supply rules for building sources it contributes
SLAM/%.o: ../SLAM/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


