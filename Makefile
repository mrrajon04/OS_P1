# Variables
TARGET_EXEC ?= myprogram
TARGET_TEST ?= test-lab

BUILD_DIR ?= build
TEST_DIR ?= tests
SRC_DIR ?= src
EXE_DIR ?= app

# Source Files
SRCS := $(shell find $(SRC_DIR) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

TEST_SRCS := $(shell find $(TEST_DIR) -name *.c)
TEST_OBJS := $(TEST_SRCS:%=$(BUILD_DIR)/%.o)
TEST_DEPS := $(TEST_OBJS:.o=.d)

EXE_SRCS := $(shell find $(EXE_DIR) -name *.c)
EXE_OBJS := $(EXE_SRCS:%=$(BUILD_DIR)/%.o)
EXE_DEPS := $(EXE_OBJS:.o=.d)

# Compilation Flags
CFLAGS ?= -Wall -Wextra -fno-omit-frame-pointer -fsanitize=address -g -MMD -MP
LDFLAGS ?= -pthread -lreadline

# Default Targets
all: $(TARGET_EXEC) $(TARGET_TEST)

# Build the Main Executable
$(TARGET_EXEC): $(OBJS) $(EXE_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(EXE_OBJS) -o $@ $(LDFLAGS)

# Build the Test Executable
$(TARGET_TEST): $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_OBJS) -o $@ $(LDFLAGS)

# Rule to Build Object Files
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Run Tests
check: $(TARGET_TEST)
	ASAN_OPTIONS=detect_leaks=1 ./$<

# Clean Up
.PHONY: clean
clean:
	$(RM) -rf $(BUILD_DIR) $(TARGET_EXEC) $(TARGET_TEST)

# Install Dependencies for Git Send-Email
.PHONY: install-deps
install-deps:
	sudo apt-get update -y
	sudo apt-get install -y libio-socket-ssl-perl libmime-tools-perl

# Include Dependency Files
-include $(DEPS) $(TEST_DEPS) $(EXE_DEPS)
