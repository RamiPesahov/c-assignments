# --- Configuration ---
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
RUN_DIR = run
TARGETS = ex1 ex2 

# Define all executables built in the run directory
EXECUTABLES = $(TARGETS:%=$(RUN_DIR)/%)

# --- Test Directories ---
TEST_DIR = tests
INPUT_DIR = $(TEST_DIR)/inputs
OUTPUT_DIR = $(TEST_DIR)/outputs

# --- Directory Setup and Compilation ---

# The default target builds all executables
.PHONY: all
all: $(EXECUTABLES)

# Rule to create the run directory
$(RUN_DIR):
	@mkdir -p $(RUN_DIR)
	@echo "Created output directory: $(RUN_DIR)"

# Generic rule to compile a .c file into an executable in the $(RUN_DIR)
$(RUN_DIR)/%: %.c | $(RUN_DIR)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) $< -o $@

# --- Testing Targets ---

# AUTOMATICALLY DISCOVER TEST CASES
# 1. Find all .txt files in inputs/exN
# 2. Strip the path to get just the filename (e.g., "base_10_000.txt")
EX1_TEST_FILES = $(notdir $(wildcard $(INPUT_DIR)/ex1/*.txt))
EX2_TEST_FILES = $(notdir $(wildcard $(INPUT_DIR)/ex2/*.txt))

# The main test target runs all specific test suites
.PHONY: test test_ex1 test_ex2 

test: test_ex1 test_ex2 
	@echo ""
	@echo "=========================================================="
	@echo "--- All test suites completed! Check output above. ---"
	@echo "=========================================================="

# Macro containing only the recipe (shell commands) for testing
# Usage: $(call TEST_RECIPE, executable_number, list_of_filenames)
define TEST_RECIPE
	@echo ""
	@echo "--- Running Test Suite for ex$(1) ($(words $(2)) examples) ---"
	@if [ -z "$(2)" ]; then \
		echo "   [WARNING] No test files found in $(INPUT_DIR)/ex$(1)/"; \
	else \
		for test_file in $(2); do \
			INPUT_FILE="$(INPUT_DIR)/ex$(1)/$$test_file"; \
			EXPECTED_FILE="$(OUTPUT_DIR)/ex$(1)/$$test_file"; \
			ACTUAL_FILE="$(RUN_DIR)/ex$(1)_$${test_file}.actual"; \
			\
			echo "-> Testing case: $$test_file"; \
			\
			if [ ! -f "$$EXPECTED_FILE" ]; then \
				echo "   [ERROR] Missing expected output file: $$EXPECTED_FILE"; \
				continue; \
			fi; \
			\
			./$(RUN_DIR)/ex$(1) < "$$INPUT_FILE" > "$$ACTUAL_FILE"; \
			\
			if diff -w -B --strip-trailing-cr "$$EXPECTED_FILE" "$$ACTUAL_FILE" > /dev/null; then \
				echo "   [PASS] $$test_file"; \
				rm -f "$$ACTUAL_FILE"; \
			else \
				echo "   [FAIL] $$test_file - Difference found."; \
				echo "          Input: $$INPUT_FILE"; \
				echo "          Diff output (Expected < vs Actual >):"; \
				diff -u --strip-trailing-cr "$$EXPECTED_FILE" "$$ACTUAL_FILE" | head -n 20; \
			fi; \
		done; \
	fi
endef

# Explicitly define targets and use the macro
test_ex1: $(RUN_DIR)/ex1
	$(call TEST_RECIPE,1,$(EX1_TEST_FILES))

test_ex2: $(RUN_DIR)/ex2
	$(call TEST_RECIPE,2,$(EX2_TEST_FILES))

# --- Utility Targets ---

.PHONY: clean
clean:
	@echo "Cleaning up generated files and directories..."
	@rm -rf $(RUN_DIR)
	@echo "Clean complete."