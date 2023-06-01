################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DPS_Meas.cpp \
../DPS_Meas_Task.cpp \
../Functional.cpp \
../OutputDC.cpp 

OBJS += \
./DPS_Meas.o \
./DPS_Meas_Task.o \
./Functional.o \
./OutputDC.o 

CPP_DEPS += \
./DPS_Meas.d \
./DPS_Meas_Task.d \
./Functional.d \
./OutputDC.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DRHEL5 -D_TM_CDIR='"/home/jspreux/DigitalTraining_7_4_4/74ACT299_tml"' -I/opt/hp93000/soc/prod_com/include -I/opt/hp93000/soc/prod_com/include/MAPI -I/opt/hp93000/soc/testmethod/include -I/opt/hp93000/soc/com/include -I/opt/hp93000/soc/pws/lib -I/opt/hp93000/soc/segments/tml/include -I/opt/hp93000/soc/segments/tml/include/ext_include -I/opt/hp93000/soc/prod_com/rdi/include -O0 -g3 -Wall -c -fmessage-length=0 -fpic -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


