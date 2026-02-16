###  ███▄ ▄███▓▓█████  ███▄ ▄███▓ ▒█████   ██▀███ ▓██   ██▓ ###
### ▓██▒▀█▀ ██▒▓█   ▀ ▓██▒▀█▀ ██▒▒██▒  ██▒▓██ ▒ ██▒▒██  ██▒ ###
### ▓██    ▓██░▒███   ▓██    ▓██░▒██░  ██▒▓██ ░▄█ ▒ ▒██ ██░ ###
### ▒██    ▒██ ▒▓█  ▄ ▒██    ▒██ ▒██   ██░▒██▀▀█▄   ░ ▐██▓░ ###
### ▒██▒   ░██▒░▒████▒▒██▒   ░██▒░ ████▓▒░░██▓ ▒██▒ ░ ██▒▓░ ###
### ░ ▒░   ░  ░░░ ▒░ ░░ ▒░   ░  ░░ ▒░▒░▒░ ░ ▒▓ ░▒▓░  ██▒▒▒  ###
### ░  ░      ░ ░ ░  ░░  ░      ░  ░ ▒ ▒░   ░▒ ░ ▒░▓██ ░▒░  ###
### ░      ░      ░   ░      ░   ░ ░ ░ ▒    ░░   ░ ▒ ▒ ░░   ###
###        ░      ░  ░       ░       ░ ░     ░     ░ ░      ###
###                                                ░ ░      ###
###                    ▒█████    █████▒                     ###
###                   ▒██▒  ██▒▓██   ▒                      ###
###                   ▒██░  ██▒▒████ ░                      ###
###                   ▒██   ██░░▓█▒  ░                      ###
###                   ░ ████▓▒░░▒█░                         ###
###                   ░ ▒░▒░▒░  ▒ ░                         ###
###                     ░ ▒ ▒░  ░                           ###
###                   ░ ░ ░ ▒   ░ ░                         ###
###                       ░ ░                               ###
###                                                         ###
###  ▄▄▄       ██▓    ▓█████   ██████   ██████  ▄▄▄         ###
### ▒████▄    ▓██▒    ▓█   ▀ ▒██    ▒ ▒██    ▒ ▒████▄       ###
### ▒██  ▀█▄  ▒██░    ▒███   ░ ▓██▄   ░ ▓██▄   ▒██  ▀█▄     ###
### ░██▄▄▄▄██ ▒██░    ▒▓█  ▄   ▒   ██▒  ▒   ██▒░██▄▄▄▄██    ###
###  ▓█   ▓██▒░██████▒░▒████▒▒██████▒▒▒██████▒▒ ▓█   ▓██▒   ###
###  ▒▒   ▓▒█░░ ▒░▓  ░░░ ▒░ ░▒ ▒▓▒ ▒ ░▒ ▒▓▒ ▒ ░ ▒▒   ▓▒█░   ###
###   ▒   ▒▒ ░░ ░ ▒  ░ ░ ░  ░░ ░▒  ░ ░░ ░▒  ░ ░  ▒   ▒▒ ░   ###
###   ░   ▒     ░ ░      ░   ░  ░  ░  ░  ░  ░    ░   ▒      ###
###       ░  ░    ░  ░   ░  ░      ░        ░        ░  ░   ###

PROJECT ?= silent-hill-3

NON_MATCHING ?= 0
GENERATE_LCF ?= 1
GENERATE_REPORT ?= 0
###############################################################
SHELL := /bin/sh
ARCH := $(shell uname -m)
KERNEL := $(shell uname -s)
PLATFORM := $(if $(filter $(KERNEL),Darwin),macos,linux)
OS := $(PLATFORM)-$(subst _,-,$(ARCH))

MAKE := make
GIT := git
PYTHON := python3
PIP := $(PYTHON) -m pip
###############################################################
BUILD = build/$(SERIAL)
TOOLS := tools
CONFIG = $(PROJECT)/config/$(SERIAL)
ASM = $(CONFIG)/asm
ASSETS = $(CONFIG)/assets
EXPECTED = expected/$(SERIAL)
LINKERS = $(CONFIG)/linkers
ROM = rom/$(SERIAL)

INCLUDE = $(PROJECT)/include
SRC = $(PROJECT)/src

include $(PROJECT)/Makefile
###############################################################
BINARIES := $(SERIAL) $(OVERLAYS)
SOURCE_EXECUTABLE := $(ROM)/$(SERIAL)
ROM_SYMLINK = $(CONFIG)/rom
SOURCE_PREREQS = \
	$(SOURCE_EXECUTABLE) \
	$(SOURCE_OVERLAY_ARCHIVE) \
	$(OVERLAY_SOURCES) | $(ROM_SYMLINK)
OVERLAY_BINS := $(OVERLAYS:%=%.bin)
OVERLAY_SOURCE_DIR = $(ROM)/overlay
OVERLAY_SOURCES = $(OVERLAY_BINS:%=$(OVERLAY_SOURCE_DIR)/%)
OVERLAY_TARGETS = $(OVERLAY_BINS:%=$(BUILD)/%)
TARGETS = $(BUILD)/$(SERIAL) $(OVERLAY_TARGETS)

MACRO_INC := $(INCLUDE)/macro.inc
LINKER_SCRIPT := $(LINKERS)/$(SERIAL).lcf
YAMLS := $(shell find $(CONFIG) -name "*.yaml" ! -name "*.config.yaml")
SPLAT_CONFIG := $(CONFIG)/splat.config.yaml
D_FILES := \
	$(patsubst $(CONFIG)/%.yaml, $(LINKERS)/%.d, $(YAMLS))
###############################################################

BINUTILS_FLAVOR := mips-ps2-decompals
BINUTILS := $(TOOLS)/binutils-$(BINUTILS_FLAVOR)

AS := $(BINUTILS)/$(BINUTILS_FLAVOR)-as
MWCCGAP_AS_FLAGS := -mno-pdr
AS_FLAGS := \
	-EL -march=r5900 -mabi=eabi -G=0 \
	$(MWCCGAP_AS_FLAGS) -I$(INCLUDE)

LD :=
ifneq ($(NON_MATCHING),1)
	LD = $(WIBO) $(MWLD) -o "$@" $(MWLD_FLAGS) \
			"$(LINKER_SCRIPT)" $(shell find $(BUILD) -name "*.o")
endif

WIBO_BINARY := wibo-$(if $(filter $(ARCH),arm64),macos,$(ARCH))
WIBO := $(TOOLS)/$(WIBO_BINARY)

MWCCGAP_ENTRYPOINT := $(TOOLS)/mwccgap/mwccgap.py
MWCCGAP := $(PYTHON) $(MWCCGAP_ENTRYPOINT)
MWCCGAP_FLAGS := \
	--use-wibo \
    --wibo-path="$(WIBO)" \
    --mwcc-path="$(MWCC)" \
    --as-path=$(AS) \
    --src-dir="$(SRC)" \
	--asm-dir-prefix="$(CONFIG)" \
    --macro-inc-path="$(MACRO_INC)" \
    --as-march=r5900 \
    --as-mabi=eabi \
	--as-flags=$(MWCCGAP_AS_FLAGS)

ifeq ($(NON_MATCHING),1)
	CC = MWCIncludes="$(SRC)" $(WIBO) $(MWCC) $(MWCC_FLAGS) -c "$<" -o "$@"
else
	CC = MWCIncludes="$(SRC)" $(MWCCGAP) $(MWCCGAP_FLAGS) "$<" "$@" $(MWCC_FLAGS)
endif

BINUTILS_TAR := binutils-$(BINUTILS_FLAVOR)-$(OS).tar.gz

OBJCOPY := $(BINUTILS)/$(BINUTILS_FLAVOR)-objcopy
OBJDIFF_BINARY := objdiff-cli-$(PLATFORM)-$(ARCH)
OBJDIFF := $(TOOLS)/$(OBJDIFF_BINARY)

ALESSATOOL := $(PYTHON) $(TOOLS)/alessatool/alessatool.py --verbose
GENERATE := generate \
	--template_path $(INCLUDE)/$(SERIAL).inc.lcf \
	--output_path $(LINKERS)/$(SERIAL).lcf \
	--build_path $(BUILD) \
	--expected_path $(EXPECTED)


SPLAT := $(ALESSATOOL) $(GENERATE) --no-lcf --no-objdiff
ifeq ($(GENERATE_REPORT),0)
	SPLAT_AND_WRITE_LCF = $(ALESSATOOL) $(GENERATE) --no-objdiff
endif
ifeq ($(GENERATE_LCF),1)
	SPLAT_AND_WRITE_LCF := $(ALESSATOOL) $(GENERATE)
endif

CHECK_MATCH_PERCENT :=
ifneq ($(NON_MATCHING),1)
	CHECK_MATCH_PERCENT = @$(TOOLS)/scripts/diff.sh $(SERIAL) $(CONFIG) $(BUILD) $(OBJCOPY)
endif 

TOOLCHAIN := $(WIBO) $(MWCCGAP_ENTRYPOINT) $(MWCC) $(MWLD) $(AS)
SETUP := $(SOURCE_PREREQS) $(TOOLCHAIN)

WIBO_HOST := https://github.com/decompals/wibo/releases/download/1.0.1
COMPILERS_HOST := https://github.com/decompme/compilers/releases/download/compilers
BINUTILS_HOST := https://github.com/dreamingmoths/binutils-mips-ps2-decompals/releases/download/v0.8-aarch64
OBJDIFF_HOST := https://github.com/encounter/objdiff/releases/download/v3.6.0
###############################################################
all: $(TARGETS)

clean:
	rm -rf $(ASM)
	rm -rf $(ASSETS)
	rm -rf $(BUILD)
	rm -rf $(EXPECTED)
	rm -rf $(LINKERS)

report: $(SETUP) $(OBJDIFF) $(EXPECTED)
	@$(MAKE) GENERATE_REPORT=1 NON_MATCHING=1
	@$(OBJDIFF) report generate -o $(BUILD)/report.json

split: $(D_FILES)

expected: $(EXPECTED)

setup: $(SETUP)

rebuild:
	rm -rf $(BUILD)
	$(MAKE)

deep-clean:
	$(MAKE) PROJECT=silent-hill-3 clean
	$(MAKE) PROJECT=silent-hill-2 clean
	rm -rf expected

death:
	@$(MAKE) clean
	rm -rf $(OVERLAY_SOURCE_DIR)
	rm -rf $(BINUTILS)
	$(foreach tool,$(TOOLCHAIN),rm -f "$(tool)";)
	unlink $(ROM_SYMLINK)
	$(GIT) submodule foreach --recursive $(GIT) reset --hard

debug:
	@echo $(YAMLS)
	@echo $(SOURCE_PREREQS)
	@echo $(TARGETS)
	@echo $(BINARIES:%=$(LINKERS)/%.d)
	@echo '---'

diff:
	$(CHECK_MATCH_PERCENT)

compiler-info:
	$(WIBO) $(MWCC) -help

alessatool:
	$(ALESSATOOL)

sh3:
	$(MAKE) PROJECT="silent-hill-3"

sh2:
	$(MAKE) PROJECT="silent-hill-2"

sh3-report:
	$(MAKE) PROJECT="silent-hill-3" report

sh2-report:
	$(MAKE) PROJECT="silent-hill-2" report

sh3-clean:
	$(MAKE) PROJECT="silent-hill-3" clean

sh2-clean:
	$(MAKE) PROJECT="silent-hill-2" clean
###############################################################
$(LINKERS)/%.d: $(CONFIG)/overlay/%.yaml $(SPLAT_CONFIG) $(SETUP)
	$(SPLAT) $(SPLAT_CONFIG) $<

$(LINKERS)/%.d: $(CONFIG)/%.yaml $(SPLAT_CONFIG) $(SETUP)
	$(SPLAT_AND_WRITE_LCF) $(SPLAT_CONFIG) $<

$(BUILD)/$(SERIAL): $(SETUP) $(OVERLAY_TARGETS) $(LINKER_SCRIPT)
	$(LD)
	$(CHECK_MATCH_PERCENT)

$(BUILD)/%.c.o: $(PROJECT)/%.c
	@mkdir -p "$(@D)"
	$(CC)

$(BUILD)/%.s.o: $(CONFIG)/%.s
	@mkdir -p "$(@D)"
	$(AS) $(AS_FLAGS) -o "$@" "$<"

$(EXPECTED):
	@mkdir -p "$(@D)"
	@$(foreach yaml,$(YAMLS),$(SPLAT) --make-full-disasm-for-code $(SPLAT_CONFIG) "$(yaml)";)
	@rm -rf $(ASM)/matchings
	@rm -rf $(ASM)/nonmatchings
	@rm -rf $(ASM)/**/matchings
	@rm -rf $(ASM)/**/nonmatchings
	$(MAKE) $$(find $(ASM) -name '*.s' \
		| sed 's|^$(ASM)/|$(BUILD)/asm/|' \
		| sed 's|\.s$$|.s.o|')
	@mv $(BUILD) $(EXPECTED)

$(LINKER_SCRIPT): $(SPLAT_CONFIG) $(CONFIG)/$(SERIAL).yaml
	$(SPLAT_AND_WRITE_LCF) $(SPLAT_CONFIG) $(CONFIG)/$(SERIAL).yaml
###############################################################
$(WIBO):
	wget -O $@ $(WIBO_HOST)/$(WIBO_BINARY)
	chmod +x $(WIBO)

$(MWCC):
	@mkdir -p "$(@D)"
	wget -O- $(COMPILERS_HOST)/$(MWCC_TAR) | tar xzv -C "$(@D)"
	chmod +x $(MWCC)

$(MWLD):
	@mkdir -p "$(@D)"
	wget -O- $(COMPILERS_HOST)/$(MWLD_TAR) | tar xzv -C "$(@D)"
	chmod +x $(MWLD)

$(AS):
	@mkdir -p "$(@D)"
	wget -O- $(BINUTILS_HOST)/$(BINUTILS_TAR) | tar xzv -C "$(@D)"
	@chmod +x $(@D)/*

$(OBJDIFF):
	@mkdir -p "$(@D)"
	wget -O $@ $(OBJDIFF_HOST)/$(OBJDIFF_BINARY)
	@chmod +x $@

$(MWCCGAP_ENTRYPOINT):
	$(GIT) submodule update --init --recursive

$(OVERLAY_SOURCES): $(SOURCE_OVERLAY_ARCHIVE)
	$(ALESSATOOL) extract --archive-path $(SOURCE_OVERLAY_ARCHIVE) --output-dir $(ROM)

$(ROM_SYMLINK):
	ln -sf $(realpath $(ROM)) $@

$(SOURCE_OVERLAY_ARCHIVE) $(SOURCE_EXECUTABLE):
	@echo "$@ is missing, please provide this file."
###############################################################
PHONY_TARGETS := \
	alessatool clean compiler-info death debug deep-clean \
	diff expected heaven hell progress rebuild report setup \
	sh2 sh3 sh2-clean sh3-clean sh2-report sh3-report split
.PHONY: $(PHONY_TARGETS)
ifeq ($(filter $(PHONY_TARGETS),$(MAKECMDGOALS)),)
-include $(BINARIES:%=$(LINKERS)/%.d)
endif
