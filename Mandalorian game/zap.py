from colorama import *
import random
class beam:
	def __init__(self):
		self.__zap=[]
		# can start from 0 in xco
		# self.xco=random.randint(40,78)
		self.__xco=78
		self.__yco=random.randint(7,24)
		self.__zno=random.randint(3,6)
		self.__i=random.randint(1,4)
		self.__cod=[]
		self.__v=1
		self.__oldv=self.__v
		if self.__i == 1 :
			for x in range(0,self.__zno):
				self.__zap.append(Back.RED+'|')
		if self.__i == 2 :
			for x in range(0,self.__zno):
				self.__zap.append(Back.RED+'-')
		if self.__i == 3:
			for x in range(0,self.__zno):
				self.__zap.append(Back.RED+'@')

	def app(self,grid):
		if self.__i==1:
			for x in range(0,self.__zno):
				grid[self.__yco+x][self.__xco]=self.__zap[x]
		if self.__i==2:
			for x in range(0,self.__zno):
				grid[self.__yco][x+self.__xco]=self.__zap[x]
		if self.__i==3:
			for x in range(0,self.__zno):
				grid[self.__yco-x][self.__xco+x]=self.__zap[x]


	def disapp(self,grid):
		if self.__i==1:
			for x in range(0,self.__zno):
				grid[self.__yco+x][self.__xco]=Back.CYAN+" "
		if self.__i==2:
			for x in range(0,self.__zno):
				grid[self.__yco][x+self.__xco]=Back.CYAN+" "
		if self.__i==3:
			for x in range(0,self.__zno):
				grid[self.__yco-x][self.__xco+x]=Back.CYAN+" "
		
	def back(self,grid):
		if self.__xco-self.__v >=0:
			self.disapp(grid)
			self.__xco=self.__xco-self.__v
			self.app(grid)
		else:
			self.disapp(grid)
			self.__zno=self.__zno-1
			self.app(grid)

	def codlist(self):
		self.__cod.clear()
		if self.__i == 1:
			for x in range(0,self.__zno):
				self.__cod.append([self.__xco,self.__yco+x])
		if self.__i == 2:
			for x in range(0,self.__zno):
				self.__cod.append([self.__xco+x,self.__yco])
		if self.__i == 3:
			for x in range(0,self.__zno):
				self.__cod.append([self.__xco+x,self.__yco-x])
		return self.__cod

	def exterm(self):
		self.__zap.clear()	
		self.__zno=0	

	def boost(self):
		self.__v=5	

	def revspeed(self):
		self.__v=self.__oldv








       