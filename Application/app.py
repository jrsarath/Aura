# -----------------------------------------------------------
# JARVIS TEST APPLICATION
# DESC: AN ATTEMPT TO TURN A DREAM INTO REALITY
# GOAL: Making an Ai Virtual assistance which doesnt spies on you.
#       not Exposing/Sending any data from device/program to any services/websites
#       Please refer to privacy section for details about Data Privacy & Data control
#       this project is open-source and transparent,
#       user always will be in full control of the program and its Data control
# Version: 0.0.1-Alpha
# Copyright © 2019 - Jr Sarath [https://github.com/jrsarath/jessica]
# -----------------------------------------------------------

# IMPORTS
# ---- SYSTEM IMPORTS
import datetime
import requests
import json
from colorama import Fore, Back, Style
# ---- TTS, SPEECH & SOUND IMPORTS
import speech_recognition as sr
from playsound import playsound
# CONFIG IMPORTS
from Config.config import *
# CORE IMPORTS
from Core.speak import *
# SKILLS IMPORT
from Skills.Query.weather import *
from Skills.Query.clock import *

# INIT
print(Fore.BLUE + "Initiating JARVIS")
print(Fore.GREEN + "JARVIS - Version: 0.0.1")

get_time()

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
