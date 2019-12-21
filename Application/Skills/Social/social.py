# CORE IMPORTS
from Core.speak import *

# FUNCTIONS
speak("Good Morning, Its " + datetime.datetime.now().strftime("%H:%M %p") + " . The weather in " + city + " is "+ weather.condition() +" , with temperature of "+ weather.temperature() +" degree "+ temperature_unit)