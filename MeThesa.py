import mechanize
import re
import random
import string
import sys

from ctypes import cdll

lib = cdll.LoadLibrary('./libfoo.so')

def page_source(url):
	if url[0] != 'h':
		url = "http://" + url
	br = mechanize.Browser()
	page = br.open(url)
	source = page.read()
	br.close()
	return source; 

class MeThesa:
	def __init__(self, size, depth):
		self.obj = lib.DirectGroup_New(size, depth)
	def TakeIn(self, text):
		lib.TakeIn(self.obj, text)
	def MyFamily(self, word, greater_than):
		lib.MyFamily(self.obj, word, int(greater_than))
	def Forget(self):
		lib.Forget(self.obj)
	def Translate(self, text):
		lib.Translate(self.obj, text)
	def End(self):
		lib.End(self.obj)

wiki = "https://en.wikipedia.org/wiki/"
wls = 7000
depth = 10
runs = raw_input("Enter number of pages to check:")
wls, depth = [int(x) for x in raw_input("Start MeThesa with -> wordlist size [space] relational depth: ").split()] 
T = MeThesa(wls, depth)
l_words = []
with open('./Dictionary_New.txt') as fm:
	l_words = fm.readlines()
for x in range(int(runs)):
	try:
		print(x)
		url_in = wiki+string.capwords(l_words[random.randint(1, len(l_words))])
		print("\n\nLooking into " + url_in)
		T.TakeIn(page_source(url_in))
	except ValueError:
		print("VALUE ERROR")
	except:
		print("NOT FOUND")
try:
	while(1 == 1):
		look = raw_input("ENTER SEARCH TERM: ")
		if(look == "XXX"):
			break
		greater_than = raw_input("FOR RELATIONSHIPS GREATER THAN: ")
		T.MyFamily(look, greater_than)
	while(1 == 1):
		word = raw_input("Enter First Word: ")
		if(word == "XXX"):
			break
		word1 = raw_input("Enter Second Word: ")
		T.OurR(word, word1)
except ValueError:
	print("VALUE ERROR")
except:
	print("NO GOOD")
	print(sys.exc_info()[0])
T.End()













