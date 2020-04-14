/*  GNOME Clipboard Daemon
 *  Copyright (C) 2003, 2006  Hongli Lai <h.lai@chello.nl>
 *
 *  Release under the GNU General Public License.
 */

#ifndef _SELECTION_DATA_LIST_H_
#define _SELECTION_DATA_LIST_H_


#include <gtk/gtk.h>

/* Simple wrapper structures for saving clipboard data */


typedef struct _SelectionDataEntry SelectionDataEntry;
typedef struct _SelectionDataList SelectionDataList;


struct _SelectionDataEntry
{
	gchar *name;
	GtkSelectionData *data;
};


SelectionDataEntry *selection_data_entry_new (gchar *name, GtkSelectionData *data);
void selection_data_entry_free (SelectionDataEntry *entry);


struct _SelectionDataList
{
	GList *entries;
};


SelectionDataList *selection_data_list_new (void);
void selection_data_list_free (SelectionDataList *list);

void selection_data_list_add (SelectionDataList *list, gchar *atom_name, GtkSelectionData *data);
GtkTargetEntry *selection_data_list_make_targets (SelectionDataList *list, guint *n_targets);


#endif /* _SELECTION_DATA_LIST_H_ */
