/*  GNOME Clipboard Daemon
 *  Copyright (C) 2003, 2006  Hongli Lai <h.lai@chello.nl>
 *
 *  Release under the GNU General Public License.
 */

#include "selection-data-list.h"


SelectionDataEntry *
selection_data_entry_new (gchar *name, GtkSelectionData *data)
{
	SelectionDataEntry *entry;

	g_return_val_if_fail (name != NULL, NULL);

	entry = (SelectionDataEntry *) g_new0 (SelectionDataEntry, 1);
	entry->name = name;
	entry->data = data;
	return entry;
}


void
selection_data_entry_free (SelectionDataEntry *entry)
{
	g_return_if_fail (entry != NULL);

	g_free (entry->name);
	if (entry->data) gtk_selection_data_free (entry->data);
	g_free (entry);
}


SelectionDataList *
selection_data_list_new ()
{
	SelectionDataList *list;

	list = (SelectionDataList *) g_new0 (SelectionDataList, 1);
	return list;
}


void
selection_data_list_free (SelectionDataList *list)
{
	GList *elist;

	g_return_if_fail (list != NULL);

	for (elist = list->entries; elist; elist = elist->next)
		selection_data_entry_free ((SelectionDataEntry *) elist->data);
	g_list_free (list->entries);
	g_free (list);
}


void
selection_data_list_add (SelectionDataList *list, gchar *atom_name, GtkSelectionData *data)
{
	SelectionDataEntry *entry;

	g_return_if_fail (list != NULL);
	g_return_if_fail (atom_name != NULL);

	entry = selection_data_entry_new (atom_name, data);
	list->entries = g_list_append (list->entries, entry);
}


GtkTargetEntry *
selection_data_list_make_targets (SelectionDataList *list, guint *n_targets)
{
	GList *elist;
	GtkTargetEntry *entries;
	guint i = 0;

	g_return_val_if_fail (list != NULL, NULL);
	g_return_val_if_fail (n_targets != NULL, NULL);

	entries = (GtkTargetEntry *) g_new0 (GtkTargetEntry, g_list_length (list->entries));
	for (elist = list->entries; elist; elist = elist->next)
	{
		SelectionDataEntry *data_entry = (SelectionDataEntry *) elist->data;

		entries[i].target = data_entry->name;
		entries[i].info = (guint) GPOINTER_TO_INT (data_entry);
		if (data_entry->data)
			entries[i].flags = (guint) gtk_selection_data_get_data_type(data_entry->data);
		i++;
	}
	*n_targets = i;

	return entries;
}
