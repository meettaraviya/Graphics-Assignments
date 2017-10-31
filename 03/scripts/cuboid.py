import sys

if len(sys.argv)>=10:
	centre = [float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3])]
	length = float(sys.argv[4])
	width = float(sys.argv[5])
	height = float(sys.argv[6])

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
	for t in tri_i:
		print(*vertices[t[0]-1], float(sys.argv[7]), float(sys.argv[8]), float(sys.argv[9]))
		print(*vertices[t[1]-1], float(sys.argv[7]), float(sys.argv[8]), float(sys.argv[9]))
		print(*vertices[t[2]-1], float(sys.argv[7]), float(sys.argv[8]), float(sys.argv[9]))
		print('')
