#!/usr/bin/env python

myfile=open("PositionInput.txt","r+")
output=open("outputfile.txt","w")
Text=(myfile.read().split("\n")) #reads in each line of the input file as a seperate list element
Alt = []
alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']

#Pull out common terms, and seperate long terms for individual word frequencies
for word in Text:
    word.title()
    if "Analyst" in word:
        word = "Analyst"
    elif "MD" in word:
        word = "Managing Director"
    elif "Vice President" in word:
        vplist = word.split("dent",1)
        for term in vplist:
            if "Vice Presi" in term:
                word = "Vice President"
            else: 
                notvp = term.split()
                for part in notvp:
                    Alt.append(part)
    elif "Banker" in word:
        word = "Banker"
    elif len(word) > 25:
        Alt.append(word)
        Text.remove(word)

#format the lists into columns of terms, and remove stray punctuation
text = str(Text)
text = text.replace("  ","~")
text = text.replace(" ","~")
text = text.replace("'","")
text = text.replace(",","\n")

alt = str(Alt)
alt = alt.replace("/","\n")
alt = alt.replace("'","")
alt = alt.replace(",","\n")
alt = alt.replace("-","")

#counting frequency 
combinedstring = text + alt
dictinput = []
frequency = {}
for line in combinedstring.split("\n"):
    if 'â€“' not in line:
        dictinput.append(line)



for item in dictinput:
    if item in frequency.keys():
        frequency[item] +=1
    else:
        frequency[item] = 1

final = ""


for i in frequency.keys():
    if len(i) >= 3:
        final = final + "{}    {}\n".format((frequency[i]),(i))

final = final.replace("[","")
final = final.replace("]","")

output.write(final)


myfile.close()
output.close()
