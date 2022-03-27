################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../timer1.c \
../twi_slave.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
timer1.o \
twi_slave.o

OBJS_AS_ARGS +=  \
main.o \
timer1.o \
twi_slave.o

C_DEPS +=  \
main.d \
timer1.d \
twi_slave.d

C_DEPS_AS_ARGS +=  \
main.d \
timer1.d \
twi_slave.d

OUTPUT_FILE_PATH +=TM\ Warthog\ Alps\ Slew\ Mod.elf

OUTPUT_FILE_PATH_AS_ARGS +="TM Warthog Alps Slew Mod.elf"

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.35
	$(QUOTE)D:\Program Files\Microchip\xc8\v2.35\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATtiny441  -mdfp="D:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\ATtiny_DFP\1.10.348\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATtiny441__ -DNDEBUG  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./timer1.o: .././timer1.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.35
	$(QUOTE)D:\Program Files\Microchip\xc8\v2.35\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATtiny441  -mdfp="D:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\ATtiny_DFP\1.10.348\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATtiny441__ -DNDEBUG  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./twi_slave.o: .././twi_slave.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.35
	$(QUOTE)D:\Program Files\Microchip\xc8\v2.35\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATtiny441  -mdfp="D:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\ATtiny_DFP\1.10.348\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATtiny441__ -DNDEBUG  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking:  XC8 C Linker : 2.35
	$(QUOTE)D:\Program Files\Microchip\xc8\v2.35\bin\xc8-cc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mcpu=ATtiny441  -mdfp="D:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\ATtiny_DFP\1.10.348\xc8"  -Wl,-Map="TM Warthog Alps Slew Mod.map" -funsigned-char -funsigned-bitfields -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax --memorysummary,memoryfile.xml  
	@echo Finished building target: $@
	"D:\Program Files\Microchip\xc8\v2.35\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "TM Warthog Alps Slew Mod.elf" "TM Warthog Alps Slew Mod.hex"
	"D:\Program Files\Microchip\xc8\v2.35\bin\avr-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "TM Warthog Alps Slew Mod.elf" "TM Warthog Alps Slew Mod.eep" || exit 0
	"D:\Program Files\Microchip\xc8\v2.35\bin\avr-objdump.exe" -h -S "TM Warthog Alps Slew Mod.elf" > "TM Warthog Alps Slew Mod.lss"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "TM Warthog Alps Slew Mod.elf" "TM Warthog Alps Slew Mod.hex" "TM Warthog Alps Slew Mod.eep" "TM Warthog Alps Slew Mod.map" "TM Warthog Alps Slew Mod.usersignatures" "TM Warthog Alps Slew Mod.a"  "TM Warthog Alps Slew Mod.lss"
	