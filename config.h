#include <gtk/gtk.h>

#define POWEROFF_CMD "poweroff"
#define REBOOT_CMD "reboot"
#define SUSPEND_CMD "systemctl suspend"
#define HIBERNATE_CMD "systemctl hibernate"
#define LOGOUT_CMD "loginctl terminate-session $XDG_SESSION_ID"

// for a list of keys see gdk/gdkkeysyms.h
#define POWEROFF_HOTKEY GDK_KEY_p
#define REBOOT_HOTKEY GDK_KEY_r
#define SUSPEND_HOTKEY GDK_KEY_s
#define HIBERNATE_HOTKEY GDK_KEY_h
#define LOGOUT_HOTKEY GDK_KEY_l
#define EXIT_HOTKEY GDK_KEY_q

