CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0 appindicator3-0.1` -Wall -lpthread -lX11
LIBS = `pkg-config --libs gtk+-3.0 appindicator3-0.1` -Wall -lpthread -lX11

SRC = gxcapindicator.c
OBJ = $(SRC:.c=.o)
EXE = gxcapindicator

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

debug: $(SRC)
	$(CC) $(CFLAGS) -g $^ -o debug $(LIBS)

test: $(EXE)
	./$(EXE)

clean:
	rm -f $(OBJ) $(EXE) debug

install: $(EXE)
	install -Dm755 $(EXE) /usr/bin/$(EXE)
	install -Dm755 gxcapindicator.desktop /usr/share/applications/gxcapindicator.desktop
	install -Dm644 gxcapindicator.conf /etc/gxcapindicator.conf
	install -Dm644 icons/keyboard-caps-disabled.svg /usr/share/icons/hicolor/32x32/devices/keyboard-caps-disabled.svg
	install -Dm644 icons/keyboard-caps-enabled.svg /usr/share/icons/hicolor/32x32/devices/keyboard-caps-enabled.svg
	install -Dm644 icons/keyboard-num-disabled.svg /usr/share/icons/hicolor/32x32/devices/keyboard-num-disabled.svg
	install -Dm644 icons/keyboard-num-enabled.svg /usr/share/icons/hicolor/32x32/devices/keyboard-num-enabled.svg

uninstall:
	rm -f /usr/bin/$(EXE)
	rm -f /usr/share/applications/gxcapindicator.desktop
	rm -f /etc/gxcapindicator.conf
	rm -f /usr/share/icons/hicolor/32x32/devices/keyboard-caps-disabled.svg
	rm -f /usr/share/icons/hicolor/32x32/devices/keyboard-caps-enabled.svg
	rm -f /usr/share/icons/hicolor/32x32/devices/keyboard-num-disabled.svg
	rm -f /usr/share/icons/hicolor/32x32/devices/keyboard-num-enabled.svg
