################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/shared/LED.obj: ../src/shared/LED.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Pro_tools/TI_Code_Composer_Studio_CCS/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --abi=eabi -me -Ooff --opt_for_speed=5 --fp_mode=strict --include_path="D:/Pro_tools/TI_Code_Composer_Studio_CCS/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="H:/MyDropbox/Dropbox/PiCopter_r1/CCS_projects/TivaWare" -g --gcc --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="src/shared/LED.pp" --obj_directory="src/shared" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/shared/MessageParser.obj: ../src/shared/MessageParser.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Pro_tools/TI_Code_Composer_Studio_CCS/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --abi=eabi -me -Ooff --opt_for_speed=5 --fp_mode=strict --include_path="D:/Pro_tools/TI_Code_Composer_Studio_CCS/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="H:/MyDropbox/Dropbox/PiCopter_r1/CCS_projects/TivaWare" -g --gcc --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="src/shared/MessageParser.pp" --obj_directory="src/shared" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/shared/SPISlave.obj: ../src/shared/SPISlave.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Pro_tools/TI_Code_Composer_Studio_CCS/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --abi=eabi -me -Ooff --opt_for_speed=5 --fp_mode=strict --include_path="D:/Pro_tools/TI_Code_Composer_Studio_CCS/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="H:/MyDropbox/Dropbox/PiCopter_r1/CCS_projects/TivaWare" -g --gcc --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="src/shared/SPISlave.pp" --obj_directory="src/shared" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


