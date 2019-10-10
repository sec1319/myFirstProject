import RPi.GPIO as GPIO
from time import sleep

def main():
	led = 18
	switch = 17
	state = 1
	GPIO.setmode(GPIO.BCM)
	GPIO.setwarnings(False)
	GPIO.setup(led, GPIO.OUT)
	GPIO.setup(switch, GPIO.IN, GPIO.PUD_UP)
	
	try:
		while True:
			if GPIO.input(switch) == 0:
				while True:
					if GPIO.input(switch) == 1:
						state = not state
						GPIO.output(led, state)
						sleep(0.2)
						break
	finally:
		print('END')

if __name__ == '__main__':
	main()
