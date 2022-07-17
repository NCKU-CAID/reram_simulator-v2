input_total = 36
weight_total = 8
input_path = './input/input1_'
weight_path = './weight/weight'

filename = 'filename.txt'

wf=open(filename,'w')

for w in range(1,weight_total+1):
    for i in range(1,1+input_total):
        text = input_path + str(i) + '.txt '
        wf.write(text)
        wt = '0\n' if (i!=1) else weight_path+str(w)+'_1.txt\n'
        wf.write(wt)
wf.close()