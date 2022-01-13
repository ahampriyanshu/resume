#!/bin/bash

var=/home/priyanshu/Desktop/Dump/bash_scripting/third.sh

if [[ -e $var ]]
then
	echo "Files exists"
else
	echo "Doesn't exist"
fi

(( 2 > 1 ))
echo "Exit status is $?"

(( 2 - 2 ))
echo "Exit status is $?"

# !      files as a opeartor
# -r     true if user has permission to read
# -w     true if user has permission to write
# -x     true if user has permission to execute
# -f     true if given file is not a dir
# -s     true if given is not empty
# -e     "    "   if file exists

echo "$$"    # PID

for var in {0..5}
do
	echo "BASH_VERSINFO[$var] = ${BASH_VERSINFO[$var]}"
done

ROOT_UID=0

echo -n "YOU ARE: "

if [ "$UID" -eq "$ROOT_UID" ]
then
	echo "root, YOUR \$UID = $UID"
else
	echo "user, YOUR \UID = $UID"
fi

someFunction()
{
	echo "Function name is $FUNCNAME"
}

someFunction

echo "Outside, \$FUNCNAME = $FUNCNAME"

declare -r PI=3.1415926
printf "Value upto second decimal of PI is %1.2f\n" $PI
