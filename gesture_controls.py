import cvzone
import cv2
import time
import numpy as np 


font = cv2.FONT_HERSHEY_SIMPLEX
color = (0,255,0)

new_time = 0
prev_time = 0

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
detector = cvzone.HandDetector(maxHands=1, detectionCon=0)
ser = cvzone.SerialObject("COM3", 9600, 1)


while True:

    ret, frame = cap.read()
    if not ret: break

    frame = detector.findHands(frame)
    lmList, bbox =  detector.findPosition(frame)
    if lmList:
        fingers =  detector.fingersUp()
        ser.sendData(fingers)

    new_time = time.time()
    fps = int(1 / (new_time - prev_time))

    frame = cv2.putText(frame, f'FPS: {fps}', (50,50), font, 1, color, 2, cv2.LINE_AA)
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == 27:
        break
    
    prev_time = new_time

cap.release()
cv2.destroyAllWindows()