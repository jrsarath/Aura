from styletts2 import tts
# No paths provided means default checkpoints/configs will be downloaded/cached.
TTS = tts.StyleTTS2()
# Optionally create/write an output WAV file.
out = TTS.inference("Hello there, I am now a python package.", output_wav_file="test.wav")
print(TTS)