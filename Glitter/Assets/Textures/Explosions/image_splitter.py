import cv2


width = 512
height = 512
rows = 8
columns = 8
input_filename = "explosion_03/Explosion.png"
output_filename = "explosion_03/explosion"

img = cv2.imread(input_filename, -1)
for y in range(rows):
    for x in range(columns):
        frame = img[(height * y):(height * y + height), (width * x):(width * x + width), :]
        cv2.imwrite(output_filename + '_' + str(x + y * columns) + '.png', frame)
