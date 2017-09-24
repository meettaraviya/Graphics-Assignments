
vertices = [
	(0,0,0),
	(5,2,0),
	(5,-2,0),
	(3,0,1),
	(3,0,-1),
]

# colors = [
# 	(0.7,0.7,0.7),
# 	(0.4,0.4,0.4),
# 	(0.4,0.4,0.4),
# 	(0.5,0.5,0.5),
# 	(0.5,0.5,0.5),
# ]

colors = [
	(1.0,0.0,0.0),
	(0.0,0.0,0.0),
	(0.0,0.0,0.0),
	(0.0,0.0,0.0),
	(0.0,0.0,0.0),
]


triangles = [
	(0,1,3),
	(0,1,4),
	(0,2,3),
	(0,2,4),
	(1,3,4),
	(2,3,4),
]

from math import *


x_min = 3
x_max = 30

for t in triangles:
	for v in t:
		print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%(vertices[v]+colors[v]))

r=0.25

print"\n"
for i in xrange(9):

	y=r*sin(radians(i*40))
	z=r*cos(radians(i*40))
	y2=r*sin(radians((i+1)*40))
	z2=r*cos(radians((i+1)*40))

	
	print(("%3.1f %3.1f %3.1f 0 0 0")%(x_min, y, z))
	print(("%3.1f %3.1f %3.1f 0 0 0")%(x_min, y2, z2))
	print(("%3.1f %3.1f %3.1f 0 0 0")%(x_max, y, z))
	print(("%3.1f %3.1f %3.1f 0 0 0")%(x_max, y, z))
	print(("%3.1f %3.1f %3.1f 0 0 0")%(x_min, y2, z2))
	print(("%3.1f %3.1f %3.1f 0 0 0")%(x_max, y2, z2))

	print(("%3.1f %3.1f %3.1f 0 0 0")%(x_max, 0, 0))
	print(("%3.1f %3.1f %3.1f 0 0 0")%(x_max, y, z))
	print(("%3.1f %3.1f %3.1f 0 0 0")%(x_max, y2, z2))

print"\n"

width = 0.05
gap = 0.4
sheer = 1
height = 1

colors_down = [
	(1,0,0),
]*10

colors_up = [
	(0,0,0),
]*10

for i in xrange(7):

	xr = x_max-i*(width+gap)
	xl = x_max - gap-i*(width+gap)

	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl,r,0)+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl+sheer,r+height,0)+colors_up[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr,r,0)+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr,r,0)+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl+sheer,r+height,0)+colors_up[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr+sheer,r+height,0)+colors_up[i]))


	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl,-(r),0)+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl+sheer,-(r+height),0)+colors_up[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr,-(r),0)+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr,-(r),0)+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl+sheer,-(r+height),0)+colors_up[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr+sheer,-(r+height),0)+colors_up[i]))

	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl,0,r)+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl+sheer,0,r+height)+colors_up[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr,0,r)+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr,0,r)+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl+sheer,0,r+height)+colors_up[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr+sheer,0,r+height)+colors_up[i]))

	
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl,0,-(r))+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl+sheer,0,-(r+height))+colors_up[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr,0,-(r))+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr,0,-(r))+colors_down[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xl+sheer,0,-(r+height))+colors_up[i]))
	print(("%3.1f %3.1f %3.1f %3.1f %3.1f %3.1f")%((xr+sheer,0,-(r+height))+colors_up[i]))

