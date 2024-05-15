import cv2
from cvzone.HandTrackingModule import HandDetector
import time
import serial

detector = HandDetector(maxHands=1, detectionCon=0.9)
video = cv2.VideoCapture(0)
# flip the video horizontally
video.set(cv2.CAP_PROP_FPS, 60)
video.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
video.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)


port = "/dev/tty.usbmodem21101"
try:
    # connect to the serial port
    ser = serial.Serial(port, 115200)

    ser.write(b"a/n")
except:
    print("Could not connect to the serial port")

currentValue = 0
try:
    while True:
        _, img = video.read()
        # img = cv2.flip(img, 1)
        hand = detector.findHands(img, draw=True)
        if hand:
            lmlist = hand[0]
            if lmlist:
                lmlist = lmlist[0]
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

        cv2.imshow("Video", img)
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
except KeyboardInterrupt:
    print("Keyboard Interrupt")

ser.write(b"nnnnn/n")
ser.close()

video.release()
cv2.destroyAllWindows()
