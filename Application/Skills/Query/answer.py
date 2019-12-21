# IMPORTS
from Config.config import *
from Core.speak import *
import requests
from bs4 import BeautifulSoup

# FUNCTIONS
def get_answers(query):
    headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.186 Safari/537.36'}
    r = requests.get('https://www.google.com/search?q='+query, headers=headers)
    soup = BeautifulSoup(r.text, 'lxml')
    result = soup.find('div', class_='Z0LcW')
    return result.text
