#include <gtk/gtk.h>
#include <libayatana-appindicator/app-indicator.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>

#include <pthread.h>

#define ML 256

AppIndicator *indicator;
AppIndicator *indicator2;

GtkIconTheme *theme;
GtkIconInfo *info;
GdkPixbuf *icon;

GtkWidget *window, *traymenu, *traymenu_item1,*traymenu_item2, *traymenu_item3,*traymenu_item4,
	*traymenu2, *traymenu_item11,*traymenu_item12, *traymenu_item13, *traymenu_item14;

char *pver="1.0";

#include "settings.h"

static void quit_app(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

void *toggle_cap()
{
	Display *d;
	unsigned int state;

	d = XOpenDisplay(NULL);
	if (d == NULL)
	{
		fprintf(stderr, "can't open display\n");
	}

	XkbGetIndicatorState(d, XkbUseCoreKbd, &state);

	int capsLock = (state & 0x01) != 0;

	XkbLockModifiers(d, XkbUseCoreKbd, LockMask, capsLock ? 0 : LockMask);
	XCloseDisplay(d);
	return NULL;
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
			app_indicator_set_icon_full(indicator, "keyboard-caps-enabled", "Caps Lock: Disabled");
		}
		else
		{
			app_indicator_set_icon_full(indicator, "keyboard-caps-disabled", "Caps Lock: Enabled");
		}
		sleep(updrate);
	}
	XCloseDisplay(d);
	return NULL;
}

void *toggle_num()
{
	Display *d;
	unsigned int state;

	d = XOpenDisplay(NULL);
	if (d == NULL)
	{
		fprintf(stderr, "can't open display\n");
		return NULL;
	}

	XkbGetIndicatorState(d, XkbUseCoreKbd, &state);

	int numLock = (state & 0x02) != 0;

	XkbLockModifiers(d, XkbUseCoreKbd, Mod2Mask, numLock ? 0 : Mod2Mask);
	XCloseDisplay(d);
	return NULL;
}

void* check_num_lock(void* arg)
{
	Display *d;
	unsigned int n;
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
		n = (xkbState.locked_mods & Mod2Mask) ? 1 : 0;

		if (n)
		{
			app_indicator_set_icon_full(indicator2, "keyboard-num-enabled", "Num Lock: Enabled");
		}
		else
		{
			app_indicator_set_icon_full(indicator2, "keyboard-num-disabled", "Num Lock: Disabled");
		}
		sleep(updrate);
	}
	XCloseDisplay(d);
	return NULL;
}

void on_about(GtkMenuItem *menuitem, gpointer userdata)
{
	dialog = gtk_about_dialog_new();
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
		theme = gtk_icon_theme_get_default();
		info = gtk_icon_theme_lookup_icon(theme, "keyboard-caps-enabled", 48, 0);
		if (info != NULL)
		{
			icon = gtk_icon_info_load_icon(info, NULL);
			gtk_window_set_icon(GTK_WINDOW(dialog), icon);
			g_object_unref(icon);
			g_object_unref(info);
		}
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "GXCapIndicator");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Copyright © 2024 ItzSelenux");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "Simple Cap/Num lock indicator for X11 Tray");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), pver);
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "https://github.com/itzselenux/gxcapindicator");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog), "Project WebSite");
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog),GTK_LICENSE_GPL_3_0);
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(dialog),"keyboard-caps-enabled");

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}