COMPILER_AND_LINKER := g++
SOURCE_FILE_EXTENSION := .cpp

# caution: "make clean" removes OBJ and BIN directories completely
SRC_DIRECTORY := src
OBJ_DIRECTORY := .obj
BIN_DIRECTORY := bin
EXTERNAL_INCLUDE_DIRECTORY := external

DEFAULT_BUILD_TARGET := debug
OTHER_BUILD_TARGETS := release test

LIBRARIES :=

COMPILER_FLAGS := -Wall -std=c++17 -I $(SRC_DIRECTORY) -I $(EXTERNAL_INCLUDE_DIRECTORY)
LINKER_FLAGS :=

COMPILER_FLAGS_debug   := $(COMPILER_FLAGS) -DDOCTEST_CONFIG_DISABLE -O0 -g
COMPILER_FLAGS_release := $(COMPILER_FLAGS) -DDOCTEST_CONFIG_DISABLE -O2 -DNDEBUG
COMPILER_FLAGS_test    := $(COMPILER_FLAGS) -O2



# ---------------------------------- make magic - do not touch ----------------------------------

define find_library_source
$1_library_source_files := \
	$$(wildcard $$(SRC_DIRECTORY)/$1/*$$(SOURCE_FILE_EXTENSION)) \
	$$(wildcard $$(SRC_DIRECTORY)/$1/*/*$$(SOURCE_FILE_EXTENSION)) \
	$$(wildcard $$(SRC_DIRECTORY)/$1/*/*/*$$(SOURCE_FILE_EXTENSION)) \
	$$(wildcard $$(SRC_DIRECTORY)/$1/*/*/*/*$$(SOURCE_FILE_EXTENSION))
endef

$(foreach lib,$(LIBRARIES),\
	$(eval $(call find_library_source,$(lib))))
library_source_files = $(foreach lib,$(LIBRARIES),$($(lib)_library_source_files))

source_files = $(filter-out $(library_source_files), \
	$(wildcard $(SRC_DIRECTORY)/*$(SOURCE_FILE_EXTENSION)) \
	$(wildcard $(SRC_DIRECTORY)/*/*$(SOURCE_FILE_EXTENSION)) \
	$(wildcard $(SRC_DIRECTORY)/*/*/*$(SOURCE_FILE_EXTENSION)) \
	$(wildcard $(SRC_DIRECTORY)/*/*/*/*$(SOURCE_FILE_EXTENSION)) \
	$(wildcard $(SRC_DIRECTORY)/*/*/*/*/*$(SOURCE_FILE_EXTENSION)) \
)

# $1: build target
# $2: library path
define create_library_target
library_object_files_$1_$2 := $$(patsubst $$(SRC_DIRECTORY)/%$$(SOURCE_FILE_EXTENSION),$$(OBJ_DIRECTORY)/$1/%.o,$($2_library_source_files))
$$(OBJ_DIRECTORY)/$1/$2.a: $$(library_object_files_$1_$2)
	@mkdir -p $$(@D)
	ar rcs $$@ $$^
endef

# $1: build target
define create_build_target
object_files_$1 := $$(patsubst $$(SRC_DIRECTORY)/%$$(SOURCE_FILE_EXTENSION),$$(OBJ_DIRECTORY)/$1/%.o,$$(source_files))
library_files_$1 := $$(foreach lib,$$(LIBRARIES),$$(OBJ_DIRECTORY)/$1/$$(lib).a)
COMPILER_FLAGS_$1 ?= $$(COMPILER_FLAGS)

.PHONY: $1 run_$1
$1: $$(BIN_DIRECTORY)/$1
$$(BIN_DIRECTORY)/$1: $$(object_files_$1) $$(library_files_$1)
	@mkdir -p $$(@D)
	$$(COMPILER_AND_LINKER) $$(strip -o $$@ $$^ $$(LINKER_FLAGS))

$$(foreach lib,$$(LIBRARIES),\
	$$(eval $$(call create_library_target,$1,$$(lib))))

$$(OBJ_DIRECTORY)/$1/%.o: $$(SRC_DIRECTORY)/%$$(SOURCE_FILE_EXTENSION)
	@mkdir -p $$(@D)
	$$(COMPILER_AND_LINKER) $$(strip $$(COMPILER_FLAGS_$1) -c $$< -o $$@)

run_$1: $1
	$(BIN_DIRECTORY)/$1
endef

$(foreach build_target,$(DEFAULT_BUILD_TARGET) $(OTHER_BUILD_TARGETS),\
	$(eval $(call create_build_target,$(build_target))))

.PHONY: clean run
clean:
	rm -rf $(OBJ_DIRECTORY) $(BIN_DIRECTORY)

run: run_$(DEFAULT_BUILD_TARGET)
