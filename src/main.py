from ai import get_response
from speech import speak

def conversation_loop():
    while True:
        user_input = input("You: ")
        if user_input.lower() == 'exit':
            print("Exiting the conversation.")
            break
        
        response = get_response(user_input)
        speak(response)
        print("AI: " + response)

def main():
    print("Starting conversation...")
    conversation_loop()

if __name__ == "__main__":
    main()