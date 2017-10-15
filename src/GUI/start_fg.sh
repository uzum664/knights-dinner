#!/bin/sh

PROJECT_PATH=`dirs -l`
PROJECT_PATH=${PROJECT_PATH}/../..
#WIDGETS_PATH=$PROJECT_PATH/src/GUI/widgets
#LIBSWIDGETS_PATH=$WIDGETS_PATH/.libs
LIBGLADE_MODULE_PATH="$LIBSWIDGETS_PATH"
export LIBGLADE_MODULE_PATH

START=uniset2-start.sh
#strace
extparam="$*"
jmake && GTK2_RC_FILES= LC_NUMERIC=C LANG=ru_RU.UTF-8 ./knights-gui $extparam || GTK2_RC_FILES= LC_NUMERIC=C gdb --args ./.libs/lt-knights-gui $extparam
