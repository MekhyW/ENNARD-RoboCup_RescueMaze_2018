import sensor, image, time, math
from pyb import UART, LED
from image import SEARCH_EX, SEARCH_DS
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQQVGA)
sensor.set_auto_gain(True)
sensor.set_auto_exposure(True)
sensor.set_auto_whitebal(True)
sensor.skip_frames(time=1000)
uart = UART(1, 9600, timeout_char=10)
uart.init(9600)
templateH = image.Image("/maze_H.pgm")
templateS = image.Image("/maze_S.pgm")
templateU = image.Image("/maze_U.pgm")
high_threshold = (0, 50)


while(True):
    img = sensor.snapshot()
    img.binary([high_threshold])
    img.dilate(2)
    img.binary([high_threshold])
    img.dilate(2)
    img.binary([high_threshold])
    img.dilate(2)
    img.binary([high_threshold])
    img.dilate(2)
    img.binary([high_threshold])
    img.dilate(1)
    img.binary([high_threshold])
    MatchS = img.find_template(templateS, 0.3, search=SEARCH_EX)
    if MatchS and MatchS[0]>30 and MatchS[0]<50:
        img.draw_rectangle(MatchS)
        uart.write('S')
        print('S')
        LED(1).off()
        LED(2).on()
        LED(3).off()
    else:
        MatchH = img.find_template(templateH, 0.4, search=SEARCH_EX)
        if MatchH and MatchH[0]>30 and MatchH[0]<50:
            img.draw_rectangle(MatchH)
            uart.write('H')
            print('H')
            LED(1).on()
            LED(2).off()
            LED(3).off()
        else:
            MatchU = img.find_template(templateU, 0.6, search=SEARCH_EX)
            if MatchU and MatchU[0]>30 and MatchU[0]<50:
                img.draw_rectangle(MatchU)
                uart.write('U')
                print('U')
                LED(1).off()
                LED(2).off()
                LED(3).on()
            else:
                uart.write('n')
                print('n')
                LED(1).off()
                LED(2).on()
                LED(3).on()
