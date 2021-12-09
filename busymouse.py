import pyautogui
import time
import sys
from datetime import datetime

pyautogui.FAILSAFE = False

xs, ys = pyautogui.size()
xm = xs / 2
ym = ys / 2

while True:
   try:
      xp, yp = pyautogui.position()

      if xp >= xm:
         xd = -1
      else:
         xd = 1
      if yp >= ym:
         yd = -1
      else:
         yd = 1

#      print("Debug: xs=", xs, " ys=", ys, " xp=", xp, " yp=", yp, " xd=", xd, " yd=", yd)
      pyautogui.moveRel(xd,yd)
      pyautogui.moveRel(0 - xd, 0 - yd)

      now = datetime.now()
      current_time = now.strftime("%H:%M:%S")
      print(current_time, end = '\r')

      time.sleep(60)
   except KeyboardInterrupt:
      print("Ok, exiting.")
      sys.exit()
