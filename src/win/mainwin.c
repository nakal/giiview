
#include "mainwin.h"

static gboolean mainwin_delete_event(GtkWidget *widget, GdkEvent  *event,
	gpointer data);
static void mainwin_destroy(GtkWidget *widget, gpointer data);


GtkWidget *mainwin_create(GtkApplication *app, const char *app_version)
{
	GtkWidget *win;
	gchar *title;

	win = gtk_application_window_new(app);

	title = g_strdup_printf("giiview - %s", app_version);
	gtk_window_set_title(GTK_WINDOW(win), title);
	g_free(title);

	g_signal_connect (win, "delete-event",
			G_CALLBACK (mainwin_delete_event), NULL);
	g_signal_connect (win, "destroy",
			G_CALLBACK (mainwin_destroy), NULL);

	gtk_widget_show(win);

	return win;
}

static gboolean mainwin_delete_event(GtkWidget *widget, GdkEvent  *event,
	gpointer data)
{
	return FALSE;
}

static void mainwin_destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}
