#include <gtk/gtk.h>
#include <libayatana-appindicator/app-indicator.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>

#include <pthread.h>

#define ML 256

GtkIconTheme *theme;
GtkIconInfo *info;
GdkPixbuf *icon;

AppIndicator *capindicator, *numindicator;

GtkWidget *capmenu, *capmenu_item_toggle,*capmenu_item_settings, *capmenu_item_about, *capmenu_item_quit,
*nummenu, *nummenu_item_toggle,*nummenu_item_settings, *nummenu_item_about, *nummenu_item_quit,

*window, *gshowcap, *gshownum, *gupdrate, *dialog, *btn_savesettings, *grid, *btn_cancel;

Display *d;

pthread_t cap_threadid, num_threadid;

guint capstate, numstate, showcap=1, shownum=1, updrate=1, nohome=0, capvisible, numvisible;

gchar *pver="1.1", config_file_path[ML];

#include "threadmgr.h"
#include "keyhandler.h"
#include "settings.h"
#include "cfgmgr.h"
#include "mainwindow.h"