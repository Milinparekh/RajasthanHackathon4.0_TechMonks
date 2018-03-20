# Created by Karan Kharecha
# Team Name: TechMonks
# Date: 19-21 March, 2018
# Description: Python script to sense the distance and send it to the server every 1 second.

import RPi.GPIO as GPIO
import time
import socket
GPIO.setmode(GPIO.BCM)

TRIG = 23
ECHO = 24
BUFFER_SIZE = 1024

print ("Distance Measurement In Progress")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('192.168.1.18', 6776))

GPIO.setup(23,GPIO.OUT)
GPIO.setup(24,GPIO.IN)
while 1:
  GPIO.output(TRIG, False)
  print ("Waiting For Sensor To Settle..")
  time.sleep(1)

  GPIO.output(TRIG, True)
  time.sleep(0.00001)
  GPIO.output(TRIG, False)

  while GPIO.input(ECHO)==0:
    pulse_start = time.time()

  while GPIO.input(ECHO)==1:
    pulse_end = time.time()

  pulse_duration = pulse_end - pulse_start

  distance = pulse_duration * 17150

  distance = round(distance, 2)

  s.send(distance.__str__())
