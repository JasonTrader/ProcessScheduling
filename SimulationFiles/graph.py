from plotly import __version__
from plotly.offline import download_plotlyjs, init_notebook_mode, iplot
from plotly.offline import plot
import plotly.graph_objs as go

#files = ["FCFS.txt","RRQ5.txt","RRQ20.txt","RRQ50.txt","SPN.txt"]
files = ["FCFS.txt"]
totTime = 100000
lname = []
lthrough = []
lturn = []
lwait = []
lresp = []
lcontext = []
lprocu = []

for fil in files:
    f = open(fil)
    afil = "Add" + fil
    f2 = open(afil)
    lin2 = f2.readline()
    [empty, numProc] = lin2.split()
    numProc = int(numProc)
    avgwait = 0
    avgresp = 0
    avgturn = 0
    for lin in f:
        [fintime, pid, arr, burst, turn, wait, resp] = lin.split()
        avgwait += float(wait)
        avgresp += float(resp)
        avgturn += float(turn)
    avgwait /= numProc
    avgresp /= numProc
    avgturn /= numProc
    lname.append(fil.rsplit('.',1)[0])
    lthrough.append((float(numProc)/totTime))
    lturn.append(avgturn)
    lwait.append(avgwait)
    lresp.append(avgresp)
    lcontext.append(1)
    lprocu.append((float(totTime-int(empty))/totTime))


gthrough = go.Bar(
    x=lname,
    y=lthrough,
    name='Throughput Time'
)
gturn = go.Bar(
    x=lname,
    y=lturn,
    name='Average Turnaround Time'
)
gwait = go.Bar(
    x=lname,
    y=lwait,
    name='Average Wait Time'
)
gresp = go.Bar(
    x=lname,
    y=lresp,
    name='Average Response Time'
)
gcontext = go.Bar(
    x=lname,
    y=lcontext,
    name='Average Context Switch Time'
)
gprocu = go.Bar(
    x=lname,
    y=lprocu,
    name='Processor Utilization %'
)

data = [gthrough, gturn, gwait, gresp, gcontext, gprocu]
layout = go.Layout(
    barmode='group'
)
for d in data:
    fig = go.Figure(data=[d], layout=layout)
    plot(fig, filename=d.name)
