import win32api
import os
import win32event
import win32process
import numpy
def main():
    print(os.getcwd())
    n = 160
    b = 100
    timeout = 30
    maxtime = 0
    step = int(n/5)
    for method in ["comb_weight","random"]:#,"comb_weight","weight","2-occ","random"]:
        #,"weight","2-occ","random","weight_rev"]:
        exePath = method+".exe"
        Sat = numpy.zeros([16])
        TO = numpy.zeros([16])
        Time = numpy.zeros([16,b+1])
        Calls = numpy.zeros([16,b+1])
        MedianTime = numpy.zeros([16])
        MedianCalls = numpy.zeros([16])
        print(exePath)
        for k in range(0,16):
            for i in range(1,b+1):
                done_flag = 0
                param = exePath+" v"+repr(n)+"_c"+repr(3*n+step*k)+" "+repr(i)
                try:
                    with open("../../solutions/"+method+"/v"+repr(n)+"_c" + repr(3 * n + step * k) + "/sol_" + repr(i) + ".txt") as f:
                        for line in f.readlines():
                            if line.split()[0]=="s":
                                if line.split()[2] != "-1" or method=="random":
                                    done_flag = 1

                except Exception as e:
                    pass
                if done_flag==0:
                    handle = win32process.CreateProcess(exePath,
                                                param,
                                                None,
                                                None,
                                                0,
                                                win32process.CREATE_NEW_CONSOLE,
                                                None,
                                                None,
                                                win32process.STARTUPINFO())
                    win32event.WaitForSingleObject(handle[0], -1)
                with open("../../solutions/"+method+"/v"+repr(n)+"_c" + repr(3 * n + step * k) + "/sol_" + repr(i) + ".txt") as f:
                    for line in f.readlines():
                        if line.split()[0]=="s":
                            Sat[k]=Sat[k]+int(line.split()[2])
                        if line.split()[0]=="t":
                            Calls[k][i - 1] = int(line.split()[2])
                            if line.split()[1]!="TimeOut":
                                Time[k][i-1]=float(line.split()[1])
                                if(Time[k][i-1]>maxtime):
                                    maxtime = Time[k][i-1]
                                    print("max time now is "+repr(maxtime)+" s in k = "+ repr(k) +" and case "+repr(i)+"\n" )
                            else:
                                TO[k]=TO[k]+1
                                Time[k][i-1]=timeout
                                Sat[k] = Sat[k]+1
            MedianTime[k]=numpy.median(Time[k])
            MedianCalls[k]=numpy.median(Calls[k])
            with open("../../solutions/"+method+"/v"+repr(n)+"_c"+repr(3*n+step*k)+"/astat.txt",'w') as f:
                print("Sat: " + repr(Sat[k]) + '\n' + "Time out: " + repr(TO[k]) + '\n' + "Median time: " + repr(MedianTime[k]) + " Median Calls: "+repr(MedianCalls[k])+'\n')
                f.write("Sat: " + repr(Sat[k]) + '\n' + "Time out: " + repr(TO[k]) + '\n' + "Median time: " + repr(MedianTime[k]) + " Median Calls: "+repr(MedianCalls[k])+'\n')
        try:
            with open("../../solutions/"+method + "/v"+repr(n)+"_total_stat.txt", 'w') as f:
                for k in range(0,16):
                    f.write("k="+ repr(k)+". Sat: " + repr(Sat[k]) + ' ' + "Time out: " + repr(TO[k]) + ' ' + "Median time: " + repr(MedianTime[k]) + " Median Calls: "+repr(MedianCalls[k])+ '\n')
        except Exception as e:
            pass
if '__main__' == __name__:
    main()
