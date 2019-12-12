# -----------------------------------------------------------
# JESSICA TEST APPLICATION
# DESC: AN ATTEMPT TO TURN A DREAM INTO REALITY
# Version: 0.0.1-Alpha
# Copyright © 2019 - Jr Sarath [https://github.com/jrsarath/jessica]
# -----------------------------------------------------------

# IMPORTS
from colorama import Fore, Back, Style
import speech_recognition as sr
from gtts import gTTS
from io import BytesIO
from playsound import playsound
from tempfile import TemporaryFile
import contextlib
with contextlib.redirect_stdout(None):
    import pygame

# INIT
print(Fore.GREEN + "Jessica - Version: 0.0.1")
'''
tts = pyttsx3.init()
voices = tts.getProperty('voices')
print("Available system voices are ")
for x in range(len(voices)):
    print(voices[x])
'''

# FUNCTIONS
def say(text):
    tts = gTTS(text=text, lang='en-us')
    fp = BytesIO()
    tts.write_to_fp(fp)
    fp.seek(0)
    pygame.mixer.init()
    pygame.mixer.music.load(fp)
    pygame.mixer.music.play()
    while pygame.mixer.music.get_busy():
        pygame.time.Clock().tick(10)

say("Hi, I'm Jessica. Nice to meet you!")

'''
# obtain audio from the microphone
r = sr.Recognizer()
with sr.Microphone() as source:
    print("Say something!")
    audio = r.listen(source)

# recognize speech using Sphinx
try:
    print("Recognized: " + r.recognize_sphinx(audio))
    tts = gTTS('hello')
    tts.save('hello.mp3')
except sr.UnknownValueError:
    print("Sphinx could not understand audio")
except sr.RequestError as e:
    print("Sphinx error; {0}".format(e))
'''