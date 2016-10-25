import sys
import math
import time
import serial
import struct

# Machine Command Codes
#------------------------------------------------
ICM_START                        = 0b00000001
ICM_STOP                         = 0b00000010
ICM_EMERGENCY_STOP               = 0b00000011
ICM_SET_VELOCITY                 = 0b00000100
ICM_SET_ACCELERATION             = 0b00000101
ICM_SET_JERK                     = 0b00000110

CCM_START                        = 0b10000001
CCM_STOP                         = 0b10000010
CCM_EMERGENCY_STOP               = 0b10000011
CCM_SET_VELOCITY                 = 0b10000100
CCM_SET_ACCELERATION             = 0b10000101
CCM_SET_JERK                     = 0b10000110

# Controller Command Codes
#------------------------------------------------
ICC_ERROR                        = 0b00100001
CCC_ERROR                        = 0b10100001

# Machine Data Codes
#------------------------------------------------
IDM_SEND_VELOCITY                = 0b01000001
IDM_SEND_ACCELERATION            = 0b01000010
IDM_SEND_JERK                    = 0b01000011
IDM_SEND_LOWER_DISPLACEMENT_X    = 0b01000100
IDM_SEND_LOWER_DISPLACEMENT_Y    = 0b01000101
IDM_SEND_UPPER_DISPLACEMENT_X    = 0b01000110
IDM_SEND_UPPER_DISPLACEMENT_Y    = 0b01000111
IDM_SEND_ROTATIONAL_POSITION_X   = 0b01001000
IDM_SEND_ROTATIONAL_POSITION_Y   = 0b01001001

CDM_SEND_VELOCITY                = 0b11000001
CDM_SEND_ACCELERATION            = 0b11000010
CDM_SEND_JERK                    = 0b11000011
CDM_SEND_LOWER_DISPLACEMENT_X    = 0b11000100
CDM_SEND_LOWER_DISPLACEMENT_Y    = 0b11000101
CDM_SEND_UPPER_DISPLACEMENT_X    = 0b11000110
CDM_SEND_UPPER_DISPLACEMENT_Y    = 0b11000111
CDM_SEND_ROTATIONAL_POSITION_X   = 0b11001000
CDM_SEND_ROTATIONAL_POSITION_Y   = 0b11001001

#endif // COMMANDS_H




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

	writeCommand(s, IDM_SEND_VELOCITY)
	writeData(s, vel)
	writeCommand(s, CDM_SEND_VELOCITY)

	writeCommand(s, IDM_SEND_ACCELERATION)
	writeData(s, acc)
	writeCommand(s, CDM_SEND_ACCELERATION)

	writeCommand(s, IDM_SEND_JERK)
	writeData(s, jer)
	writeCommand(s, CDM_SEND_JERK)

	writeCommand(s, IDM_SEND_LOWER_DISPLACEMENT_X)
	writeData(s, ldx)
	writeCommand(s, CDM_SEND_LOWER_DISPLACEMENT_X)

	writeCommand(s, IDM_SEND_LOWER_DISPLACEMENT_Y)
	writeData(s, ldy)
	writeCommand(s, CDM_SEND_LOWER_DISPLACEMENT_Y)

	writeCommand(s, IDM_SEND_UPPER_DISPLACEMENT_X)
	writeData(s, udx)
	writeCommand(s, CDM_SEND_UPPER_DISPLACEMENT_X)

	writeCommand(s, IDM_SEND_UPPER_DISPLACEMENT_Y)
	writeData(s, udy)
	writeCommand(s, CDM_SEND_UPPER_DISPLACEMENT_Y)

	writeCommand(s, IDM_SEND_ROTATIONAL_POSITION_X)
	writeData(s, rpx)
	writeCommand(s, CDM_SEND_ROTATIONAL_POSITION_X)

	writeCommand(s, IDM_SEND_ROTATIONAL_POSITION_Y)
	writeData(s, rpy)
	writeCommand(s, CDM_SEND_ROTATIONAL_POSITION_Y)

	time.sleep(0.01)

# Citations: 
#	Function: 	binary()
#	Author:		Dan Lecocq
#	URL:		http://stackoverflow.com/questions/16444726/binary-representation-of-float-in-python-bits-not-hex
