# IMPORTS
from Config.config import *
from Core.speak import *
import datetime

# FUNCTIONS
def time():
    time = datetime.datetime.now().time()
    return time.strftime('%I:%M %p')

def get_time():
    speak("Its "+time())