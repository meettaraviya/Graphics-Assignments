def cuboid(arg):
	centre = [float(arg[1]), float(arg[2]), float(arg[3])]
	length = float(arg[4])
	width = float(arg[5])
	height = float(arg[6])

	vertices = []
	for i in [-1, 1]:
		for j in [-1, 1]:
			for k in [-1, 1]:
				vertices.append([centre[0]+0.5*i*length, centre[1]+0.5*j*width, centre[2] + 0.5*k*height])

	tri_i = [
		[1,2,3],
		[2,3,4],
		[3,8,4],
		[3,7,8],
		[1,5,3],
		[5,3,7],
		[1,2,6],
		[1,5,6],
		[4,8,6],
		[2,4,6],
		[7,8,5],
		[5,6,8],
	]
	v = []
	for t in tri_i:
		v.append([*vertices[t[0]-1], float(arg[7]), float(arg[8]), float(arg[9]), "1","0.0","0.0"])
		v.append([*vertices[t[1]-1], float(arg[7]), float(arg[8]), float(arg[9]), "1","0.0","0.0"])
		v.append([*vertices[t[2]-1], float(arg[7]), float(arg[8]), float(arg[9]), "1","0.0","0.0"])

	return v

def toFile(v, name):
	f = open(name, "w")
	for vi in v:
		f.write(" ".join([str(i) for i in vi])+"\n")


toFile(cuboid(["x",0,0,0,2,2,2,0,1,1]),"")

