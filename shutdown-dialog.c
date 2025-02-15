// vim: et:ts=4:sw=4

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logout.h"
#include "config.h"

void on_window_show(GtkWidget *w, gpointer data);
gboolean on_key(GtkWidget *widget, GdkEventKey *event, gpointer data);
void on_click(GtkWidget *widget, gpointer data);

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window, *btn_close, *btn_poweroff, *btn_reboot, *btn_suspend, *btn_hibernate, *btn_logout;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_resource("/shutdown-dialog/ui.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window")); 
    btn_close = GTK_WIDGET(gtk_builder_get_object(builder, "close-button"));
    btn_poweroff = GTK_WIDGET(gtk_builder_get_object(builder, "poweroff-button"));
    btn_reboot = GTK_WIDGET(gtk_builder_get_object(builder, "reboot-button"));
    btn_suspend = GTK_WIDGET(gtk_builder_get_object(builder, "suspend-button"));
    btn_hibernate = GTK_WIDGET(gtk_builder_get_object(builder, "hibernate-button"));
    btn_logout = GTK_WIDGET(gtk_builder_get_object(builder, "logout-button"));

    g_signal_connect(window, "show", G_CALLBACK(on_window_show), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(btn_close, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(btn_poweroff, "clicked", G_CALLBACK(on_click), NULL);
    g_signal_connect(btn_reboot, "clicked", G_CALLBACK(on_click), NULL);
    g_signal_connect(btn_suspend, "clicked", G_CALLBACK(on_click), NULL);
    g_signal_connect(btn_hibernate, "clicked", G_CALLBACK(on_click), NULL);
    g_signal_connect(btn_logout, "clicked", G_CALLBACK(on_click), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

void on_window_show(GtkWidget *w, gpointer data) {
    GdkWindow *window = gtk_widget_get_window(w);
    GdkDisplay *display;
    GdkSeat *seat;
    int timeout = 0;

    display = gdk_display_get_default();
    seat = gdk_display_get_default_seat(display);

    while (gdk_seat_grab(seat, window, GDK_SEAT_CAPABILITY_KEYBOARD, TRUE, NULL, NULL, NULL, NULL) != GDK_GRAB_SUCCESS && ++timeout < 10) {
        usleep(50000);
    }
}

gboolean on_key(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_Escape || event->keyval == EXIT_HOTKEY) {
        gtk_main_quit();
        return TRUE;
    }

    // handle commands

    char *cmd = NULL;

    switch (event->keyval) {
        case POWEROFF_HOTKEY:
            cmd = POWEROFF_CMD;
            break;
        case REBOOT_HOTKEY:
            cmd = REBOOT_CMD;
            break;
        case SUSPEND_HOTKEY:
            cmd = SUSPEND_CMD;
            break;
        case HIBERNATE_HOTKEY:
            cmd = HIBERNATE_CMD;
            break;
        case LOGOUT_HOTKEY:
            cmd = LOGOUT_CMD;
            break;
    }

    if (cmd) {
        system(cmd);
        gtk_main_quit();
        return TRUE;
    }

    return FALSE;
}

void on_click(GtkWidget *widget, gpointer data) {
    const char *name = gtk_widget_get_name(widget);
    char *cmd = NULL;

    printf("Executing %s\n", name);
    if (!strcmp(name, "poweroff")) {
        cmd = POWEROFF_CMD;
    } else if (!strcmp(name, "reboot")) {
        cmd = REBOOT_CMD;
    } else if (!strcmp(name, "suspend")) {
        cmd = SUSPEND_CMD;
    } else if (!strcmp(name, "hibernate")) {
        cmd = HIBERNATE_CMD;
    } else if (!strcmp(name, "logout")) {
        cmd = LOGOUT_CMD;
    }

    if (cmd) system(cmd);

    gtk_main_quit();
}
