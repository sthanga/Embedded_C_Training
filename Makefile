TOOLCHAIN_SYSROOT = /home/skthanga/nxp/nxpsetup/newsetup/sysroots/aarch64-thales-linux
INCLUDE_DIR = $(TOOLCHAIN_SYSROOT)/usr/include
LIB_DIR = $(TOOLCHAIN_SYSROOT)/usr/lib
#CROSS_COMPILE = aarch64-linux-gnu-
#CC = $(CROSS_COMPILE)gcc

CFLAGS = --sysroot=$(TOOLCHAIN_SYSROOT) -I$(INCLUDE_DIR)
LDFLAGS = --sysroot=$(TOOLCHAIN_SYSROOT) -L$(LIB_DIR)

TARGET = hostcpuStateMachine
SRC = hostcpuStateMachine.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC)
clean:
	rm -f $(TARGET)

