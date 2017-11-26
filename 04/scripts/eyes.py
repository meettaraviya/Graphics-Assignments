from math import *
r = 5.0
r1 = 2.0
for i in range(9):

  y=r*sin(radians(i*40))
  x=r*cos(radians(i*40))
  y2=r*sin(radians((i+1)*40))
  x2=r*cos(radians((i+1)*40))

  yr=r1*sin(radians(i*40))
  xr=r1*cos(radians(i*40))
  yr2=r1*sin(radians((i+1)*40))
  xr2=r1*cos(radians((i+1)*40))

  print(("%3.1f %3.1f %3.1f 1 1 1 1 0 0")%(-7.5, -40, -6.0))
  print(("%3.1f %3.1f %3.1f 1 1 1 1 0 0")%(x-7.5, y-40, -6.0))
  print(("%3.1f %3.1f %3.1f 1 1 1 1 0 0")%(x2-7.5, y2-40, -6.0))

  print(("%3.1f %3.1f %3.1f 0 0 0 1 0 0")%(-7.5, -40, -7.0))
  print(("%3.1f %3.1f %3.1f 0 0 0 1 0 0")%(xr-7.5, yr-40, -7.0))
  print(("%3.1f %3.1f %3.1f 0 0 0 1 0 0")%(xr2-7.5, yr2-40, -7.0))


