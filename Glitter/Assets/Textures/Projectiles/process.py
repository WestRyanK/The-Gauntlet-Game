import cv2
import numpy as np


input_filename = "flare.png"
output_filename = "flare2.png"

img = cv2.imread(input_filename, -1)
frame = np.copy(img)
frame[:,:,:] = 255.0
s = 0.3
alpha = img[:,:,0] * s + img[:,:,1] * s + img[:,:,2] * s
frame[:,:,3] = alpha
cv2.imwrite(output_filename, frame)
