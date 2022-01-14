# Bash Crash Course

## Session 1
```bash
#!/bin/bash

# use chmod +x to give executable permission to run this script

echo "Hi there, SUP ?"   #this will print to the screen

echo "jkdsfjdsjf #fjdfjklsd"

echo fdsjfsdjlkf #jvjkdflksdfkjl

name=tea

echo "the word is $name conatains ${#name} chars"

echo $(( 2#111 ))      #count len of string

echo "Hey there"; echo "you there "   #terminating the command

var=1

if [ "$var" -gt 0 ]; then echo "YES"; else echo "NO"
fi    #if-else loop in bash


# cp -R /path/to/source/ .  command to copy some content to the current folder

colors="red green blue"

echo $colors

for col in $colors
do                                   #for and do loop in bash 
	echo $col
done


for col in "$colors"
do
	echo $col	#for and do loop in bash 
done


for col in '$colors'
do
	echo $col	#for and do loop in bash 
done


let "y=((x=20, 10/2))"
echo $y

var=DSLCoNnEctiOn
echo ${var,}  
echo ${var,,}
echo ${var^}
echo ${var^^}

echo "\"Linux is awesome\""

# ls --help | grep "\-l"    to use "" in grep 


let val=500/2
val2=`echo $val`
echo $val2


var=20

if [ "$var" -gt 15 ]
then :                       #null operator
else
	echo $var
fi	

# touch file.ext                       to create a new file

# echo "something new" > file.ext      to append to the empty file

# echo "somrthing newer" >> file.ext   to apppend to a file with some existing text

# : > file.txt                         to clean all the contents of a file

# : >> file.txt                        to create a file with fail-save option

var=10

if [ "$var" != 0 ]
then
	echo "NOT"
else
	echo "YES"
fi

let var=100*10
let var2=100**3

echo "$var  $var2"

# rm filename*       deletes everything that starts with filename

var=10

echo $(( var2 = var1<20?1:0))

colors=(red green blue)        # an array in bash

var=1
(var=2;)               # var = 1

echo \${test1,test2,test3}\$

echo {1..10}      # loop

var1=1
var2=2

{
var1=11
var2=12           # updated values will be 11 and 12
}

# ||              OR 
# &&              AND

# - + % /          same as in any other programing language

# cd ~             home directory

echo ~+
echo ~-

unset var   # unset var duh..
```

## Session 2
```bash
"""
read var                   # to read input
echo $var
"""

for var in 1 2 3
do 
	echo $var
done

echo $?   #return exit value

#  $#   no of arg passed

"""
read var

if [ "$var" -gt 0 ]
then
	if [ "$var" -lt 1000**1000 ]
	then
		if [ "$var" -gt 1]
			echo "Between 1 and 10"
		fi
	fi
elif [ "$var" -eq 0 ]
	echo "Zero it is"
else
	echo "It is a neg"
fi
"""

```

## Session 3
```bash
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

```