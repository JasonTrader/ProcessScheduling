from plotly import __version__
from plotly.offline import download_plotlyjs, init_notebook_mode, iplot
from plotly.offline import plot
import plotly.graph_objs as go

#files = ["FCFS.txt","RRQ5.txt","RRQ20.txt","RRQ50.txt","SPN.txt"]
files = ["FCFS.txt", "RRQ5.txt", "RRQ20.txt", "RRQ50.txt", "SPN.txt", "SRT.txt", "Feedback.txt"]
prefs = ["DATAFILES/Run1/", "DATAFILES/Run2/", "DATAFILES/Run3/"]
speedupfiles2 = ["FCFS2C.txt", "RRQ52C.txt", "RRQ202C.txt", "RRQ502C.txt", "SPN2C.txt", "SRT2C.txt", "Feedback2C.txt"]
speedupfiles4 = ["FCFS4C.txt", "RRQ54C.txt", "RRQ204C.txt", "RRQ504C.txt", "SPN4C.txt", "SRT4C.txt", "Feedback4C.txt"]
totTime = 100000
lname = []
lthrough = []
lturn = []
lwait = []
lresp = []
lcontext = []
lprocu = []
lspeed2 = []
lspeed4 = []

for fil in files:
    totwait = 0
    totresp = 0
    totturn = 0
    totProc = 0
    for pref in prefs:
        f = open(pref + fil)
        afil = pref + "Add" + fil
        f2 = open(afil)
        lin2 = f2.readline()
        [empty, numProc] = lin2.split()
        numProc = int(numProc)
        count = 0
        while count < int(numProc):
            count += 1
            lin = f.readline()
            [fintime, pid, arr, burst, turn, wait, resp] = lin.split()
            totwait += float(wait)
            totresp += float(resp)
            totturn += float(turn)
        totProc += int(numProc)
    avgwait = totwait / totProc
    avgresp = totresp / totProc
    avgturn = totturn / totProc
    lname.append(fil.rsplit('.',1)[0])
    lthrough.append((float(totProc)/(totTime*len(prefs)))*1000)
    lturn.append(avgturn/1000)
    lwait.append(avgwait/1000)
    lresp.append(avgresp/1000)
    lcontext.append(float(1)/1000)
    lprocu.append((float((totTime*len(prefs))-int(empty)))/(totTime*len(prefs)))
    for s2 in speedupfiles2:
        s2totturn = 0
        s2totProc = 0
        for pref in prefs:
            f = open(pref + s2)
            afil = pref + "Add" + s2
            f2 = open(afil)
            lin2 = f2.readline()
            [s2empty, s2numProc] = lin2.split()
            s2numProc = int(s2numProc)
            count = 0
            while count < int(s2numProc):
                count += 1
                lin = f.readline()
                [fintime, pid, arr, burst, turn, wait, resp] = lin.split()
                s2totturn += float(turn)
            s2totProc += int(s2numProc)
        s2avgturn = s2totturn / s2totProc
        lspeed2.append(float(avgturn - s2avgturn)/avgturn)
    for s4 in speedupfiles4:
        s4totturn = 0
        s4totProc = 0
        for pref in prefs:
            f = open(pref + s4)
            afil = pref + "Add" + s4
            f2 = open(afil)
            lin2 = f2.readline()
            [s4empty, s4numProc] = lin2.split()
            s4numProc = int(s4numProc)
            count = 0
            while count < int(s4numProc):
                count += 1
                lin = f.readline()
                [fintime, pid, arr, burst, turn, wait, resp] = lin.split()
                s4totturn += float(turn)
            s4totProc += int(s4numProc)
        s4avgturn = s4totturn / s4totProc
        lspeed4.append(float(avgturn - s4avgturn)/avgturn)

gthrough = go.Bar(
    x=lname,
    y=lthrough,
    name='Throughput (Processes per microsecond)'
)
gturn = go.Bar(
    x=lname,
    y=lturn,
    name='Average Turnaround Time (in microseconds)'
)
gwait = go.Bar(
    x=lname,
    y=lwait,
    name='Average Wait Time (in microseconds)'
)
gresp = go.Bar(
    x=lname,
    y=lresp,
    name='Average Response Time (in microseconds)'
)
gcontext = go.Bar(
    x=lname,
    y=lcontext,
    name='Average Context Switch Time (in microseconds)'
)
gprocu = go.Bar(
    x=lname,
    y=lprocu,
    name='Processor Utilization %'
)
gs2 = go.Bar(
    x=lname,
    y=lspeed2,
    name='Speed percentage increase moving from 1 to 2 cores'
)
gs4 = go.Bar(
    x=lname,
    y=lspeed4,
    name='Speed percentage increase moving from 1 to 4 cores'
)

data = [gthrough, gturn, gwait, gresp, gcontext, gprocu, gs2, gs4]
layout = go.Layout(
    barmode='group'
)

for d in data:
    yaxis = go.YAxis(title=d.name)
    layout.update(
        yaxis1=yaxis
    )
    fig = go.Figure(data=[d], layout=layout)
    plot(fig, filename=d.name)
