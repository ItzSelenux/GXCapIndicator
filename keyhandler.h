void *toggle_cap()
{
	XkbGetIndicatorState(d, XkbUseCoreKbd, &capstate);
	int capsLock = (capstate & 0x01) != 0;
	XkbLockModifiers(d, XkbUseCoreKbd, LockMask, capsLock ? 0 : LockMask);
	return NULL;
}

void *check_cap()
{
	unsigned n;
	XkbStateRec xkbState;

	while (1)
	{
		XkbGetState(d, XkbUseCoreKbd, &xkbState);
		n = (xkbState.locked_mods & LockMask) ? 1 : 0;
		const char *icon_name = n ? "keyboard-caps-enabled" : "keyboard-caps-disabled";
		const char *status_message = n ? "Caps Lock: Enabled" : "Caps Lock: Disabled";
		app_indicator_set_icon_full(capindicator, icon_name, status_message);
		app_indicator_set_title(capindicator, status_message);
		sleep(updrate);
	}
	return NULL;
}

void *toggle_num()
{
	XkbGetIndicatorState(d, XkbUseCoreKbd, &numstate);
	int numLock = (numstate & 0x02) != 0;
	XkbLockModifiers(d, XkbUseCoreKbd, Mod2Mask, numLock ? 0 : Mod2Mask);
	return NULL;
}

void *check_num(void *arg)
{
	unsigned int n;
	XkbStateRec xkbState;

	while (1)
	{
		XkbGetState(d, XkbUseCoreKbd, &xkbState);
		n = (xkbState.locked_mods & Mod2Mask) ? 1 : 0;
		const char *icon_name = n ? "keyboard-num-enabled" : "keyboard-num-disabled";
		const char *status_message = n ? "Num Lock: Enabled" : "Num Lock: Disabled";
		app_indicator_set_icon_full(numindicator, icon_name, status_message);
		app_indicator_set_title(numindicator, status_message);
		sleep(updrate);
	}
	return NULL;
}