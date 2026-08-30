#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# make sure we have bash
#---------------------------------------------------------------------------------
export SHELL := /usr/bin/env bash

#---------------------------------------------------------------------------------
# path to tools
#---------------------------------------------------------------------------------
DEVKITPATH=$(shell echo "$(DEVKITPRO)" | sed -e 's/^\([a-zA-Z]\):/\/\1/')
export PATH	:=	$(DEVKITPATH)/tools/bin:$(DEVKITPATH)/devkitARM/bin:$(PATH)

#---------------------------------------------------------------------------------
# the prefix on the compiler executables
#---------------------------------------------------------------------------------
PREFIX		:=	arm-none-eabi-

export CC	:=	$(PREFIX)gcc
export CXX	:=	$(PREFIX)g++
export AR	:=	$(PREFIX)gcc-ar
export OBJCOPY	:=	$(PREFIX)objcopy
export STRIP	:=	$(PREFIX)strip

ISVC=$(or $(VCBUILDHELPER_COMMAND),$(MSBUILDEXTENSIONSPATH32),$(MSBUILDEXTENSIONSPATH))

ifneq (,$(ISVC))
	ERROR_FILTER	:=	2>&1 | sed -e 's/\(.[a-zA-Z]\+\):\([0-9]\+\):/\1(\2):/g'
endif

#---------------------------------------------------------------------------------
# allow seeing compiler command lines with make V=1 (similar to autotools' silent)
#---------------------------------------------------------------------------------
ifeq ($(V),1)
    SILENTMSG := @true
    SILENTCMD :=
else
    SILENTMSG := @echo
    SILENTCMD := @
endif

#---------------------------------------------------------------------------------
# canned command sequence for binary data
#---------------------------------------------------------------------------------
define bin2o
        $(eval _tmpasm := $(shell mktemp))
        $(SILENTCMD)bin2s -a 4 -H `(echo $(<F) | tr . _)`.h $< > $(_tmpasm)
        $(SILENTCMD)$(CC) -x assembler-with-cpp $(CPPFLAGS) $(ASFLAGS) -c $(_tmpasm) -o $(<F).o
        @rm $(_tmpasm)
endef

#---------------------------------------------------------------------------------
# Generate compile commands
#---------------------------------------------------------------------------------
ifeq ($(GENERATE_COMPILE_COMMANDS),1)
    ADD_COMPILE_COMMAND := @/opt/devkitpro/tools/bin/generate_compile_commands
else
    ADD_COMPILE_COMMAND := @true
endif

#---------------------------------------------------------------------------------
%.a:
#---------------------------------------------------------------------------------
	$(SILENTMSG) $(notdir $@)
	@rm -f $@
	$(SILENTCMD)$(AR) -rc $@ $^

#---------------------------------------------------------------------------------
%.arm.o: CFLAGS    += -marm
%.arm.o: CXXFLAGS  += -marm

#---------------------------------------------------------------------------------
%.thumb.o: CFLAGS    += -mthumb
%.thumb.o: CXXFLAGS  += -mthumb

#---------------------------------------------------------------------------------
%.iwram.o: CFLAGS    += -marm -mlong-calls
%.iwram.o: CXXFLAGS  += -marm -mlong-calls

#---------------------------------------------------------------------------------
%.itcm.o: CFLAGS     += -marm -mlong-calls
%.itcm.o: CXXFLAGS   += -marm -mlong-calls

#---------------------------------------------------------------------------------
%.o: %.cpp
	$(SILENTMSG) CXX.9 $(notdir $<)
	$(ADD_COMPILE_COMMAND) add $(CXX) "$(CPPFLAGS) $(CXXFLAGS) -c $< -o $@" $<
	$(SILENTCMD)$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.d $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ $(ERROR_FILTER)

#---------------------------------------------------------------------------------
%.o: %.c
	$(SILENTMSG) CC.9 $(notdir $<)
	$(SILENTCMD)$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(ERROR_FILTER)
	$(ADD_COMPILE_COMMAND) add $(CC) "$(CPPFLAGS) $(CFLAGS) -c $< -o $@" $<

#---------------------------------------------------------------------------------
%.o: %.s
	$(SILENTMSG) AS.9 $(notdir $<)
	$(ADD_COMPILE_COMMAND) add $(CC) "-x assembler-with-cpp $(CPPFLAGS) $(ASFLAGS) -c $< -o $@" $<
	$(SILENTCMD)$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d -x assembler-with-cpp $(CPPFLAGS) $(ASFLAGS) -c $< -o $@ $(ERROR_FILTER)

#---------------------------------------------------------------------------------
%.arm9: %.elf
	$(SILENTCMD)$(OBJCOPY) -O binary $< $@
	$(SILENTMSG) built ... $(notdir $@)

#---------------------------------------------------------------------------------
%.elf:
	$(SILENTMSG) linking $(notdir $@)
	$(ADD_COMPILE_COMMAND) end
	$(SILENTCMD)$(LD)  $(LDFLAGS) $(OFILES) $(LIBPATHS) $(LIBS) -o $@

#---------------------------------------------------------------------------------
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
# DATA is a list of directories containing binary files
# all directories are relative to this makefile
#---------------------------------------------------------------------------------
BUILD		:=	build
SOURCES		:=	source
INCLUDES	:=	include ../common
DATA		:=
GRAPHICS	:=	data


#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-mthumb -mthumb-interwork


CFLAGS	:=	-g -Wall -Wextra -Wlogical-op -Wno-psabi -O3 -D_FORTIFY_SOURCE=1\
			-Wshadow -Wpointer-arith -Wcast-qual -Wno-ignored-qualifiers\
			-Wduplicated-branches -Wduplicated-cond -Wno-volatile\
			-Wfloat-equal -Wformat=1 -Wlogical-op -Werror\
			-Wno-analyzer-possible-null-dereference -Wno-stringop-overflow\
			-Wno-analyzer-possible-null-argument -Wno-stringop-overread\
			-Wno-array-bounds -Wno-analyzer-null-dereference\
			-Wno-analyzer-use-of-uninitialized-value -Wno-restrict\
			-Wmissing-noreturn -Wsuggest-attribute=malloc -Wunused-macros\
			-Wno-class-memaccess -march=armv5te -mtune=arm946e-s -fomit-frame-pointer\
			-ffast-math -fgcse-sm -fgcse-las -fgcse-after-reload -funsafe-loop-optimizations\
			$(EXTRA_FLAGS) -DGAME_CODE="\"$(GAME_CODE)\"" -DVERSION=$(VERSION) \
			-DGAME_TITLE="\"$(GAME_TITLE)\"" -DVERSION_NAME="\"$(VERSION_NAME)\"" $(ARCH) \

ifdef DESQUID
CFLAGS	+=	-DDESQUID
endif
ifdef NOSOUND
CFLAGS	+=	-DNO_SOUND
endif
ifdef NOSOUNDFADE
CFLAGS	+=	-DNO_FADE
endif
ifdef FLASHCARD
CFLAGS	+=	-DFLASHCARD
endif


CFLAGS	+=	$(INCLUDE) -DARM9
CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions -std=c++23 -Wno-multichar

ASFLAGS	:=	-g $(ARCH) -march=armv5te -mtune=arm946e-s

LDFLAGS	=	-specs=$(CURDIR)/../link/neo_ds_arm9.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------

LIBS	:=	-lfat -ldswifi9 -lnds9 -lfont

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBPATH	:=	../lib/
LIBDIRS	:=	$(foreach dir,$(LIBPATH),$(sort $(dir $(wildcard $(dir)/*/))))

#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export ARM9ELF	:=	$(CURDIR)/$(TARGET).elf
export DEPSDIR := $(CURDIR)/$(BUILD)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
					$(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir))

ALL_CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
ALL_CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
ALL_SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

OV_CFILES		:=	$(sort $(filter ov_%.c, $(ALL_CFILES)))
OV_CPPFILES		:=	$(sort $(filter ov_%.cpp, $(ALL_CPPFILES)))
OV_SFILES		:=	$(sort $(filter ov_%.s, $(ALL_SFILES)))
ALL_OVERLAYS	:=	$(OV_CFILES) $(OV_CPPFILES) $(OV_SFILES)

CFILES		:=	$(filter-out ov_%.c, $(ALL_CFILES))
CPPFILES	:=	$(filter-out ov_%.cpp, $(ALL_CPPFILES))
SFILES		:=	$(filter-out ov_%.s, $(ALL_SFILES))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))
PNGFILES	:=	$(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.png)))


export CONFIG_FILE  := $(CURDIR)/link/overlays.config
export EXPORTED_OVERLAYS :=

ifneq ($(wildcard $(CONFIG_FILE)),)
# Strip comments and collect every raw line definition
RAW_LINES := $(shell grep -v '^\s*\#' $(CONFIG_FILE) | grep -v '^\s*$$' | tr '\n' ';')
$(foreach line,$(subst ;, ,$(RAW_LINES)), \
	$(eval _ID  := $(word 1,$(subst |, ,$(line)))) \
	$(eval _GRP := $(word 2,$(subst |, ,$(line)))) \
	$(eval _LIM := $(word 3,$(subst |, ,$(line)))) \
	$(eval _AFT := $(word 4,$(subst |, ,$(line)))) \
	$(eval _AFT_CLEAN := $(patsubst after=%,%,$(_AFT))) \
	$(eval EXPORTED_OVERLAYS += $(_ID)) \
	$(eval export OVERLAY_$(_ID)_GRP := $(_GRP)) \
	$(eval export OVERLAY_$(_ID)_LIM := $(_LIM)) \
	$(eval export OVERLAY_$(_ID)_AFT := $(_AFT_CLEAN)) \
)
endif

export OVERLAY_RAW_IDS	:=	$(sort $(EXPORTED_OVERLAYS))

RAW_STRIPPED		:=	$(patsubst ov_%,%,$(ALL_OVERLAYS))
PURE_NUMERIC_IDS	:=
$(foreach item,$(RAW_STRIPPED), \
	$(eval _ID := $(firstword $(subst _, ,$(item)))) \
	$(eval _ID_CLEAN := $(patsubst %.cpp,%,$(patsubst %.c,%,$(patsubst %.s,%,$(_ID))))) \
	$(eval PURE_NUMERIC_IDS += $(_ID_CLEAN)) \
)

export OVERLAY_RAW_IDS	:=	$(sort $(PURE_NUMERIC_IDS))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(ALL_CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

$(OV_CPPFILES:.cpp=.o):	CXXFLAGS	+= -DCOMPILING_OVERLAY_MODULE=1 $(filter-out -O3,$(CXXFLAGS)) -O1 -mlong-calls
$(OV_CFILES:.c=.o):		CFLAGS		+= -DCOMPILING_OVERLAY_MODULE=1 $(filter-out -O3,$(CFLAGS)) -O1 -mlong-calls

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
					$(PNGFILES:.png=.o) \
					$(ALL_CPPFILES:.cpp=.o) $(ALL_CFILES:.c=.o) $(ALL_SFILES:.s=.o)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(abspath $(CURDIR)/$(dir))) \
			$(foreach dir,$(LIBDIRS),-I$(abspath $(dir)/include)) \
			-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(abspath $(dir)/lib))

.PHONY: $(BUILD)

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -f $(CURDIR)/Makefile generate_header
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
	@$(MAKE) --no-print-directory -f $(CURDIR)/Makefile validate_sizes


generate_header:
	$(SILENTMSG) generating overlay definition header...
	$(SILENTCMD)mkdir -p $(BUILD)
	$(SILENTCMD)out_file="$(BUILD)/overlay_table.h"; \
	echo "#pragma once" > $$out_file; \
	echo "#include <nds/ndstypes.h>" >> $$out_file; \
	echo "#include <overlay.h>" >> $$out_file; \
	echo "" >> $$out_file; \
	echo "extern \"C\" {" >> $$out_file; \
	grep -v '^\s*#' "$(CONFIG_FILE)" | grep -v '^\s*$$' | while read -r line || [ -n "$$line" ]; do \
		id=$$(echo "$$line" | cut -d'|' -f1 | xargs); \
		echo "    extern u8 __ov$${id}_start[];" >> $$out_file; \
		echo "    extern u8 __ov$${id}_end[];" >> $$out_file; \
		echo "    extern u8 __ov$${id}_ctors_start[];" >> $$out_file; \
		echo "    extern u8 __ov$${id}_ctors_end[];" >> $$out_file; \
	done; \
	echo "}" >> $$out_file; \
	echo "" >> $$out_file; \
	grep -v '^\s*#' "$(CONFIG_FILE)" | grep -v '^\s*$$' | while read -r line || [ -n "$$line" ]; do \
		id=$$(echo "$$line" | cut -d'|' -f1 | xargs); \
		echo "static const OvHeader __ov_hdr_ov$${id} = {" >> $$out_file; \
		echo "    .m_id           = ( $${id} )," >> $$out_file; \
		echo "    .m_ramAddress   = (u32) __ov$${id}_start," >> $$out_file; \
		echo "    .m_ramSize      = (u32) ( __ov$${id}_end - __ov$${id}_start )," >> $$out_file; \
		echo "    .m_bssSize      = 0," >> $$out_file; \
		echo "    .m_sinitInit    = (u32) __ov$${id}_ctors_start," >> $$out_file; \
		echo "    .m_sinitInitEnd = (u32) __ov$${id}_ctors_end," >> $$out_file; \
		echo "    .m_fileName     = ( $${id} )," >> $$out_file; \
		echo "    .m_comprSize    = 0," >> $$out_file; \
		echo "    .m_flag         = 0" >> $$out_file; \
		echo "};" >> $$out_file; \
		echo "" >> $$out_file; \
	done; \
	echo "static const OvHeader OVERLAYS[] = {" >> $$out_file; \
	grep -v '^\s*#' "$(CONFIG_FILE)" | grep -v '^\s*$$' | while read -r line || [ -n "$$line" ]; do \
		id=$$(echo "$$line" | cut -d'|' -f1 | xargs); \
		echo "    __ov_hdr_ov$${id}," >> $$out_file; \
	done; \
	echo "};" >> $$out_file; \
	echo "static const u32 OVERLAY_COUNT = sizeof( OVERLAYS ) / sizeof( OVERLAYS[ 0 ] );" >> $$out_file

validate_sizes:
	@echo "Checking overlay memory usage..."
	$(SILENTCMD)if [ ! -f "$(CONFIG_FILE)" ]; then echo "(missing overlay configuration.)"; exit 0; fi; \
	grep -v '^\s*#' "$(CONFIG_FILE)" | grep -v '^\s*$$' | while read -r line || [ -n "$$line" ]; do \
		id=$$(echo "$$line" | cut -d'|' -f1 | xargs); \
		grp=$$(echo "$$line" | cut -d'|' -f2 | xargs); \
		lim=$$(echo "$$line" | cut -d'|' -f3 | xargs); \
		if [ -z "$$lim" ]; then lim=0; fi; \
		bin_file="$(CURDIR)/../FSROOT/ov/$${id}"; \
		if [ -f "$$bin_file" ]; then \
			v_size=$$(wc -c < "$$bin_file" | xargs); \
		else \
			v_size=-1; \
		fi; \
		if [ -z "$$v_size" ]; then v_size=0; fi; \
		if [ "$$v_size" -gt "$$lim" ]; then \
			echo "[FAIL] $${id} ($$grp): $$v_size / $$lim"; \
			exit 1; \
		else \
			echo "[ OK ] $${id} ($$grp): $$v_size / $$lim"; \
		fi; \
	done

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) *.elf *.nds* *.bin ../FSROOT/ov

rebuild: clean $(BUILD)

#---------------------------------------------------------------------------------
else

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(ARM9ELF):	 _overlay.ld $(OFILES)
	@echo linking $(notdir $@)
	$(ADD_COMPILE_COMMAND) end
	$(SILENTCMD)$(LD)  $(LDFLAGS) $(OFILES) $(LIBPATHS) $(LIBS) -o $@.full 2> >(grep -v "not in segment" >&2)
	$(SILENTMSG) processing overlay binary assets...
	$(SILENTCMD)mkdir -p $(CURDIR)/../../FSROOT/ov
	$(SILENTCMD)for id in $$(grep -v '^\s*\#' "$(CONFIG_FILE)" | grep -v '^\s*$$' | cut -d'|' -f1 | xargs); do \
		$(OBJCOPY) -O binary -j .ov$${id} $@.full $(CURDIR)/../../FSROOT/ov/$${id}; \
	done
	$(SILENTMSG) cleaning ELF...
	$(SILENTCMD)$(OBJCOPY) \
		$$(grep -v '^\s*\#' "$(CONFIG_FILE)" | grep -v '^\s*$$' | cut -d'|' -f1 | sed 's/^/--remove-section=.ov/') \
		--strip-all \
		$@.full $@

_overlay.ld:
	$(SILENTMSG) generating overlay table definitions...
	$(SILENTCMD)echo "/* Automatically Generated */" > $@
	$(SILENTCMD)echo "__overlay_peak_vma = __overlay_vma_start;" >> $@
	$(SILENTCMD)PREV_LMA="__overlay_vma_start"; \
		while read -r line || [ -n "$$line" ]; do \
			id=$$(echo "$$line" | cut -d'|' -f1 | xargs); \
			grp=$$(echo "$$line" | cut -d'|' -f2 | xargs); \
			lim=$$(echo "$$line" | cut -d'|' -f3 | xargs); \
			aft=$$(echo "$$line" | cut -d'|' -f4 | grep "after=" | sed 's/after=//' | xargs); \
			echo "/* --- Module ID: $${id} [Group: $$grp] --- */" >> $@; \
			if [ -z "$$aft" ]; then \
				target_vma="__overlay_vma_start"; \
			else \
				ifs_save=$$IFS; IFS=','; \
				max_expr=""; \
				for parent in $$aft; do \
					parent_clean=$$(echo "$$parent" | xargs); \
					if [ -z "$$max_expr" ]; then \
						max_expr="__ov$${parent_clean}_end"; \
					else \
						max_expr="MAX($$max_expr, __ov$${parent_clean}_end)"; \
					fi; \
				done; \
				IFS=$$ifs_save; \
				target_vma="$$max_expr"; \
			fi; \
			echo ".ov$${id} $$target_vma : AT($$PREV_LMA)" >> $@; \
			echo "{" >> $@; \
			echo "    __ov$${id}_start = .;" >> $@; \
			echo "    KEEP(*ov_$${id}.o(.text.ov_$${id}_main))" >> $@; \
			echo "    KEEP(*ov_$${id}_*.o(.text .text.* .rodata .rodata.* .data .data.* .bss .bss.* COMMON))" >> $@; \
			echo "    KEEP(*(.ov$${id} .ov$${id}.* .ov$${id}_* .ov$${id}_*.*))" >> $@; \
			echo "    __ov$${id}_ctors_start = .;" >> $@; \
			echo "    KEEP(*ov_$${id}.o(.ctors .ctors.* .init_array .init_array.*))" >> $@; \
			echo "    KEEP(*ov_$${id}_*.o(.ctors .ctors.* .init_array .init_array.*))" >> $@; \
			echo "    __ov$${id}_ctors_end = .;" >> $@; \
			echo "    __ov$${id}_dtors_start = .;" >> $@; \
			echo "    KEEP(*ov_$${id}.o(.dtors .dtors.* .fini_array .fini_array.*))" >> $@; \
			echo "    KEEP(*ov_$${id}_*.o(.dtors .dtors.* .fini_array .fini_array.*))" >> $@; \
			echo "    __ov$${id}_dtors_end = .;" >> $@; \
			echo "    KEEP(*ov_$${id}.o(.text .text.* .rodata .rodata.* .data .data.* .bss .bss.* COMMON))" >> $@; \
			echo "    . = ALIGN(4);" >> $@; \
			echo "    __ov$${id}_end = .;" >> $@; \
			echo "}" >> $@; \
			echo "PROVIDE(__ov$${id}_lma = LOADADDR(.ov$${id}));" >> $@; \
			echo "PROVIDE(__ov$${id}_size = SIZEOF(.ov$${id}));" >> $@; \
			echo "" >> $@; \
			echo "__overlay_peak_vma = DEFINED(.ov$${id}) ? MAX(__overlay_peak_vma, __ov$${id}_end) : __overlay_peak_vma;" >> $@; \
			PREV_LMA="$$PREV_LMA + DEFINED(.ov$${id}) ? SIZEOF(.ov$${id}) : 0"; \
		done < <(grep -v '^\s*#' "$(CONFIG_FILE)" | grep -v '^\s*$$')
		$(SILENTCMD)echo "" >> $@

.PRECIOUS: %.h %.s

#---------------------------------------------------------------------------------
%.s %.h	: %.png %.grit
#---------------------------------------------------------------------------------
	$(SILENTCMD)grit $< -fts -o$*

#---------------------------------------------------------------------------------
%.bin.o	: %.bin
#---------------------------------------------------------------------------------
	$(SILENTMSG) bin2o.9 $(notdir $<)
	$(SILENTCMD)$(bin2o)

-include $(DEPSDIR)/*.d

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
