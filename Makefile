# Detect OS
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

# Version handling
VERSION ?= 0.0.0
VERSION_DEFINE = -DVERSION=\"$(VERSION)\"

# Compiler settings
ifeq ($(UNAME_S),Darwin)
    CC = clang
    CFLAGS = -Wall -Wextra -O2 $(VERSION_DEFINE)
    LDFLAGS = 
    INSTALL = install
    INSTALL_FLAGS = -m 755
    MAN_INSTALL_FLAGS = -m 644
else
    CC = gcc
    CFLAGS = -Wall -Wextra -O2 $(VERSION_DEFINE)
    LDFLAGS = 
    INSTALL = install
    INSTALL_FLAGS = -m 755
    MAN_INSTALL_FLAGS = -m 644
endif

# Directories
SRC_DIR = src
APP_DIR = $(SRC_DIR)/app
INSTALLER_DIR = $(SRC_DIR)/installer
BIN_DIR = bin
RESOURCES_DIR = resources

# Targets
APP_TARGET = $(BIN_DIR)/lgbt
INSTALLER_TARGET = $(BIN_DIR)/installer

# Installation paths
ifeq ($(UNAME_S),Darwin)
    INSTALL_PREFIX ?= /usr/local
else
    INSTALL_PREFIX ?= /usr
endif

BINDIR = $(INSTALL_PREFIX)/bin
MANDIR = $(INSTALL_PREFIX)/share/man/man1

# Platform-specific settings
ifeq ($(UNAME_S),Darwin)
    # macOS specific settings
    CFLAGS += -D_DARWIN_C_SOURCE
    MANDIR = $(INSTALL_PREFIX)/share/man/man1
else ifeq ($(UNAME_S),Linux)
    # Linux specific settings
    CFLAGS += -D_GNU_SOURCE
    MANDIR = $(INSTALL_PREFIX)/share/man/man1
else ifeq ($(UNAME_S),MINGW32_NT-6.1)
    # Windows specific settings
    CFLAGS += -D_WIN32
    APP_TARGET := $(APP_TARGET).exe
    INSTALLER_TARGET := $(INSTALLER_TARGET).exe
    BINDIR = $(INSTALL_PREFIX)/bin
    MANDIR = $(INSTALL_PREFIX)/share/man/man1
endif

.PHONY: all clean install uninstall

all: $(APP_TARGET) $(INSTALLER_TARGET)

$(APP_TARGET): $(APP_DIR)/main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(INSTALLER_TARGET): $(INSTALLER_DIR)/main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -rf $(BIN_DIR)

install: all
	$(INSTALL) -d $(DESTDIR)$(BINDIR)
	$(INSTALL) $(INSTALL_FLAGS) $(APP_TARGET) $(DESTDIR)$(BINDIR)
	$(INSTALL) -d $(DESTDIR)$(MANDIR)
	$(INSTALL) $(MAN_INSTALL_FLAGS) $(RESOURCES_DIR)/lgbt.1 $(DESTDIR)$(MANDIR)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/lgbt
	rm -f $(DESTDIR)$(MANDIR)/lgbt.1

# Development targets
dev: CFLAGS += -g -DDEBUG
dev: all

# Help target
help:
	@echo "Available targets:"
	@echo "  all        - Build both the main program and installer (default)"
	@echo "  clean      - Remove built binaries"
	@echo "  install    - Install the program and man page"
	@echo "  uninstall  - Remove installed files"
	@echo "  dev        - Build with debug symbols"
	@echo ""
	@echo "Variables:"
	@echo "  VERSION    - Set version number (e.g., make VERSION=1.0.0)"
	@echo "  INSTALL_PREFIX - Installation prefix (default: /usr or /usr/local on macOS)"
	@echo "  CC         - C compiler (default: gcc or clang on macOS)"
	@echo "  CFLAGS     - C compiler flags"
	@echo ""
	@echo "Platform: $(UNAME_S) $(UNAME_M)"
	@echo "Current version: $(VERSION)" 