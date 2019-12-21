# CORE & CONFIG IMPORTS
from Config.config import *
from Core.speak import *
# LIBRARIES IMPORT
from yahoo_weather.weather import YahooWeather
from yahoo_weather.config.units import Unit

# VARIABLES
yahoo = YahooWeather(APP_ID="p4McgJ34",
                     api_key="dj0yJmk9aVBNcUVDOWRGTVdnJmQ9WVdrOWNEUk5ZMmRLTXpRbWNHbzlNQS0tJnM9Y29uc3VtZXJzZWNyZXQmc3Y9MCZ4PTAz",
                     api_secret="d286fbd2a72da8f2fc239c21b73683be07dae6a9")
if temperature_unit == 'celsius':
    yahoo_unit = Unit.celsius
else:
    yahoo_unit = Unit.fahrenheit
yahoo.get_yahoo_weather_by_city(city, yahoo_unit)

# FUNCTIONS
class weather:
    def condition():
        return yahoo.condition.text
    def temperature():
        return str(yahoo.condition.temperature)

def get_temperature(mode):
    if mode == 'full':
        speak("Its currently "+weather.condition()+" in kolkata with temperature of "+weather.temperature()+" degrees "+temperature_unit)
    else:
        speak("Its currently "+weather.temperature()+" degrees "+temperature_unit)