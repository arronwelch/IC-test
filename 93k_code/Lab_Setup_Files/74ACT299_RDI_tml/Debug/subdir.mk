################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PMU_Meas.cpp \
../dynamic_idd_rdi.cpp \
../func_Idd_burst_meas.cpp \
../gross_func_RDI.cpp 

OBJS += \
./PMU_Meas.o \
./dynamic_idd_rdi.o \
./func_Idd_burst_meas.o \
./gross_func_RDI.o 

CPP_DEPS += \
./PMU_Meas.d \
./dynamic_idd_rdi.d \
./func_Idd_burst_meas.d \
./gross_func_RDI.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_TM_CDIR='"/home/Jeff.Schulze/TEMP/TEMP/74ACT299_RDI_tml"' -I/opt/hp93000/soc/prod_com/include -I/opt/hp93000/soc/prod_com/include/MAPI -I/opt/hp93000/soc/testmethod/include -I/opt/hp93000/soc/com/include -I/opt/hp93000/soc/pws/lib -I/opt/hp93000/soc/segments/tml/include -I/opt/hp93000/soc/prod_com/rdi/include -O0 -g3 -Wall -c -fmessage-length=0 -fpic -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


