int showcap, shownum, updrate;
char config_file_path[ML];

GtkWidget *gshowcap, *gshownum, *gupdrate, *dialog, 
*box,*filechooser_syslinuxpath, *btn_savesettings,*notebook, *colorsgrid, *dialog, *grid, *btn_cancel;


void on_btn_cancel_clicked(GtkWidget *widget, gpointer data)
{
	gtk_widget_destroy(GTK_WIDGET(data));
}

void readconf()
{
	//READ THE CONF
	char *home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		fprintf(stderr, "Error: HOME environment variable is not set.\n");
		exit(1);
	}

	snprintf(config_file_path, sizeof(config_file_path), "%s/.config/gxcapindicator.conf", home_dir);

	FILE *file = fopen(config_file_path, "r");
	if (file == NULL)
	{
		if (file == NULL)
		{
			FILE *default_conf = fopen("/etc/gxcapindicator.conf", "r");
			if (default_conf == NULL)
			{
				fprintf(stderr, "Error: could not open default configuration file /etc/gxcapindicator.conf, please reinstall the program or put a config file in ~/.config/gxcapindicator.conf.\n");
				exit(1);
			}

			file = fopen(config_file_path, "w");
			if (file == NULL)
			{
				fprintf(stderr, "Error: could not create %s for writing.\n", config_file_path);
				exit(1);
			}

			int ch;
			while ((ch = fgetc(default_conf)) != EOF)
			{
				fputc(ch, file);
			}
			fclose(default_conf);
			printf("Default configuration file copied to %s.\n", config_file_path);
		}
		else
		{
			fclose(file);
			printf("%s exists and can be read.\n", config_file_path);
		}
	}

	char line[ML];
	if (file != NULL)
	{
		// Read each line from the file and parse the variable assignments
		while (fgets(line, ML, file) != NULL)
		{
			char *name = strtok(line, "=");
			char *value_str = strtok(NULL, "=");

			if (name != NULL && value_str != NULL)
			{
				if (strcmp(name, "showcap") == 0) 
					showcap = atoi(value_str);
				else if (strcmp(name, "shownum") == 0)
					shownum = atoi(value_str);
				else if (strcmp(name, "updrate") == 0)
					updrate = atoi(value_str);
			}
		}
		fclose(file);
	}
	else
	{
		printf("Error opening file");
	}
}

void reset(GtkWidget *widget)
{
	readconf();

	if (!showcap)
	{
		app_indicator_set_status(indicator, APP_INDICATOR_STATUS_PASSIVE);
	}
	else
	{
		app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
	}

	if (!shownum)
	{
		app_indicator_set_status(indicator2, APP_INDICATOR_STATUS_PASSIVE);
	}
	else
	{
		app_indicator_set_status(indicator2, APP_INDICATOR_STATUS_ACTIVE);
	}

}

void saveconfig()
{
	const gchar *cshowcap = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowcap)) ? "1" : "0";
	const gchar *cshownum = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshownum)) ? "1" : "0";
	const gchar *cupdrate = gtk_entry_get_text(GTK_ENTRY(gupdrate));

	if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowcap)) && !gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshownum)))
	{
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ERROR: Invalid Situation\n\nIs not possible to have both 'shownum' and 'showcap' as FALSE");
		gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return;
	}

	FILE *output;
	output = fopen(config_file_path, "w");
	if (output == NULL)
	{
		g_printerr("\033[1;31mERROR\033[0m: Process running but config does not exist, did you moved the file?\n");
		gtk_main_quit();
	}
	else
	{
		fprintf(output, "[GXCapIndicator Configuration File, place default on /etc/gxcapindicator.conf]\n");
		fprintf(output, "showcap=%s\n", cshowcap);
		fprintf(output, "shownum=%s\n", cshownum);

		if (strlen(cupdrate) > 0)
		{
			fprintf(output, "updrate=%s\n", cupdrate);
		}
		else
		{
			fprintf(output, "updrate=1\n");
		}
		fclose(output);
	}
	reset(window);
	gtk_widget_destroy(GTK_WIDGET(dialog));
}

void on_preferences(GtkWidget *button, gpointer data)
{
	gtk_init(NULL, NULL);
		dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
		gtk_window_set_title(GTK_WINDOW(dialog), "GXCapIndicator Settings");

		theme = gtk_icon_theme_get_default();
		info = gtk_icon_theme_lookup_icon(theme, "keyboard-caps-enabled", 48, 0);
		if (info != NULL)
		{
			icon = gtk_icon_info_load_icon(info, NULL);
			gtk_window_set_icon(GTK_WINDOW(dialog), icon);
			g_object_unref(icon);
			g_object_unref(info);
		}
		g_signal_connect(dialog, "destroy", G_CALLBACK(gtk_main_quit), NULL);
		gtk_container_set_border_width(GTK_CONTAINER(dialog), 5);

			grid = gtk_grid_new();
		gtk_container_add(GTK_CONTAINER(dialog), grid);
		gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
		gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

			gshowcap = gtk_check_button_new();
			gshownum = gtk_check_button_new();
			gupdrate = gtk_entry_new();

		btn_cancel = gtk_button_new_with_label("cancel");
		btn_savesettings = gtk_button_new_with_label("save");

		gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Show Caps Lock:"), 0, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), gshowcap, 1, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Show Num Lock:"), 0, 1, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), gshownum, 1, 1, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Update rate (seconds):"), 0, 2, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), gupdrate, 1, 2, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), btn_cancel, 0, 6, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), btn_savesettings, 1, 6, 1, 1);

		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowcap), !!showcap);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshownum), !!shownum);

		char buffer[32];
		snprintf(buffer, sizeof(buffer), "%d", updrate);
		gtk_entry_set_text(GTK_ENTRY(gupdrate), buffer);

			g_signal_connect(btn_cancel, "clicked", G_CALLBACK(on_btn_cancel_clicked), dialog);
			g_signal_connect(btn_savesettings, "clicked", G_CALLBACK(saveconfig), dialog);
	gtk_widget_show_all(dialog);
	gtk_main();
}