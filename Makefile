# ---------------------------------------------------- USAGE ----------------------------------------------------
# make                  -> builds using settings of the    first BUILD VARIANT and the      first TARGET PLATFORM
# make variant          -> builds using settings of the "target" BUILD VARIANT and the      first TARGET PLATFORM
# make variant_platform -> builds using settings of the "target" BUILD VARIANT and the "platform" TARGET PLATFORM
# make run                  -> like "make"                 but (tries to) run the result
# make run_variant          -> like "make variant"          but (tries to) run the result
# make run_variant_platform -> like "make variant_platform" but (tries to) run the result
# make all -> builds every possible variant_platform combination



# -------------------------------------------------- SETTINGS ---------------------------------------------------
# caution: "make clean" removes OBJ and BIN directories completely
SRC_DIRECTORY := src
OBJ_DIRECTORY := .obj
BIN_DIRECTORY := bin
EXTERNAL_INCLUDE_DIRECTORY := external
SOURCE_FILE_EXTENSION := .cpp

# folders inside SRC_DIRECTORY, whose contents will be combined into a static library before linking
# specify relative path starting within SRC_DIRECTORY
LIBRARIES :=



# first platform specified is used as default
TARGET_PLATFORMS := linux windows

COMPILER_AND_LINKER_linux   := g++
COMPILER_AND_LINKER_windows := x86_64-w64-mingw32-g++-posix



# must be different from TARGET_PLATFORMS
# first variant specified is used as default
BUILD_VARIANTS := debug release test

# COMPILER_FLAGS, COMPILER_FLAGS_platform and COMPILER_FLAGS_variant will be combined
# resulting value can be overridden with COMPILER_FLAGS_variant_platform
COMPILER_FLAGS := -Wall -std=c++17 -I $(SRC_DIRECTORY) -I $(EXTERNAL_INCLUDE_DIRECTORY)
COMPILER_FLAGS_debug   := -DDOCTEST_CONFIG_DISABLE -O0 -g
COMPILER_FLAGS_release := -DDOCTEST_CONFIG_DISABLE -O2 -DNDEBUG
COMPILER_FLAGS_test    := -O2

# LINKER_FLAGS behave like COMPILER_FLAGS
LINKER_FLAGS_windows := -static-libstdc++



# ------------------------------------------ MAKE MAGIC - DO NOT TOUCH ------------------------------------------
# $1: library path
define find_library_source
$1_library_source_files := \
	$$(wildcard $$(SRC_DIRECTORY)/$1/*$$(SOURCE_FILE_EXTENSION)) \
	$$(wildcard $$(SRC_DIRECTORY)/$1/*/*$$(SOURCE_FILE_EXTENSION)) \
	$$(wildcard $$(SRC_DIRECTORY)/$1/*/*/*$$(SOURCE_FILE_EXTENSION)) \
	$$(wildcard $$(SRC_DIRECTORY)/$1/*/*/*/*$$(SOURCE_FILE_EXTENSION))
endef

$(foreach lib,$(LIBRARIES), \
	$(eval $(call find_library_source,$(lib))))
library_source_files = $(foreach lib,$(LIBRARIES),$($(lib)_library_source_files))

source_files = $(filter-out $(library_source_files), \
	$(wildcard $(SRC_DIRECTORY)/*$(SOURCE_FILE_EXTENSION)) \
	$(wildcard $(SRC_DIRECTORY)/*/*$(SOURCE_FILE_EXTENSION)) \
	$(wildcard $(SRC_DIRECTORY)/*/*/*$(SOURCE_FILE_EXTENSION)) \
	$(wildcard $(SRC_DIRECTORY)/*/*/*/*$(SOURCE_FILE_EXTENSION)) \
	$(wildcard $(SRC_DIRECTORY)/*/*/*/*/*$(SOURCE_FILE_EXTENSION)))

# $1: build variant
# $2: target platform
# $3: library path
define create_library_rule
library_object_files_$1_$2_$3 := $$(patsubst $$(SRC_DIRECTORY)/%$$(SOURCE_FILE_EXTENSION),$$(OBJ_DIRECTORY)/$2/$1/%.o,$($3_library_source_files))
$$(OBJ_DIRECTORY)/$2/$1/$3.a: $$(library_object_files_$1_$2_$3)
	@mkdir -p $$(@D)
	ar rcs $$@ $$^
endef



# $1: build variant
# $2: target platform
define create_build_variant_rules
object_files_$1_$2 := $$(patsubst $$(SRC_DIRECTORY)/%$$(SOURCE_FILE_EXTENSION),$$(OBJ_DIRECTORY)/$2/$1/%.o,$$(source_files))
library_files_$1_$2 := $$(foreach lib,$$(LIBRARIES),$$(OBJ_DIRECTORY)/$2/$1/$$(lib).a)
COMPILER_FLAGS_$1_$2 ?= $$(COMPILER_FLAGS) $$(COMPILER_FLAGS_$1) $$(COMPILER_FLAGS_$1)
LINKER_FLAGS_$1_$2   ?= $$(LINKER_FLAGS)   $$(LINKER_FLAGS_$1)   $$(LINKER_FLAGS_$2)

ifeq ($2,$(word 1,$(TARGET_PLATFORMS)))
.PHONY: $1 run_$1
$1: $1_$2
run_$1: run_$1_$2
endif

.PHONY: $1_$2 run_$1_$2
$1_$2: $$(BIN_DIRECTORY)/$2/$1
$$(BIN_DIRECTORY)/$2/$1: $$(object_files_$1_$2) $$(library_files_$1_$2)
	@mkdir -p $$(@D)
	$$(COMPILER_AND_LINKER_$2) $$(strip -o $$@ $$^ $$(LINKER_FLAGS_$1_$2))

$$(foreach lib,$$(LIBRARIES), \
	$$(eval $$(call create_library_rule,$1,$2,$$(lib))))

$$(OBJ_DIRECTORY)/$2/$1/%.o: $$(SRC_DIRECTORY)/%$$(SOURCE_FILE_EXTENSION)
	@mkdir -p $$(@D)
	$$(COMPILER_AND_LINKER_$2) $$(strip $$(COMPILER_FLAGS_$1_$2) -c $$< -o $$@)

run_$1_$2: $1_$2
	$(BIN_DIRECTORY)/$2/$1
endef



$(foreach target_platform,$(TARGET_PLATFORMS), \
	$(foreach build_variant,$(BUILD_VARIANTS), \
		$(eval $(call create_build_variant_rules,$(build_variant),$(target_platform)))))



.PHONY: clean run all
clean:
	rm -rf $(OBJ_DIRECTORY) $(BIN_DIRECTORY)

run: run_$(word 1,$(BUILD_VARIANTS))_$(word 1,$(TARGET_PLATFORMS))

all: $(foreach target_platform,$(TARGET_PLATFORMS), \
		$(foreach build_variant,$(BUILD_VARIANTS), \
			$(build_variant)_$(target_platform)))
