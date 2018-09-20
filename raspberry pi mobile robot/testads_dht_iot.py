import httplib, urllib
import Adafruit_ADS1x15
import time
import RPi.GPIO as GPIO
import Adafruit_DHT

sensor = Adafruit_DHT.DHT11
adc = Adafruit_ADS1x15.ADS1115()
sleep = 15
key = '4GVGTMTNUX6AIQLE'
GAIN = 1
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(23,GPIO.OUT)
pin = 18

while True:
	water_level = adc.read_adc(0, gain=GAIN)
	sea_level = adc.read_adc(1, gain=GAIN)
	water_flow = adc.read_adc(2, gain=GAIN)
	#humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)
	print('water ={0:0.1f}  sea={1:0.1f} flow={1:0.1f}'.format(water_level, sea_level, water_flow))
	params = urllib.urlencode({'field1':water_level, 'field2':water_level, 'field3':water_level, 'field4':sea_level, 'field5':water_flow, 'key':key})
	headers = {"Content-typZZe":"application/x-www-form-urlencoded","Accept": "text/plain"}
	conn = httplib.HTTPConnection("api.thingspeak.com:80")
	conn.request("POST", "/update", params, headers)
	response = conn.getresponse()
	print response.status, response.reason
	data = response.read()
	conn.close()
	if water_level > 13000:
		print "water pump on"
		GPIO.output(23,GPIO.HIGH)
		time.sleep(2)
	if water_level < 13000:
		print "water pump off"
		GPIO.output(23,GPIO.LOW)
		if sea_level > 13000:
			print "barrier closed"
		if sea_level < 13000:
			print "barrier open"
		time.sleep(2)
	time.sleep(sleep)
