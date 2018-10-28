#!/usr/bin/python
import serial
import syslog
from simple_pid import PID
import pygame


motorDriverArduino = serial.Serial('/dev/ttyS0',9600,timeout=0.1)
potentiometerArduino = serial.Serial('/dev/ttyS1',9600,timeout=0.1)

potentiometerTargets = [100,100,100,100,100,100]
potentiometerMax = 255
potentiometerMin = 0

tunings = (1,0.1,0.05)
pids = []

pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)

for i in range(0,5):
    initializePid(i)

while running:
    updateTargets()
    currentPotentiometers = readPotentiometers()
    updateMotorDrivers(currentPotentiometers)

def initializePid(index):
    pid[index] = PID(tunings[0], tunings[1], tunings[3], setpoint=(potentiometerMax - potentiometerMin)/2)
    pid[index].output_limits = (-255, 255)

def updateTargets()
    dPad = joystick.get_hat()
    velocities = [
        joystick.get_axis(0),
        joystick.get_axis(1),
        joystick.get_axis(2),
        joystick.get_axis(3),
        dPad[0],
        dPad[1]]

    for index, velocity in enumerate(velocities):
        target = potentiometerTargets[index]
        target += velocity
        if(target > potentiometerMax):
            target = potentiometerMax
        if(target < potentiometerMin):
            target = potentiometerMin
        potentiometerTargets[index] = target

def updateMotorDrivers(currentPotentiometers):
    for index, potentionmeter in enumerate(currentPotentiometers):
        updatePid(potentionmeter, index)

def updatePid(currentPotentiometer, motorIndex):
    pulseWidth = pid[motorIndex](currentPotentiometer)
    direction = pulseWidth > 0
    motorAndDirection = motorIndex * 2 + direction
    motorDriverArduino.write([motorAndDirection,pulseWidth])

def readPotentiometers():
    potentiometers = potentiometerArduino.read(potentiometerArduino.inWaiting())
    print ("potentiometers: ")
    print (msg)
    return potentiometers