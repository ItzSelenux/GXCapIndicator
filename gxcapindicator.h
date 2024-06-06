#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>

#include <pthread.h>

#define ML 256

AppIndicator *indicator;

GtkIconTheme *theme;
GtkIconInfo *info;
GdkPixbuf *icon;

GtkWidget *window;
GtkWidget *traymenu;
GtkWidget *traymenu_item3;


static void quit_app(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

void* check_caps_lock(void* arg)
{
	Display *d;
	unsigned n;
	XkbStateRec xkbState;

	d = XOpenDisplay(NULL);
	if (d == NULL)
	{
		fprintf(stderr, "can't open display\n");
		return NULL;
	}

	while (1)
	{
		XkbGetState(d, XkbUseCoreKbd, &xkbState);
		n = (xkbState.locked_mods & LockMask) ? 1 : 0;
		if (n)
		{
			app_indicator_set_icon_full(indicator, "keyboard-caps-enabled", "Indicator Icon");
		}
		else
		{
			app_indicator_set_icon_full(indicator, "keyboard-caps-disabled", "Indicator Icon");
		}
		sleep(1);
	}
	XCloseDisplay(d);
	return NULL;
}
