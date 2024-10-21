import cv2
import numpy as np
import time
from ultralytics import YOLO


def list_available_cameras():
    available_cameras = []
    for camera_id in range(10):
        print(f"Versuche Zugriff auf Kamera Nr. {camera_id} ...", end=" ")
        cap = cv2.VideoCapture(camera_id)
        if cap.isOpened():
            print("ERFOLG!")
            available_cameras.append(camera_id)
            cap.release()
        else:
            print("FEHLGESCHLAGEN!")
    return available_cameras


    
available_cameras = list_available_cameras()
print("-" * 40)
print("Verfügbare Kameras:", available_cameras)
print("-" * 40 + "\n")

camera_to_use = 2

cap = cv2.VideoCapture(camera_to_use)
if not cap.isOpened():
    print("Kann die Kamera nicht öffnen")
    exit()

frame_nr = 0

model = YOLO("yolo11l.pt")

try:
    
    pop_initialized = False

    start_time = time.time()

    while True:        
        ret, frame = cap.read()
        frame_nr += 1

        # If user presses q, we quit this demo  
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        results = model(frame, verbose=False)

        end_time = time.time()
        duration = end_time - start_time
                
        img = results[0].plot()  # This plots the detections on the image

        processing_time_avg = duration / frame_nr
        cv2.putText(img, f'Frame: {frame_nr} Processing time: {processing_time_avg:.2f} sec',
                    (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2, cv2.LINE_AA)
        cv2.imshow('Kamerabild', img)
        
        
finally:
    # free resources
    cap.release()
    cv2.destroyAllWindows()
