import sensor, image, time, math
from pyb import UART
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQSIF)
sensor.set_auto_gain(True)
sensor.set_auto_exposure(True)
sensor.set_auto_whitebal(True)
sensor.skip_frames(time=2000)
uart = UART(1, 9600, timeout_char=10)
uart.init(9600)
classifierH = image.HaarCascade("/classifierH.cascade")
classifierS = image.HaarCascade("/classifierS.cascade")
classifierU = image.HaarCascade("/classifierU.cascade")


while(True):
    img = sensor.snapshot()
    MatchH = img.find_features(classifierH, threshold=0.5, scale=2)
    if MatchH:
        img.draw_rectangle(MatchH)
        uart.write('H')
        print('H')
    else:
        MatchS = img.find_features(classifierS, threshold=0.5, scale=2)
        if MatchS:
            img.draw_rectangle(MatchS)
            uart.write('S')
            print('S')
        else:
            MatchU = img.find_features(classifierU, threshold=0.5, scale=2)
            if MatchU:
                img.draw_rectangle(MatchU)
                uart.write('U')
                print('U')
            else:
                uart.write('n')
                print('n')
