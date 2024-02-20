from langchain.chains import LLMChain
from langchain_community.llms import LlamaCpp
from langchain.callbacks.manager import CallbackManager
from langchain.callbacks.streaming_stdout import StreamingStdOutCallbackHandler
from langchain.chains import LLMChain
from langchain.memory import ConversationBufferMemory
from langchain_experimental.chat_models import Llama2Chat
from langchain.prompts.chat import (
    ChatPromptTemplate,
    HumanMessagePromptTemplate,
    MessagesPlaceholder,
)
from langchain.schema import SystemMessage
from halo import Halo

callback_manager = CallbackManager([StreamingStdOutCallbackHandler()])
llm = LlamaCpp(
    model_path="lib/llama-2-7b-chat.Q6_K.gguf",
    temperature=0.75,
    max_tokens=2000,
    top_p=1,
    verbose=False,
    streaming=False,
)
model = Llama2Chat(llm=llm)
memory = ConversationBufferMemory(memory_key="chat_history", return_messages=True)
template_messages = [
    SystemMessage(content="You are a helpful assistant."),
    MessagesPlaceholder(variable_name="chat_history"),
    HumanMessagePromptTemplate.from_template("{text}"),
]
prompt_template = ChatPromptTemplate.from_messages(template_messages)
chain = LLMChain(llm=model, prompt=prompt_template, memory=memory)


def get_response(text):
    with Halo(text='Loading', spinner='dots'):
        response = chain.invoke(input=text)
    return response["text"]