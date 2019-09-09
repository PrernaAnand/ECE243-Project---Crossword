from PIL import Image

im = Image.open('digits.png') # Can be many different formats.
pix = im.load()
width, height =  im.size

pixels = list(im.getdata())

print "{"
'''
print pixels[0]
r = bin(pixels[0][0])[2:7].zfill(5)
g = bin(pixels[0][1])[2:8].zfill(5)
b = bin(pixels[0][2])[2:8].zfill(5)

rgb = r+g+b

hexRGB = hex(int(rgb, 2))

print hexRGB
'''
for p in pixels:

	#red = bin(p[0])
	#green = bin(p[1])
	#blue = bin(p[2])

	#r = red.replace('0x', '')
	#g = green.replace('0x', '')
	#b = blue.replace('0x', '')


	r = bin(p[0])[2:7].zfill(5)
	g = bin(p[1])[2:8].zfill(6)
	b = bin(p[2])[2:7].zfill(5)

	rgb = r+g+b

	hexRGB = hex(int(rgb, 2))

	#print  r + " " + g + " " + b 
	print hexRGB + ", "

print "}"	



