import mechanize
import re

from ctypes import cdll

lib = cdll.LoadLibrary('./libfoo.so')

def page_source(url):
	br = mechanize.Browser()
	page = br.open(url)
	source = page.read()
	return source; 

class B_View:
	def __init__(self, size, depth):
		self.obj = lib.OverGroup_New(size, depth)
	def TakeIn(self, text):
		lib.TakeIn(self.obj, text)
	def MyFamily(self, word):
		lib.MyFamily(self.obj, word)
	def __del__(self):
		lib.Finish(self.obj)
	def Finish(self):
		lib.Finish(self.obj)
url = " "
b = B_View(7000, 10) # Create lib class and use that as base. 

while(1 == 1):
	url = raw_input("Enter url: ")
	if url == "XXX":
		break
	if url[0] != 'h':
		url = "http://" + url
	b.TakeIn(page_source(url))
	find_me = raw_input("Look For: ")
	b.MyFamily(find_me)
#b.Finish()
