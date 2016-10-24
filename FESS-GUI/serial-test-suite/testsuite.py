import sys
import math
import time
import serial
import struct

COMMAND_GET_VELO_FLOA = 0b00000000
COMMAND_GET_ACCE_FLOA = 0b00000001
COMMAND_GET_JERK_FLOA = 0b00000010
COMMAND_GET_LOWE_DISP = 0b00000011
COMMAND_GET_UPPE_DISP = 0b00000100
COMMAND_GET_ROTA_POSI = 0b00000101
COMMAND_GET_ALLD_FLOA = 0b00111111

COMMAND_SET_EMER_STOP = 0b01000000
COMMAND_SET_VELO_FLOA = 0b01000001
COMMAND_SET_ACCE_FLOA = 0b01000010
COMMAND_SET_JERK_FLOA = 0b01000011
COMMAND_SET_ALLD_FLOA = 0b01111111

COMMAND_ERR_EMER_STOP = 0b10000000
COMMAND_ERR_FIFO_FULL = 0b10000001

COMMAND_RES_VELO_FLOA = 0b11000000
COMMAND_RES_ACCE_FLOA = 0b11000001
COMMAND_RES_JERK_FLOA = 0b11000010
COMMAND_RES_LOWE_DISP = 0b11000011
COMMAND_RES_UPPE_DISP = 0b11000100
COMMAND_RES_ROTA_POSI = 0b11000101
COMMAND_RES_ALLD_FLOA = 0b11111111


def binary(num): 
	return ''.join(bin(ord(c)).replace('0b', '').rjust(8, '0') for c in struct.pack('!f', num))

def derivative(value,prev_value):
	return value-prev_value;

def writeCommand(device, command):
	device.write(struct.pack('!B',command))

def writeData(device, data):
	sdat = binary(data)
	device.write(struct.pack('!B',int(sdat[24:32],2))) 
	device.write(struct.pack('!B',int(sdat[16:24],2)))
	device.write(struct.pack('!B',int(sdat[8:16],2)))
	device.write(struct.pack('!B',int(sdat[0:8],2)))

def readCommand(device):
	command = device.read()		

key = 0
vel = 0
acc = 0
pos = 0

path = sys.argv[1]

s = serial.Serial(path)

while(True):

	

	prev_vel = vel
	prev_acc = acc

	vel = math.sin(key*1.6+math.cos(key*1.7)*2)*10 + math.sin(key*1.2+0.56)*20 + 26
	acc = derivative(vel,prev_vel)
	jer = derivative(acc,prev_acc)

	pos += vel

	udx = 2*math.cos(key) - math.cos(2*key)
	udy = 2*math.sin(key) - math.sin(2*key)
	ldx = 2*math.cos(key + 0.1) - math.cos(2*key + 0.1)
	ldy = 2*math.sin(key + 0.1) - math.sin(2*key + 0.1)

	rpx = math.sin(pos/100)
	rpy = math.cos(pos/100)

	key += 0.01

	writeCommand(s, COMMAND_RES_ALLD_FLOA)
	writeData(s, vel)
	writeData(s, acc)
	writeData(s, jer)

	writeData(s, ldx)
	writeData(s, ldy)
	writeData(s, udx)
	writeData(s, udy)

	writeData(s, rpx)
	writeData(s, rpy)

	time.sleep(0.10)

# Citations: 
#	Function: 	binary()
#	Author:		Dan Lecocq
#	URL:		http://stackoverflow.com/questions/16444726/binary-representation-of-float-in-python-bits-not-hex
