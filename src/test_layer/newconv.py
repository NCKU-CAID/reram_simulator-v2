
outfile = 'newoutput.txt'

def mac_operation(input,weight):
    result=0
    for i,w in zip(input,weight):
        temp = i * w
        result = result + temp
    return result


resultlist=[]
write_file = open(outfile,'w')
for i in range(1,36+1):
    filename = './input/input1_'+str(i)+'.txt'
    f = open(filename,'r')
    text = f.read()

    inputlist=[]
    textlist = text.split('\n')
    textlist.pop()
    for l in textlist:
        inputlist.append(int(l))
        # change data type (from str to int)
    chtext = 'Position_'+str(i)+' :'
    write_file.write(chtext+'\n')

    for w in range(1,8+1):
        weightname = './weight/weight'+str(w)+'_1.txt'
        wf = open(weightname,'r')
        weighttext = wf.read()
        weightlist=[]
        weighttext = weighttext.split('\n')
        weighttext.pop()
        for l in weighttext:
            weightlist.append(int(float(l)))
            # change data type (from str to int)

        for t in range(8):
            #print(weightlist[t*64:t*64+27])
            weight_tile='weight'+str(w)+'_1 No '+str(t+1)+'  '
            write_file.write(weight_tile)
            r = mac_operation(weightlist[t*27:t*27+27],inputlist)
            write_file.write(str(r)+'\n')
            


