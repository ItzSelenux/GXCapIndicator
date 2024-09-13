#include "gxcapindicator.h"

int main(int argc, char *argv[])
{
	readconf();
	gtk_init(&argc, &argv);
	create_window();
}