import cv2


rows = 4
columns = 4
input_filename = "Projectiles/BlueMatterCannon/BlueMatterCannon2.png"
output_filename = "Projectiles/BlueMatterCannon/anti_matter_cannon"

img = cv2.imread(input_filename, -1)
h, w, d = img.shape
width = w / columns + 2
height = h / rows + 2
print str(width) + " " + str(height)
for y in range(rows):
    for x in range(columns):
        frame = img[(height * y):(height * y + height), (width * x):(width * x + width), :]
        cv2.imwrite(output_filename + '_' + str(x + y * columns) + '.png', frame)
