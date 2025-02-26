import numpy

def printout( t, T, N ):
    imax = 10
    print(f"{t:8.0f} ", end="")
    for i in range( imax ):
        idx = i*(N+1)//(imax-1);
        Ti = T[idx]
        print(f"{Ti-273.0:7.2f} ", end="")
    print("")

N = 1024
time = 51200
printtime = time//20

Tinit = 300.0
T1 = 1000.0
T2 = 200.0
dx = 0.01
dt = 0.001
alpha = 0.03
k = alpha * dt / dx / dx

T = numpy.array([0.0]*(N+2))

for i in range(1, N+1):
    T[i] = Tinit
    
T[0]=T1
T[N+1]=T2

for t in range(time):
    if (t % printtime) == 0:
        printout(t, T, N)
    v = T[0]
    for i in range(1, N+1):
        Tslash = k*(T[i+1] + v - 2*T[i])
        v = T[i]
        T[i] += Tslash

printout( time, T, N )
