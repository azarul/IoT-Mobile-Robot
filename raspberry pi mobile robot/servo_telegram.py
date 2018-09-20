import time, datetime
import RPi.GPIO as GPIO
import telepot
from telepot.loop import MessageLoop

cradle = 18

now = datetime.datetime.now()
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO.setup(18, GPIO.OUT)
p = GPIO.PWM(18,20)
 
GPIO.setup(cradle, GPIO.OUT)
GPIO.output(cradle, 0)  #OFF initially

def action(msg):
    chat_id = msg['chat']['id']
    command = msg['text']

    print 'Received: %s' % command

    if 'on' in command:
        message = "Turned on "
        if 'cradle' in command:
            message = message + "cradle "
            GPIO.output(cradle, 1)
            p.start(7.5)
        message = message + "system"
        telegram_bot.sendMessage (chat_id, message)

    if 'off' in command:
        message = "Turned off "
        if 'cradle' in command:
            message = message + "cradle "
            GPIO.output(cradle, 0)
            p.stop()
        message = message + "system"
        telegram_bot.sendMessage (chat_id, message)

telegram_bot = telepot.Bot('579763862:AAE67SjL-0KqofS6V3Kp4R3txfEBBzal6O0')
print (telegram_bot.getMe())

MessageLoop(telegram_bot, action).run_as_thread()
print 'Up and Running....'

try:
    while 1:
        p.ChangeDutyCycle(4)
        time.sleep(2)
        p.ChangeDutyCycle(2.5)
        time.sleep(2)
        p.ChangeDutyCycle(4)
        time.sleep(2)
        p.ChangeDutyCycle(2.5)
        time.sleep(2)
