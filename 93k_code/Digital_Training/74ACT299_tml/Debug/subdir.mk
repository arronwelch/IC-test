################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DPS_Meas_Task.cpp \
../DPS_Meas_Task_Gen.cpp \
../Functional.cpp \
../OutputDC.cpp 

OBJS += \
./DPS_Meas_Task.o \
./DPS_Meas_Task_Gen.o \
./Functional.o \
./OutputDC.o 

CPP_DEPS += \
./DPS_Meas_Task.d \
./DPS_Meas_Task_Gen.d \
./Functional.d \
./OutputDC.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DRHEL5 -D_TM_CDIR='"/home/demo/nq/Digital_Training/74ACT299_tml"' -I/opt/hp93000/soc/prod_com/include -I/opt/hp93000/soc/prod_com/include/MAPI -I/opt/hp93000/soc/testmethod/include -I/opt/hp93000/soc/com/include -I/opt/hp93000/soc/pws/lib -I/opt/hp93000/soc/segments/tml/include -I/opt/hp93000/soc/segments/tml/include/ext_include -I/opt/hp93000/soc/prod_com/rdi/include -I/opt/93000mts/mts//execution_engine/include -I/opt/93000mts/mts//solution_tools/common/include -O0 -g3 -Wall -c -fmessage-length=0 -fpic -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


