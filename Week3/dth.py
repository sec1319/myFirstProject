import Adafruit_DHT as dht
import time

#Define DHT module
sensor = dht.DHT11
PIN = 4 

while True:
	hum, tem = dht.read_retry(sensor, PIN)

	if hum is None or tem is None:
		print('Failed to get data')
		pass

	else:
		print('Temperature = {0:0.1f}*C Humidity = {1:0.1f}%'.format(tem, hum))
		time.sleep(2)


