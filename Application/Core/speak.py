# IMPORTS
from gtts import gTTS
import pyttsx3
from io import BytesIO
import contextlib
with contextlib.redirect_stdout(None):
    import pygame

# FUNCTIONS
def say(text):
    '''
        Jessica uses Google TTS as her voice right now.
        Might switch to Some device level TTS Engines later on
        Sadly there's no good natural TTS for Linux is available right now
    '''
    tts = gTTS(text=text, lang='en-us')
    fp = BytesIO()
    tts.write_to_fp(fp)
    fp.seek(0)
    pygame.mixer.init()
    pygame.mixer.music.load(fp)
    pygame.mixer.music.play()
    while pygame.mixer.music.get_busy():
        pygame.time.Clock().tick(10)

def speak(text):
    engine = pyttsx3.init()
    engine.setProperty('rate', 175)
    engine.say(text)
    engine.runAndWait()