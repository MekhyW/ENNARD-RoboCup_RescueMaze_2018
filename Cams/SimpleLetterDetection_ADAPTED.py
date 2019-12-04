# Smart Letter Detection Version 3
import sensor, image, time, math
from image import SEARCH_EX, SEARCH_DS
from pyb import LED,UART,Pin
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQQVGA)
sensor.skip_frames(time=1000)
sensor.set_auto_gain(True)
sensor.set_auto_whitebal(True)
sensor.set_auto_exposure(True)
uart = UART(1, 9600, timeout_char=10)
uart.init(9600)
templateH = image.Image("/maze_H.pgm")
templateS = image.Image("/maze_S.pgm")
templateU = image.Image("/maze_U.pgm")
ImageX = 80
ImageY = 70
high_threshold = (0, 60)
thresholds = (0, 120)
centX = ImageX // 2
centY = ImageY // 2

global best_match

while(True):
    img = sensor.snapshot()
    img.rotation_corr(0, 0, 180, 0, 0, 1)
    img.binary([high_threshold])
    img.dilate(2)
    img.binary([high_threshold])
    MatchH = img.find_template(templateH, 0.5, search=SEARCH_EX)
    MatchS = img.find_template(templateS, 0.2, search=SEARCH_EX)
    MatchU = img.find_template(templateU, 0.5, search=SEARCH_EX)
    most_middle = 10000
    match_found = False
    White2Black = 0

    for blob in img.find_blobs([thresholds], pixels_threshold=50, area_threshold=10, merge=False):

        # touch side break
        if blob.x() == 0 or blob.y() == 0 or blob.y() + blob.h() >= ImageY - 1 or blob.x() + blob.w() >= ImageX - 1:
            continue

        distance = math.floor( math.sqrt( math.pow((blob.cx() - centX),2 ) + math.pow((blob.cy() - centY),2)))

        if distance < most_middle and blob.pixels() < 3000 and blob.pixels() > 10:
            most_middle = distance
            best_match = blob
            match_found = True

    if match_found:

        MidY = best_match.cy()
        BotX = best_match.x() + best_match.w()
        TopX = best_match.x()

        BlackCount = 0
        lastWhite = True

        for X in range(TopX,BotX,1):

            if img.get_pixel(X, MidY) == 0 and lastWhite:
                White2Black += 1
                lastWhite = False

            elif img.get_pixel(X, MidY) == 0:
                BlackCount += 1

            elif img.get_pixel(X, MidY) != 0:
                lastWhite = True

        if(img.get_pixel(TopX + 1, MidY) == 0 and White2Black == 1):
            White2Black += 1

        img.draw_line( (TopX,MidY,BotX,MidY),color = (150,150,150))
        lastWhite = True

    if White2Black==2 and MatchS:
        White2Black=3
    if White2Black==2 and MatchH:
        White2Black=1
    if White2Black==1 and MatchU:
        White2Black=2

    if White2Black == 3:
        uart.write('S')
        print('S')
        LED(1).off()
        LED(2).on()
        LED(3).off()

    elif White2Black == 2:
        uart.write('U')
        print('U')
        LED(1).off()
        LED(2).off()
        LED(3).on()

    elif White2Black == 1:
        uart.write('H')
        print('H')
        LED(1).on()
        LED(2).off()
        LED(3).off()

    else:
        uart.write('n')
        print('n')
        LED(1).off()
        LED(2).on()
        LED(3).on()

    match_found = False
