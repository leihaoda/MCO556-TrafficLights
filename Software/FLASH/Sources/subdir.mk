################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Lights.c" \
"../Sources/StateTimeController.c" \
"../Sources/TemperatureSensor.c" \
"../Sources/Timer.c" \
"../Sources/TrafficControl.c" \
"../Sources/TrafficCounter.c" \
"../Sources/WalkRequest.c" \
"../Sources/analog.c" \
"../Sources/keypad.c" \
"../Sources/lcd.c" \
"../Sources/main.c" \
"../Sources/serial.c" \

C_SRCS += \
../Sources/Lights.c \
../Sources/StateTimeController.c \
../Sources/TemperatureSensor.c \
../Sources/Timer.c \
../Sources/TrafficControl.c \
../Sources/TrafficCounter.c \
../Sources/WalkRequest.c \
../Sources/analog.c \
../Sources/keypad.c \
../Sources/lcd.c \
../Sources/main.c \
../Sources/serial.c \

OBJS += \
./Sources/Lights_c.obj \
./Sources/StateTimeController_c.obj \
./Sources/TemperatureSensor_c.obj \
./Sources/Timer_c.obj \
./Sources/TrafficControl_c.obj \
./Sources/TrafficCounter_c.obj \
./Sources/WalkRequest_c.obj \
./Sources/analog_c.obj \
./Sources/keypad_c.obj \
./Sources/lcd_c.obj \
./Sources/main_c.obj \
./Sources/serial_c.obj \

OBJS_QUOTED += \
"./Sources/Lights_c.obj" \
"./Sources/StateTimeController_c.obj" \
"./Sources/TemperatureSensor_c.obj" \
"./Sources/Timer_c.obj" \
"./Sources/TrafficControl_c.obj" \
"./Sources/TrafficCounter_c.obj" \
"./Sources/WalkRequest_c.obj" \
"./Sources/analog_c.obj" \
"./Sources/keypad_c.obj" \
"./Sources/lcd_c.obj" \
"./Sources/main_c.obj" \
"./Sources/serial_c.obj" \

C_DEPS += \
./Sources/Lights_c.d \
./Sources/StateTimeController_c.d \
./Sources/TemperatureSensor_c.d \
./Sources/Timer_c.d \
./Sources/TrafficControl_c.d \
./Sources/TrafficCounter_c.d \
./Sources/WalkRequest_c.d \
./Sources/analog_c.d \
./Sources/keypad_c.d \
./Sources/lcd_c.d \
./Sources/main_c.d \
./Sources/serial_c.d \

C_DEPS_QUOTED += \
"./Sources/Lights_c.d" \
"./Sources/StateTimeController_c.d" \
"./Sources/TemperatureSensor_c.d" \
"./Sources/Timer_c.d" \
"./Sources/TrafficControl_c.d" \
"./Sources/TrafficCounter_c.d" \
"./Sources/WalkRequest_c.d" \
"./Sources/analog_c.d" \
"./Sources/keypad_c.d" \
"./Sources/lcd_c.d" \
"./Sources/main_c.d" \
"./Sources/serial_c.d" \

OBJS_OS_FORMAT += \
./Sources/Lights_c.obj \
./Sources/StateTimeController_c.obj \
./Sources/TemperatureSensor_c.obj \
./Sources/Timer_c.obj \
./Sources/TrafficControl_c.obj \
./Sources/TrafficCounter_c.obj \
./Sources/WalkRequest_c.obj \
./Sources/analog_c.obj \
./Sources/keypad_c.obj \
./Sources/lcd_c.obj \
./Sources/main_c.obj \
./Sources/serial_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/Lights_c.obj: ../Sources/Lights.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Lights.args" -ObjN="Sources/Lights_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/StateTimeController_c.obj: ../Sources/StateTimeController.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/StateTimeController.args" -ObjN="Sources/StateTimeController_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/TemperatureSensor_c.obj: ../Sources/TemperatureSensor.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/TemperatureSensor.args" -ObjN="Sources/TemperatureSensor_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/Timer_c.obj: ../Sources/Timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Timer.args" -ObjN="Sources/Timer_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/TrafficControl_c.obj: ../Sources/TrafficControl.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/TrafficControl.args" -ObjN="Sources/TrafficControl_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/TrafficCounter_c.obj: ../Sources/TrafficCounter.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/TrafficCounter.args" -ObjN="Sources/TrafficCounter_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/WalkRequest_c.obj: ../Sources/WalkRequest.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/WalkRequest.args" -ObjN="Sources/WalkRequest_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/analog_c.obj: ../Sources/analog.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/analog.args" -ObjN="Sources/analog_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/keypad_c.obj: ../Sources/keypad.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/keypad.args" -ObjN="Sources/keypad_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/lcd_c.obj: ../Sources/lcd.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/lcd.args" -ObjN="Sources/lcd_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/serial_c.obj: ../Sources/serial.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/serial.args" -ObjN="Sources/serial_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


