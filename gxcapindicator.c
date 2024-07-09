#include "gxcapindicator.h"

int main(int argc, char *argv[])
{
	readconf();

	printf("num=%d cap=%d", shownum, showcap);
	pthread_t thread_id;
	if (pthread_create(&thread_id, NULL, check_caps_lock, NULL) != 0)
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	if (pthread_create(&thread_id, NULL, check_num_lock, NULL) != 0)
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	gtk_init(&argc, &argv);

		// Cap Tray Icon
		indicator = app_indicator_new("gxcapindicator-capslock", "GXCapIndicator", APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
		if (showcap)
		{
			app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
		}
		app_indicator_set_icon_full(indicator, "image-loading-symbolic", "Caps Lock");

		traymenu = gtk_menu_new();
		traymenu_item1 = gtk_menu_item_new_with_label("Toggle Caps Lock");
		traymenu_item2 = gtk_menu_item_new_with_label("Settings");
		traymenu_item3 = gtk_menu_item_new_with_label("About");
		traymenu_item4 = gtk_menu_item_new_with_label("Quit");
		gtk_menu_shell_append(GTK_MENU_SHELL(traymenu), traymenu_item1);
		gtk_menu_shell_append(GTK_MENU_SHELL(traymenu), traymenu_item2);
		gtk_menu_shell_append(GTK_MENU_SHELL(traymenu), traymenu_item3);
		gtk_menu_shell_append(GTK_MENU_SHELL(traymenu), traymenu_item4);
		gtk_widget_show_all(traymenu);
		app_indicator_set_menu(indicator, GTK_MENU(traymenu));


		// Num Tray Icon
		indicator2 = app_indicator_new("gxcapindicator-numlock","GXCapIndicator",APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
		if (shownum)
		{
			app_indicator_set_status(indicator2, APP_INDICATOR_STATUS_ACTIVE);
		}
		app_indicator_set_label(indicator2, "Indicator 2", NULL);
		app_indicator_set_icon_full(indicator2, "image-loading-symbolic", "Num Lock");

		traymenu2 = gtk_menu_new();
		traymenu_item11 = gtk_menu_item_new_with_label("Toggle Num Lock");
		traymenu_item12 = gtk_menu_item_new_with_label("Settings");
		traymenu_item13 = gtk_menu_item_new_with_label("About");
		traymenu_item14 = gtk_menu_item_new_with_label("Quit");
		gtk_menu_shell_append(GTK_MENU_SHELL(traymenu2), traymenu_item11);
		gtk_menu_shell_append(GTK_MENU_SHELL(traymenu2), traymenu_item12);
		gtk_menu_shell_append(GTK_MENU_SHELL(traymenu2), traymenu_item13);
		gtk_menu_shell_append(GTK_MENU_SHELL(traymenu2), traymenu_item14);
		gtk_widget_show_all(traymenu2);
		app_indicator_set_menu(indicator2, GTK_MENU(traymenu2));


	g_signal_connect(G_OBJECT(traymenu_item1), "activate", G_CALLBACK(toggle_cap), NULL);
	g_signal_connect(G_OBJECT(traymenu_item2), "activate", G_CALLBACK(on_preferences), NULL);
	g_signal_connect(G_OBJECT(traymenu_item3), "activate", G_CALLBACK(on_about), NULL);
	g_signal_connect(G_OBJECT(traymenu_item4), "activate", G_CALLBACK(quit_app), NULL);

	g_signal_connect(G_OBJECT(traymenu_item11), "activate", G_CALLBACK(toggle_num), NULL);
	g_signal_connect(G_OBJECT(traymenu_item12), "activate", G_CALLBACK(on_preferences), NULL);
	g_signal_connect(G_OBJECT(traymenu_item13), "activate", G_CALLBACK(on_about), NULL);
	g_signal_connect(G_OBJECT(traymenu_item14), "activate", G_CALLBACK(quit_app), NULL);

	gtk_main();

	pthread_cancel(thread_id);
	pthread_join(thread_id, NULL);

	return 0;
}
