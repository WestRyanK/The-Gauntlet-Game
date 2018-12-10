import cv2
import numpy as np
import glob

files = list(glob.glob("orig/*.png"))
for file in files:
    img = cv2.imread(file, -1)
    img = np.flip(img, 0)
    cv2.imwrite(file, img)
