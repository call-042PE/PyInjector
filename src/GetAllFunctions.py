import os,sys,inspect,re,dis,json,types

hexaPattern = re.compile(r'\b0x[0-9A-F]+\b')
def GetAllFunctions(): # get all function in a script
    functionFile = open("dumpedMembers.txt","w+")
    members = inspect.getmembers(sys.modules[__name__]) # the code will take all the members in the __main__ module, the main problem is that it can't dump main code function
    for member in members:
        match = re.search(hexaPattern,str(member[1]))
        if(match):
            functionFile.write("{\"functionName\":\""+str(member[0])+"\",\"functionAddr\":\""+match.group(0)+"\"}\n")
        else:
            functionFile.write("{\"functionName\":\""+str(member[0])+"\",\"functionAddr\":null}\n")
    functionFile.close()

GetAllFunctions()