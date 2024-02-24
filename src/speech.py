import os
import time
import wave
import struct
import whisper
import pyaudio
import tempfile
import pvporcupine
from styletts2 import tts
from pydub import AudioSegment
from pydub.playback import play
from dotenv import load_dotenv

# Load env variables
load_dotenv()
# Initialize hotword listener
porcupine = None
pa = pyaudio.PyAudio()
recorder = None
# Initialize TTS model
TTS = tts.StyleTTS2()
# Load Whisper model
model = whisper.load_model(name="medium", download_root="lib")

#  convert text to speech & play
def speak(text, output_file=f'{tempfile.gettempdir()}/output-{time.time()}.wav'):
    TTS.inference(text, output_wav_file=output_file)
    audio = AudioSegment.from_wav(output_file)
    play(audio)
    os.remove(output_file)
    return; 

def init_hotword_listener():
    env_variable_value = os.getenv("PICOVOICE_API_KEY")
    global porcupine
    porcupine = pvporcupine.create(
        access_key=env_variable_value,
        keywords=['picovoice'])
    global recorder
    recorder = pa.open(
        rate=porcupine.sample_rate,
        channels=1,
        format=pyaudio.paInt16,
        input=True,
        frames_per_buffer=porcupine.frame_length)
    return
    
    
def listen_for_hotword():
    try:
        print("Listening for hotword... Press Ctrl+C to exit")
        while True:
            pcm = recorder.read(porcupine.frame_length)
            pcm = struct.unpack_from("h" * porcupine.frame_length, pcm)
            result = porcupine.process(pcm)
            if result >= 0:
                print("Hotword detected!")
    except KeyboardInterrupt:
        print("Stopping...")
    finally:
        recorder.close()
        pa.terminate()
        porcupine.delete()


if __name__ == "__main__":
    speak("Hi, how are you")