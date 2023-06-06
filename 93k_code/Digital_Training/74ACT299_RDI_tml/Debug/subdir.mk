################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PMU_Meas.cpp \
../func_Idd_burst_meas.cpp \
../gross_func_rdi.cpp 

OBJS += \
./PMU_Meas.o \
./func_Idd_burst_meas.o \
./gross_func_rdi.o 

CPP_DEPS += \
./PMU_Meas.d \
./func_Idd_burst_meas.d \
./gross_func_rdi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DRHEL5 -D_TM_CDIR='"/home/demo/nq/Digital_Training/74ACT299_RDI_tml"' -I/opt/hp93000/soc/prod_com/include -I/opt/hp93000/soc/prod_com/include/MAPI -I/opt/hp93000/soc/testmethod/include -I/opt/hp93000/soc/com/include -I/opt/hp93000/soc/pws/lib -I/opt/hp93000/soc/segments/tml/include -I/opt/hp93000/soc/segments/tml/include/ext_include -I/opt/hp93000/soc/prod_com/rdi/include -I/opt/93000mts/mts//execution_engine/include -I/opt/93000mts/mts//solution_tools/common/include -O0 -g3 -Wall -c -fmessage-length=0 -fpic -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


