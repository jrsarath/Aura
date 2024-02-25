import os
import time
import wave
import struct
import pyaudio
import tempfile
import pvporcupine
from styletts2 import tts
from pydub import AudioSegment
from pydub.playback import _play_with_ffplay
from dotenv import load_dotenv
import speech_recognition as sr


# Load env variables
load_dotenv()
# PyAudio
pa = pyaudio.PyAudio()
# Initialize hotword listener
env_variable_value = os.getenv("PICOVOICE_API_KEY")
porcupine = pvporcupine.create(access_key=env_variable_value, keywords=['picovoice'])
recorder = None
# Initialize TTS model
TTS = tts.StyleTTS2()

#  convert text to speech & play
def speak(text, output_file=f'{tempfile.gettempdir()}/output-{time.time()}.wav'):
    TTS.inference(text, output_wav_file=output_file)
    audio = AudioSegment.from_wav(output_file)
    _play_with_ffplay(audio)
    os.remove(output_file)
    return
    
def listen_for_hotword():
    try:
        print("Listening for hotword... Press Ctrl+C to exit")
        recorder = pa.open(
                    rate=porcupine.sample_rate,
                    channels=1,
                    format=pyaudio.paInt16,
                    input=True,
                    frames_per_buffer=porcupine.frame_length)
        while True:
            pcm = recorder.read(porcupine.frame_length)
            pcm = struct.unpack_from("h" * porcupine.frame_length, pcm)
            result = porcupine.process(pcm)
            if result >= 0:
                print("Hotword detected!")
                return True
    except KeyboardInterrupt:
        print("Stopping...")
    # finally:
        # recorder.close()
        # pa.terminate()
        # porcupine.delete()

def speech_recogniztion():
    # obtain audio from the microphone
    r = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening...")
        audio = r.listen(source)
    print("Transcribing...")
    transcript = r.recognize_whisper(audio, model="medium", translate=True)
    print("Transcript:", transcript)
    return transcript


if __name__ == "__main__":
    listen_for_hotword()