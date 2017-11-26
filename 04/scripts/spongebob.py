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
		v.append([*vertices[t[2]-1], float(arg[7]), float(arg[8]), float(arg[9]), "1","0.0","0.0\n"])
		# v.append([])

	return v

def toFile(v, name):
	f = open(name, "a")
	for vi in v:
		f.write(" ".join([str(i) for i in vi])+"\n")
	f.close()

##front part
toFile(cuboid(["x",0,-50,0,30,60,10,1,0.843137,0]),"front.raw")
toFile(cuboid(["x",0,-85,0,30,10,10,0.972549,0.972549,1]),"front.raw")
toFile(cuboid(["x",0,-100,0,30,20,10,0.545098,0.270588,0.0745098]),"front.raw")
toFile(cuboid(["x",7.5,-112.5,0,10,5,10,0.627451,0.321569,0.176471]),"front.raw")
toFile(cuboid(["x",-7.5,-112.5,0,10,5,10,0.627451,0.321569,0.176471]),"front.raw")


##right hand
toFile(cuboid(["x",20,-50,0,10,10,2.5,0.972549,0.972549,1]),"right_hand_low.raw")
toFile(cuboid(["x",35,-50,0,20,5,2.5,1,0.843137,0]),"right_hand_low.raw")

toFile(cuboid(["x",55,-50,0,20,5,2.5,1,0.843137,0]),"right_hand_high.raw")
toFile(cuboid(["x",55,-50,0,20,5,2.5,1,0.843137,0]),"right_hand_high.raw")

toFile(cuboid(["x",67.5,-47.5,0,5,15,2.5,1,0.843137,0]),"right_hand_high.raw")
toFile(cuboid(["x",70,-50,0,10,10,2.5,1,0.843137,0]),"right_hand_high.raw")


##left hand
toFile(cuboid(["x",-20,-50,0,10,10,2.5,0.972549,0.972549,1]),"left_hand_low.raw")
toFile(cuboid(["x",-35,-50,0,20,5,2.5,1,0.843137,0]),"left_hand_low.raw")

toFile(cuboid(["x",-55,-50,0,20,5,2.5,1,0.843137,0]),"left_hand_high.raw")
toFile(cuboid(["x",-55,-50,0,20,5,2.5,1,0.843137,0]),"left_hand_high.raw")

toFile(cuboid(["x",-67.5,-47.5,0,5,15,2.5,1,0.843137,0]),"left_hand_high.raw")
toFile(cuboid(["x",-70,-50,0,10,10,2.5,1,0.843137,0]),"left_hand_high.raw")

##right leg
toFile(cuboid(["x",7.5,-120,0,5,10,2.5,1,0.843137,0]),"right_leg_high.raw")
toFile(cuboid(["x",7.5,-130,0,5,10,2.5,1,0.843137,0]),"right_leg_low.raw")
toFile(cuboid(["x",7.5,-140,0,10,10,10,0.156863,0.156863,0.156863]),"right_leg_low.raw")


##left leg
toFile(cuboid(["x",-7.5,-120,0,5,10,2.5,1,0.843137,0]),"left_leg_high.raw")
toFile(cuboid(["x",-7.5,-130,0,5,10,2.5,1,0.843137,0]),"left_leg_low.raw")
toFile(cuboid(["x",-7.5,-140,0,10,10,10,0.156863,0.156863,0.156863]),"left_leg_low.raw")








