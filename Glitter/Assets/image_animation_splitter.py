import cv2


rows = 4
columns = 4
input_filename = "projectile_01/Projectile.png"
output_filename = "projectile_01/projectile"

img = cv2.imread(input_filename, -1)
h, w, d = img.shape
width = w / columns + 2
height = h / rows + 2
print str(width) + " " + str(height)
for y in range(rows):
    for x in range(columns):
        frame = img[(height * y):(height * y + height), (width * x):(width * x + width), :]
        cv2.imwrite(output_filename + '_' + str(x + y * columns) + '.png', frame)
