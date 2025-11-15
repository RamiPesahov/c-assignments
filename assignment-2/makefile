# --- Configuration ---
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
RUN_DIR = run
TARGETS = ex1 ex2 ex3

# Define all executables built in the run directory
EXECUTABLES = $(TARGETS:%=$(RUN_DIR)/%)

# --- Directory Setup and Compilation ---

# The default target builds all executables
.PHONY: all
all: $(EXECUTABLES)

# Rule to create the run directory
$(RUN_DIR):
	@mkdir -p $(RUN_DIR)
	@echo "Created output directory: $(RUN_DIR)"

# Generic rule to compile a .c file into an executable in the $(RUN_DIR)
# The '| $(RUN_DIR)' ensures the directory is created before compilation
$(RUN_DIR)/%: %.c | $(RUN_DIR)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) $< -o $@

# --- Testing Targets ---

# All test cases defined based on the directory structure
EX1_TEST_CASES = example1
EX2_TEST_CASES = example1
EX3_TEST_CASES = example1 example2 example3 example4 example5

# The main test target runs all specific test suites
.PHONY: test test_ex1 test_ex2 test_ex3

test: test_ex1 test_ex2 test_ex3
	@echo ""
	@echo "=========================================================="
	@echo "--- All test suites completed! Check output above. ---"
	@echo "=========================================================="

# Macro containing only the recipe (shell commands) for testing
# Usage: $(call TEST_RECIPE, executable_number, list_of_examples)
define TEST_RECIPE
	@echo ""
	@echo "--- Running Test Suite for ex$(1) ($(words $(2)) examples) ---"
	@for example in $(2); do \
	INPUT_FILE="tests/ex$(1)_$${example}_in.txt"; \
	EXPECTED_FILE="tests/ex$(1)_$${example}_out.txt"; \
	ACTUAL_FILE="$(RUN_DIR)/ex$(1)_$${example}_out.actual"; \
	echo "-> Testing case: $$example (Input: $${INPUT_FILE})"; \
	./$(RUN_DIR)/ex$(1) < $${INPUT_FILE} > $${ACTUAL_FILE}; \
	if diff -w -B --strip-trailing-cr $${EXPECTED_FILE} $${ACTUAL_FILE} > /dev/null; then \
		echo "   [PASS] $$example"; \
		rm -f $${ACTUAL_FILE}; \
	else \
		echo "   [FAIL] $$example - Difference found. Output comparison:"; \
		diff -u $${EXPECTED_FILE} $${ACTUAL_FILE}; \
	fi; \
	done
endef

# Explicitly define targets and use the macro for the recipe (fix for macro newline issue)
test_ex1: $(RUN_DIR)/ex1
	$(call TEST_RECIPE,1,$(EX1_TEST_CASES))

test_ex2: $(RUN_DIR)/ex2
	$(call TEST_RECIPE,2,$(EX2_TEST_CASES))

test_ex3: $(RUN_DIR)/ex3
	$(call TEST_RECIPE,3,$(EX3_TEST_CASES))


# --- Utility Targets ---

.PHONY: clean
clean:
	@echo "Cleaning up generated files and directories..."
	@rm -rf $(RUN_DIR)
	@echo "Clean complete."