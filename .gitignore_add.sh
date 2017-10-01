#! /bin/sh

FILE=./.gitignore
cat $FILE > $FILE.save
#git status | grep '#[^ ]' | sed -e "s/^#\t//" >> $FILE
list=`git status | sed -n 's/^[^ ]*$/\0/p' | sed -n 's/\s//p' | sed 's/#//'`
title=1
if [ -z "$list" ] ; then
	title=
fi
for l in $list ; do
	if [ -z `cat $FILE | grep -o "^$l$"` ] ; then
	    if [ $title = 1 ] ; then
		    echo >> $FILE
		    d=`date`
		    echo "#$d" >> $FILE
		    echo "#" >> $FILE
	    fi
	    echo ${l} >> $FILE
	    title=
	fi
done
