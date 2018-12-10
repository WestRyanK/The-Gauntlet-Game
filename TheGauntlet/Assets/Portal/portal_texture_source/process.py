import cv2
import glob
import numpy as np

texture = cv2.imread("original/portal_texture.png", -1)
files = list(glob.glob('*.png'))

for i in range(len(files)):
    portal = cv2.imread(str(i) + ".png", -1)
    #portal = portal[457:818,163:524,:]
    portal = portal[163:524,457:818,:]
    portal = cv2.resize(portal, (486, 486))
    portal = cv2.cvtColor(portal, cv2.COLOR_RGB2RGBA)
    texture[:486,945:1431,:] = portal
    #texture[:486,880:,:] = portal
    cv2.imwrite("./out/portal_texture_" + str(i) + ".png", texture)
