LDFLAGS=-lrt -lpcap -lpthread
CPPFLAGS=-Wall -O0 -D _GNU_SOURCE -I..
CFLAGS := $(CFLAGS)

all: usb_camera_plugin

%.o: %.cpp
	g++ $(CFLAGS) -c -o $@ $< $(CPPFLAGS)  # Use g++ instead of gcc

usb_camera_plugin: usb_camera_plugin.o
	g++ usb_camera_plugin.o -shared -Wl,-soname,usb_camera_plugin.so.1 -o usb_camera_plugin.so.1.0.1 -lc

clean:
	rm -f usb_camera_plugin.so.* *.o
