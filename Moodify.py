import pyowm
from json import load
from urllib2 import urlopen
from geoip import geolite2
import datetime
import spotify
import time
import serial

#PULL WEATHER AND TEMPERATURE FROM INTERNET
ip = load(urlopen('http://jsonip.com'))['ip']
match = geolite2.lookup(ip)

owm = pyowm.OWM('c1fdcae65d6a8baaf32140250ac42d93')

obs = owm.weather_at_coords(match.location[0], match.location[1])

w = obs.get_weather()
temp = w.get_temperature()['temp'] - 273
weather = w.get_status()
if len(weather) > 6:
	weather = weather[:6]
hour = datetime.datetime.now().hour
time_of_day = ""
if hour > 6 and hour < 18:
        time_of_day = "Daytime"
elif hour >= 18 or hour <=6:
        time_of_day = "Nighttime"

print
print "Moodify"
print "-------"
print
print "%s - It is %dC and %s outside." % (time_of_day, temp, weather)
print

#CHOOSE AND PLAY SONG

ser = serial.Serial('/dev/ttyACM0')
session = spotify.Session()
audio = spotify.AlsaSink(session)

#log in
session.login('ethanxrosen','2x3bvQAke7P2')
while session.connection.state != 1:
	session.process_events()
	time.sleep(0.5)



old_song = ""

while True:

	mood = int(ser.read(1))
	if mood is 0:
		track_id = "4iu49FeQQGiUh2Dn1A8qCl" #normal
	elif mood is 1:
		track_id = "04KTF78FFg8sOHC1BADqbY" #hot
	elif mood is 2:
		track_id = "451GvHwY99NKV4zdKPRWmv" #rainy
	elif mood is 3:
		track_id = "67NoL59qSZbk6dzmxJPvU7" #night

	song = "spotify:track:" + track_id
	if song != old_song:
		old_song = song

		track = session.get_track(song)
		track.load()
		session.player.load(track)
		rc = session.player.play()