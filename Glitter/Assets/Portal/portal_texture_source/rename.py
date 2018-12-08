import glob
import os


for i in range(10, 45):
    os.rename( str(i) + ".png", "renamed/" + str(i - 10) + ".png")

#files = sorted(list(glob.glob("original/*.png")))
#for i, filename in enumerate(files):
#    print filename
#    os.rename(filename, "./original/renamed/" + str(i) + ".png")
