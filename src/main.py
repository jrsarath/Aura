from styletts2 import tts
import whisper

from langchain.chains import LLMChain
from langchain_community.llms import LlamaCpp
from langchain.callbacks.manager import CallbackManager
from langchain.callbacks.streaming_stdout import StreamingStdOutCallbackHandler

# # No paths provided means default checkpoints/configs will be downloaded/cached.
# TTS = tts.StyleTTS2()
# # Optionally create/write an output WAV file.
# out = TTS.inference("Hello there, I am now a python package.", output_wav_file="test.wav")

# model = whisper.load_model("medium")
# result = model.transcribe("test.wav")
# print(result["text"])

# Make sure the model path is correct for your system!
callback_manager = CallbackManager([StreamingStdOutCallbackHandler()])
llm = LlamaCpp(
    model_path="lib/llama-2-7b-chat.gguf",
    temperature=0.75,
    max_tokens=2000,
    top_p=1,
    callback_manager=callback_manager,
    verbose=False,
)

prompt = 'What is the highest point in earth'
llm.invoke(prompt)