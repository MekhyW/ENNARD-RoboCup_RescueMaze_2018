# Untitled - By: dell 1 - dom ago 5 2018

import sensor, image, time
from pyb import UART, LED
thresholds = (0, 50)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(True)
sensor.set_auto_exposure(False)
sensor.set_auto_whitebal(True)

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    print(clock.fps())
    img.rotation_corr(0, 0, 180, 0, 0, 1)
    for blob in img.find_blobs([thresholds]):
        img.draw_rectangle(blob.rect())

