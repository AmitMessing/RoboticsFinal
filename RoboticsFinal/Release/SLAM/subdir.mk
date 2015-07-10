################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SLAM/Map.cpp \
../SLAM/Particle.cpp \
../SLAM/SlamManager.cpp 

OBJS += \
./SLAM/Map.o \
./SLAM/Particle.o \
./SLAM/SlamManager.o 

CPP_DEPS += \
./SLAM/Map.d \
./SLAM/Particle.d \
./SLAM/SlamManager.d 


# Each subdirectory must supply rules for building sources it contributes
SLAM/%.o: ../SLAM/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


