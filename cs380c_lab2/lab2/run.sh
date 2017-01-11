#!/usr/bin/env bash
THREE_ADDR_TO_C_TRANSLATOR=../../cs380c_lab1/lab1/run.sh

opt=0
for option in $*
do
	pos=`expr index "$option" =`
	argument=${option:1:pos-2}
	value=${option:pos}
	if [ $argument = "backend" ]
	then
		if  [ $value = "c" ]
		then	
		    if [ $opt = 0 ]
		    then
			../../cs380c_lab1/lab1/run.sh
		    elif [ $opt = 11 ]
		    then
			$(cd `dirname $0`; pwd)/SCP_gen 3addr | ${THREE_ADDR_TO_C_TRANSLATOR}
		    elif [ $opt = 12 ]
		    then
			$(cd `dirname $0`; pwd)/DSE_gen 3addr | ${THREE_ADDR_TO_C_TRANSLATOR}
		    fi
		elif [ $value = "cfg" ]
		then
		    if [ $opt = 0 ]
		    then
			$(cd `dirname $0`; pwd)/CFG_gen
		    elif [ $opt = 11 ]
		    then
			$(cd `dirname $0`; pwd)/SCP_gen cfg
		    elif [ $opt = 12 ]
		    then
			$(cd `dirname $0`; pwd)/DSE_gen cfg
		    fi
		elif [ $value = "3addr" ]
		then
	      if [ $opt = 0 ]
		    then
			echo 1
		    elif [ $opt = 11 ]
		    then
			$(cd `dirname $0`; pwd)/SCP_gen 3addr
		    elif [ $opt = 12 ]
		    then
			$(cd `dirname $0`; pwd)/DSE_gen 3addr
		    fi
		elif [ $value = "rep" ]
		then
		    if [ $opt = 0 ]
		    then
			echo 1
		    elif [ $opt = 11 ]
		    then
			$(cd `dirname $0`; pwd)/SCP_gen rep
		    elif [ $opt = 12 ]
		    then
			$(cd `dirname $0`; pwd)/DSE_gen rep
		    fi
		fi
	elif [ $argument = "opt" ]
	then
		if [ $value = "scp" ]
		then
			opt=11
		elif [ $value = "dse" ]
		then
			opt=12
		fi		
	fi
done
