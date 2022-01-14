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
