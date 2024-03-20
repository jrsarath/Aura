#!/usr/bin/env python
from dotenv import load_dotenv
from ai import get_response
from speech import speak, listen_for_hotword, speech_recogniztion

# Load env variables
load_dotenv()

def conversation_loop(user_text):
    response = get_response(user_text)
    print("Aura: " + response)
    speak(response) 
    return
        

def main():
    while True:
        if listen_for_hotword():
            print('Starting recognizion...')
            transcript = speech_recogniztion()
            conversation_loop(transcript)

if __name__ == "__main__":
    main()