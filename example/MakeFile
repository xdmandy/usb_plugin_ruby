LDFLAGS=-lrt -lpcap -lpthread
CPPFLAGS=-Wall -O0 -D _GNU_SOURCE
CFLAGS := $(CFLAGS)

all: usb_camera_plugin

%.o: %.cpp
	g++ $(CFLAGS) -c -o $@ $< $(CPPFLAGS)

usb_camera_plugin: usb_camera_plugin.o
	gcc usb_camera_plugin.o -shared -Wl,-soname,usb_camera_plugin.so.1 -o usb_camera_plugin.so.1.0.1 -lc

clean:
	rm -f usb_camera_plugin.so.* *.o
