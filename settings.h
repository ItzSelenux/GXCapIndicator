void create_num_indicator();
void create_cap_indicator();

void readconf()
{
	char *home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		g_warning("HOME environment variable is not set.");
		nohome = 1;
		return;
	}

	snprintf(config_file_path, sizeof(config_file_path), "%s/.config/gxcapindicator.conf", home_dir);

	FILE *file = fopen(config_file_path, "r");

	if (file == NULL)
	{
		file = fopen(config_file_path, "w");
		if (file == NULL)
		{
			g_warning("could not open %s for writing.", config_file_path);
			nohome = 1;
			return;
		}
		else
		{
			fclose(file);
			return;
		}
	}

	char line[ML];
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
			else if (strcmp(name, "vcapstate") == 0)
				vcapstate = atoi(value_str);
			else if (strcmp(name, "vnumstate") == 0)
				vnumstate = atoi(value_str);
		}
	}
	fclose(file);
}


void reset(GtkWidget *widget)
{
	readconf();
	app_indicator_set_status(capindicator, showcap ? APP_INDICATOR_STATUS_ACTIVE : APP_INDICATOR_STATUS_PASSIVE);
	app_indicator_set_status(numindicator, shownum ? APP_INDICATOR_STATUS_ACTIVE : APP_INDICATOR_STATUS_PASSIVE);

	if (showcap) 
	{
		create_cap_indicator();
		cleanup_thread(&cap_threadid, &cap_thread_active);
	}

	if (shownum) 
	{
		create_num_indicator();
		cleanup_thread(&num_threadid, &num_thread_active);
	}
}


void saveconfig()
{
	const gchar *cshowcap = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowcap)) ? "1" : "0";
	const gchar *cshownum = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshownum)) ? "1" : "0";
	const gchar *cupdrate = gtk_entry_get_text(GTK_ENTRY(gupdrate));
	const gchar *cvcapstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gcapstate)) ? "1" : "0";
	const gchar *cvnumstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gnumstate)) ? "1" : "0";

	if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowcap)) && !gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshownum)))
	{
		dialog = gtk_message_dialog_new(GTK_WINDOW(window),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_OK,
			"ERROR: Invalid Situation\n\nIs not possible to have both 'shownum' and 'showcap' as FALSE");
		gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

		info = gtk_icon_theme_lookup_icon(theme, "dialog-error", 48, 0);
		if (info != NULL)
		{
			icon = gtk_icon_info_load_icon(info, NULL);
			gtk_window_set_icon(GTK_WINDOW(dialog), icon);
			g_object_unref(icon);
			g_object_unref(info);
		}
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		return;
	}

	FILE *output;
	output = fopen(config_file_path, "w");
	if (output == NULL)
	{
		output = fopen(config_file_path, "w");
		if (output == NULL)
		{
			g_warning("could not open %s for writing.", config_file_path);
			nohome = 1;
			return;
		}
		else
		{
			fclose(output);
			return;
		}
	}
	else
	{
		fprintf(output, "[GXCapIndicator Configuration File]\n");
		fprintf(output, "showcap=%s\n", cshowcap);
		fprintf(output, "shownum=%s\n", cshownum);
		fprintf(output, "vcapstate=%s\n", cvcapstate);
		fprintf(output, "vnumstate=%s\n", cvnumstate);
		fprintf(output, "updrate=%s\n", strlen(cupdrate) > 0 ? cupdrate : "1");
		fclose(output);
	}
	reset(window);
	gtk_widget_destroy(GTK_WIDGET(dialog));
}