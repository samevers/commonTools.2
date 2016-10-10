#!/bin/sh
#ls -lR > x
targetDir=$1
echo $targetDir
#ls -lR | perl allFiles.pl| awk '{print "cp "$0" "$targetDir"/"$0}' > copy.sh
ls -lR | perl allFiles.pl| awk '{print "cp "$0" ../../commonTools.2/src/"$0}' > copy.sh
