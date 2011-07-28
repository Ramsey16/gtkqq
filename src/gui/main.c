#include <gtk/gtk.h>
#include <stdlib.h>
#include <loginpanel.h>
#include <mainpanel.h>
#include <mainwindow.h>
#include <qq.h>
#include <log.h>
#include <gqqconfig.h>
#include <msgloop.h>

/*
 * Global
 */
QQInfo *info = NULL;
GQQConfig *cfg = NULL;

int main(int argc, char **argv)
{
	gtk_init(&argc, &argv);

	log_init();
	info = qq_init(NULL);
	if(info == NULL){
		return -1;
	}
    cfg = gqq_config_new(info);
    gqq_config_load_last(cfg);

    if(gqq_msgloop_start() == -1){
        g_error("Start message loop error! (%s, %d)", __FILE__, __LINE__);
        return -1;
    }

	GtkWidget *win = qq_mainwindow_new();
	gtk_widget_show_all(win);
	
	gtk_main();
	qq_logout(info, NULL);
    gqq_config_save(cfg);
    qq_finalize(info, NULL);
	return 0;
}
