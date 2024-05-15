import cv2
from cvzone.HandTrackingModule import HandDetector
import time
import serial

detector = HandDetector(maxHands=1, detectionCon=0.9)
video = cv2.VideoCapture(0)

port = "/dev/tty.usbmodem21101"
try:
    # connect to the serial port
    ser = serial.Serial(port, 115200)

    ser.write(b"a/n")
except:
    print("Could not connect to the serial port")

currentValue = 0

while True:
    _, img = video.read()
    img = cv2.flip(img, 1)
    hand = detector.findHands(img, draw=True)
    if hand:
        lmlist = hand[0]
        if lmlist:
            # print(lmlist)
            lmlist = lmlist[0]
            # print(lmlist)
            # myLmList = lmlist["lmList"]
            # print("#######")
            # print(myLmList)
            # myHandType = lmlist["type"]
            # print(myHandType)
            # print(myLmList)
            # try:
            fingerup = detector.fingersUp(lmlist)
            if currentValue != fingerup:
                print(fingerup)
                currentValue = fingerup
                output = ""
                for finger in fingerup:
                    if finger:
                        output += "1"
                    else:
                        output += "0"
                output += "\n"
                print(output)
                try:
                    ser.write(output.encode())
                except:
                    pass

                # if fingerup == [0, 0, 0, 0, 0]:
                #     print("0")
                #     if currentValue != 0:
                #         # ser.write(b"0/n")
                #         currentValue = 0
                # if fingerup == [0, 1, 0, 0, 0]:
                #     print("1")
                #     if currentValue != 1:
                #         # ser.write(b"1/n")
                #         currentValue = 1
                # if fingerup == [0, 1, 1, 0, 0]:
                #     print("2")
                #     if currentValue != 2:
                #         # ser.write(b"2/n")
                #         currentValue = 2
                # if fingerup == [0, 1, 1, 1, 0]:
                #     print("3")
                #     if currentValue != 3:
                #         # ser.write(b"3/n")
                #         currentValue = 3
                # if fingerup == [0, 1, 1, 1, 1]:
                #     print("4")
                #     if currentValue != 4:
                #         # ser.write(b"4/n")
                #         currentValue = 4
                # if fingerup == [1, 1, 1, 1, 1]:
                #     print("5")
                #     if currentValue != 5:
                #         # ser.write(b"5/n")
                #         currentValue = 5
                # if fingerup == [1, 0, 0, 0, 0]:
                #     print("6")
                # if fingerup == [1, 1, 0, 0, 0]:
                #     print("7")
                # if fingerup == [1, 1, 1, 0, 0]:
                #     print("8")
                # if fingerup == [1, 1, 1, 1, 0]:
                #     print("9")
            # except Exception as e:
            #     print(e)

    cv2.imshow("Video", img)
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

video.release()
cv2.destroyAllWindows()
