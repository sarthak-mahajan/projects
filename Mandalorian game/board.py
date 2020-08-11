from colorama import *
import numpy as np
class board:
	def __init__(self):
		self.__arr=[]
		self.__rows=34
		self.__column=94
		for x in range(1,self.__rows):
			self.__arr2=[]
			for y in range(1,self.__column):
				if x == 1 or x == self.__rows-1:
					self.__arr2.append("T"+Back.RED)
				else:
					self.__arr2.append(" "+Back.CYAN)	
			self.__arr.append(self.__arr2)	
		self.__mat=np.asarray(self.__arr)						
	def printboard(self):
		for x in range(1,self.__rows):
			for y in range(1,self.__column):
				print(self.__mat[x-1][y-1],end='')
			print()

	def matt(self):
		return self.__mat