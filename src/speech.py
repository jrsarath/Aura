import os
import whisper
from styletts2 import tts
from pydub import AudioSegment
from pydub.playback import play


# Initialize TTS model
TTS = tts.StyleTTS2()
# Load Whisper model
model = whisper.load_model(name="medium", download_root="lib")

#  convert text to speech & play
def speak(text, output_file="temp/output.wav"):
    TTS.inference(text, output_wav_file=output_file)
    audio = AudioSegment.from_wav(output_file)
    play(audio)
    os.remove(output_file) 
    return; 
