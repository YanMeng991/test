from PIL import Image

img = Image.open("fishing_boat.bmp")
col = img.size[0]
row = img.size[1]

for x in range(row):
    for y in range(col):
        print('{0:03d} '.format(img.getpixel((y,x))), end = '')
    print('')
