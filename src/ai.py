from langchain.chains import LLMChain
from langchain_community.llms import LlamaCpp
from langchain.callbacks.manager import CallbackManager
from langchain.callbacks.streaming_stdout import StreamingStdOutCallbackHandler
from halo import Halo

callback_manager = CallbackManager([StreamingStdOutCallbackHandler()])
llm = LlamaCpp(
    model_path="lib/llama-2-7b-chat.gguf",
    max_tokens=2000,
    top_p=1,
    callback_manager=callback_manager,
    verbose=False,
)

def get_response(prompt):
    # with Halo(text='Loading', spinner='dots'):
    response = llm.invoke(prompt)
    return response