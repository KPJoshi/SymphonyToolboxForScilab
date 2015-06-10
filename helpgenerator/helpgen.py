#! /usr/bin/env python3

import sys #for getting command line argument

#the section the parser is in
nonesec=-1
descsec=0
argsec=1
retsec=2
exsec=3
autsec=4

#check no. of args
if len(sys.argv)!=2:
	print("Error: Expected 1 argument, got",len(sys.argv)-1)
	exit(1)

#get strings
templateStrings=open("template.txt").read().split("SPLITHERE")

#open file
datfile=open(sys.argv[1])

#initially not in a function specifier
section=nonesec

#infinite loop
while True:
	line=datfile.readline() #get the line, including end of line
	if not line: #if at eof, then line is completely empty, without even a \n
		break #break at eof
	line=line.strip() #now strip it of the \n
	if line=="" or line[0]=='#':
		continue #ignore comments (lines starting with #) and empty lines
	if line=="function":
		if section!=nonesec:
			print("Parse error.")
			exit(1)
		section=descsec
		while True:
			func=datfile.readline().strip() #get the function
			if func[0]!='#':
				break
		funcname=(func.split("("))[0] #and just the name
		while True:
			purpose=datfile.readline().strip() #get short function description
			if purpose[0]!='#':
				break
		outfile=open(funcname+".xml","w") #open output file
		outfile.write(templateStrings[0].replace("FUNNAME",funcname).replace("PURPOSE",purpose).replace("FUNFULL",func)) #load first part of template
	elif line=="args":
		if section!=descsec:
			print("Parse error.")
			exit(1)
		section=argsec
		outfile.write(templateStrings[1])
		hasargs=True
		outfile.write("\t\t<variablelist>\n")
	elif line=="noargs":
		if section!=descsec:
			print("Parse error.")
			exit(1)
		section=argsec
		outfile.write(templateStrings[1])
		hasargs=False
	elif line=="return":
		if section!=argsec:
			print("Parse error.")
			exit(1)
		section=retsec
		if(hasargs):
			outfile.write("\t\t</variablelist>\n")
		else:
			outfile.write("\t\t<para>This function takes no arguments</para>\n")
		outfile.write(templateStrings[2])
	elif line=="examples":
		if section!=retsec:
			print("Parse error")
			exit(1)
		section=exsec
		outfile.write(templateStrings[3])
	elif line=="authors":
		if section!=exsec:
			print("Parse error")
			exit(1)
		section=autsec
		outfile.write(templateStrings[4])
	elif line=="fend":
		if section!=autsec:
			print("Parse error")
			exit(1)
		section=nonesec
		outfile.write(templateStrings[5])
		outfile.close()
	elif section!=nonesec:
		if section==descsec:
			outfile.write("\t\t<para>"+line+"</para>\n")
		elif section==argsec:
			line=line.split(" ",maxsplit=1)
			outfile.write("\t\t\t<varlistentry>\n\t\t\t\t<term>"+line[0]+"</term>\n\t\t\t\t<para>"+line[1]+"</para>\n\t\t\t</varlistentry>\n")
		elif section==retsec:
			outfile.write("\t\t<para>"+line+"</para>\n")
		elif section==exsec:
			outfile.write("\t\t<programlisting role=\"example\">"+line+"</programlisting>\n")
		elif section==autsec:
			outfile.write("\t\t\t<member>"+line+"</member>\n")
		
