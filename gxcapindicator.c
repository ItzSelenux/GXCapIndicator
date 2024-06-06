#include "gxcapindicator.h"

int main(int argc, char *argv[])
{
	pthread_t thread_id;
	if (pthread_create(&thread_id, NULL, check_caps_lock, NULL) != 0)
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	gtk_init(&argc, &argv);

	// Tray Icon
	indicator = app_indicator_new("example-app-indicator", "gxcapindicator", APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
	app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);

	app_indicator_set_icon_full(indicator, "image-loading-symbolic", "Indicator Icon");

	traymenu = gtk_menu_new();
	traymenu_item3 = gtk_menu_item_new_with_label("Quit");
	gtk_menu_shell_append(GTK_MENU_SHELL(traymenu), traymenu_item3);
	gtk_widget_show_all(traymenu);
	app_indicator_set_menu(indicator, GTK_MENU(traymenu));

	g_signal_connect(G_OBJECT(traymenu_item3), "activate", G_CALLBACK(quit_app), NULL);

	gtk_main();

	pthread_cancel(thread_id);
	pthread_join(thread_id, NULL);

	return 0;
}
