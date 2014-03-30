
#include <stdlib.h>

#include "../win/mainwin.h"

const char GIIVIEW_VERSION[] = "1.0.0";

int main(int argc, char *argv[])
{
	GtkApplication *app;
	GtkWidget *win;

	gtk_init(&argc, &argv);

	app = gtk_application_new("github.nakal.giiview",
		G_APPLICATION_NON_UNIQUE);
	g_application_register(G_APPLICATION(app), g_cancellable_new(),
		NULL);

	win = mainwin_create(app, GIIVIEW_VERSION);
	gtk_application_add_window(app, GTK_WINDOW(win));

	gtk_main();
	exit(0);
}
