#! /usr/bin/env python3

import sys #for getting command line argument

#the section the parser is in
nonesec=-1
mainsec=0
exsec=1
autsec=2

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
	line=datfile.readline().strip() #get the line
	if not line:
		break #break at eof
	if line[0]=='#':
		continue #ignore comments (lines starting with #)
	if line=="function":
		if section!=nonesec:
			print("Parse error.")
			exit(1)
		section=mainsec
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
	elif line=="examples":
		if section!=mainsec:
			print("Parse error 1.",section)
			exit(1)
		section=exsec
		outfile.write(templateStrings[1])
	elif line=="authors":
		if section!=exsec:
			print("Parse error 2.",section)
			exit(1)
		section=autsec
		outfile.write(templateStrings[2])
	elif line=="fend":
		if section!=autsec:
			print("Parse error 3.",section)
			exit(1)
		section=nonesec
		outfile.write(templateStrings[3])
		outfile.close()
	elif section!=nonesec:
		if section==mainsec:
			outfile.write("\t\t<para>"+line+"</para>\n")
		elif section==exsec:
			outfile.write("\t\t<programlisting role=\"example\">"+line+"</programlisting>\n")
		elif section==autsec:
			outfile.write("\t\t\t<member>"+line+"</member>\n")
		
