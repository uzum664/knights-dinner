#!/bin/sh

PROJECT_PATH=`dirs -l`
PROJECT_PATH=${PROJECT_PATH}/../..
WIDGETS_PATH=$PROJECT_PATH/src/GUI/widgets
LIBSWIDGETS_PATH=$WIDGETS_PATH/.libs

GLADE_CATALOG_PATH="$WIDGETS_PATH"
GLADE_MODULE_PATH="$LIBSWIDGETS_PATH"
export GLADE_CATALOG_PATH
export GLADE_MODULE_PATH

#GTK2_RC_FILES=theme/gtkrc
glade-3 gui.glade 1>/dev/null 2>/dev/null && exit 0 &
#gdb --args glade-3 gui.glade
