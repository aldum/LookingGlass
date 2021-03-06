USE_DXGI ?= 1
USE_XCB  ?= 1

OUTPUT = looking-glass-host
EXT    =

CFLAGS  = -std=gnu99 -Wall -Werror
CFLAGS += -g -O3
CFLAGS += -I.
CFLAGS += -I../common

OBJS  = app.o

# if windows
ifdef OS
  CC      = gcc.exe
  LDFLAGS = -L./windows/dll -mwindows
  LIBS   += -lsetupapi
  OBJS   += windows/platform.o
  OBJS   += windows/windebug.o
  CFLAGS += -I../vendor/kvm-guest-drivers-windows
  EXT     = .exe

  ifeq ($(USE_DXGI), 1)
    CFLAGS += -DUSE_DXGI -DCOBJMACROS -DINITGUID
    LIBS   += -ld3d11 -ldxgi
    DLLS   += windows/dll/libd3d11.a
    OBJS   += windows/capture/dxgi.o
  endif
else
  CC    = gcc
  OBJS += linux/platform.o
  LIBS += -lpthread

  ifeq ($(USE_XCB), 1)
    CFLAGS += -DUSE_XCB
    LIBS   += -lxcb -lxcb-shm -lXfixes
    OBJS   += linux/capture/xcb.o
  endif
endif

all: $(OBJS) $(DLLS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(OUTPUT)$(EXT) $(OBJS) $(LIBS)

clean:
	rm -v $(OBJS) $(DLLS) $(OUTPUT)$(EXT)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.a: %.def
	dlltool --def $< --output-lib $@
