/*  GNOME Clipboard Daemon
 *  Copyright (C) 2003, 2006  Hongli Lai <h.lai@chello.nl>
 *
 *  Release under the GNU General Public License.
 */

#include <gtk/gtk.h>
#include "clipboard-daemon.h"

int
main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	clipboard_daemon_start ();
	gtk_main ();
	return 0;
}
