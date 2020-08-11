from colorama import *
import random
import time
class coins:
	def __init__(self):
		self.__coin=[]
		self.__xco=random.randint(10,78)
		self.__yco=random.randint(1,18)
		self.__cno=random.randint(1,9)
		self.__cod=[]	
		self.__v=1	
		self.__oldv=self.__v
		for x in range(0,self.__cno):
			self.__coin.append(Back.YELLOW+'$')

	def app(self,grid):
		for x in range(0,self.__cno):
			grid[self.__yco][x+self.__xco]=self.__coin[x]

	def disapp(self,grid):
		for x in range(0,self.__cno):
			grid[self.__yco][x+self.__xco]=Back.CYAN+" "

	def delete(self,grid):
		self.disapp(grid)
		self.__xco=self.__xco+self.__v
		self.__cno=self.__cno-1
		self.app(grid)

	def back(self,grid):
		grid[self.__yco][self.__xco] = Back.CYAN+" "
		if self.__xco-self.__v >=0:
			self.disapp(grid)
			self.__xco=self.__xco-self.__v
			self.app(grid)
		else:
			self.disapp(grid)
			self.__cno=self.__cno-1
			self.app(grid)

	def codlist(self):
		self.__cod.clear()
		for x in range(0,self.__cno):
			self.__cod.append([self.__xco+x,self.__yco])
		return self.__cod

	def boost(self):
		self.__v=5
	
	def revspeed(self):
		self.__v=self.__oldv


class allbullet:
	def __init__(self,xco,yco,grid):
		self._bno=2
		self._xco=xco
		self._yco=yco

	def exterm(self):
		self._bno=1
		self._xco=91


class bullet(allbullet):
	def __init__(self,xco,yco,grid):
		self.__bu=[]
		# self.xco=xco+1
		# self.yco=yco+1
		self.__v=1
		self.__oldv=self.__v
		self.__bu.append(Back.WHITE+'?')
		super().__init__(xco+1,yco+1,grid)
		self.app(grid)

	def front(self,grid,zapp_cod,obj):
		self.disapp(grid)
		if self._xco+self.__v < 91:
			for x in range(-2,2):
				if [self._xco+x,self._yco] in zapp_cod :
					super().exterm()
					self.__ob=obj
					self.__ob.disapp(grid)
					self.__ob.exterm()
					self.__bu[0]=Back.CYAN+" "
					return 
			self._xco=self._xco+self.__v
			self.app(grid)
		else:
			self.__bu[0]=Back.CYAN+" "

	

	def front2(self,grid,zapp_cod,obj):
		self.disapp(grid)
		if self._xco+self.__v < 92:
			for x in range(0,1):
				if [self._xco+x,self._yco] in zapp_cod :
					super().exterm()
					self.__ob=obj
					self.__ob.die()
					return
			self._xco=self._xco+self.__v
			self.app(grid)
		else:
			self.__bu[0]=Back.CYAN+" "

	def app(self,grid):
		for x in range(1,self._bno):
			grid[self._yco][self._xco]=self.__bu[0]

	def disapp(self,grid):
		for x in range(1,self._bno):
			grid[self._yco][self._xco]=Back.CYAN+" "

	def boost(self):
		self.__v=5

	def revspeed(self):
		self.__v=self.__oldv

class enbullet(allbullet):
	def __init__(self,xco,yco,grid):
		self.__bu=[]
		# self.xco=xco-1
		# self.yco=yco-1
		self.__v=3
		self.__bu.append(Back.RED+'=')
		super().__init__(xco-1,yco+1,grid)
		self.app(grid)

	def back(self,grid,zapp_cod,obj):
		self.disapp(grid)
		if self._xco-self.__v > 0:
			for x in range(0,1):
				if [self._xco+x,self._yco] in zapp_cod :
					self.exterm()
					self.__ob=obj
					self.__ob.die()
					return
			self._xco=self._xco-self.__v
			self.app(grid)
		else:
			self.__bu[0]=Back.CYAN+" "

	def app(self,grid):
		for x in range(1,self._bno):
			grid[self._yco][self._xco]=self.__bu[0]

	def disapp(self,grid):
		for x in range(1,self._bno):
			grid[self._yco][self._xco]=Back.CYAN+" "

	def exterm(self):
		self._bno=1
		self._xco=0


	

class magnet:
	def __init__(self,grid):
		self.__mag=[]
		self.__co=[]
		self.__xco=random.randint(75,78)
		self.__yco=random.randint(3,18)
		self.__v=1
		self.__range=25
		self.__lis=[]
		self.__lis2=[]
		self.__flag=0
		for x in range(1,self.__range+1):
			self.__lis.append(x+self.__xco)
		for x in range(1,self.__range+1):
			self.__lis2.append(self.__xco-x)
		self.__oldv=self.__v
		self.__mag.append(Back.BLUE+'U')
		self.app(grid)

	def app(self,grid):
		grid[self.__yco][self.__xco]=self.__mag[0]

	def disapp(self,grid):
		grid[self.__yco][self.__xco]=Back.CYAN+" "

	def back(self,grid):
		self.disapp(grid)
		if self.__xco-self.__v >= 2:
			self.__xco=self.__xco-self.__v
			self.app(grid)
		else:
			self.__mag[0]=Back.CYAN+" "
			self.__flag=1

	def attract(self,grid,obj,ch):
		self.__lis.clear()
		self.__lis2.clear()
		self.__ch=ch
		for x in range(1,self.__range+1):
			self.__lis.append(x+self.__xco)
		for x in range(1,self.__range+1):
			self.__lis2.append(self.__xco-x)
		self.__obj=obj
		self.__lis3=self.__obj.codlist()
		for x in self.__lis3:
			# print(x[0])
			# print(self.lis)
			if x[0] in self.__lis:
				self.__obj.magmoveleft(grid,self.cod(),self.__ch,self.__flag)
			if x[0] in self.__lis2:
					self.__obj.magmoveright(grid,self.cod(),self.__ch,self.__flag)
			# if x[0] not in self.lis:
			# 	if x[0] not in self.lis2:
			# 		# print("deattract")
			# 		self.obj.revspeed()

	def boost(self):
		self.__v=5

	def revspeed(self):
		self.__v=self.__oldv

	def exterm(self):
		self.__mag[0]=Back.CYAN+" "

	def cod(self):
		self.__co.clear()
		self.__co.append([self.__xco,self.__yco])
		return self.__co


class boost:
	def __init__(self,grid):
		self.__boos=[]
		self.__xco=78
		self.__yco=random.randint(1,18)
		self.__v=1	
		self.__oldv=self.__v
		self.__cod=[]
		self.__boos.append(Back.BLUE+'+')
		self.app(grid)

	def app(self,grid):
		grid[self.__yco][self.__xco]=self.__boos[0]

	def disapp(self,grid):
		grid[self.__yco][self.__xco]=Back.CYAN+" "

	def back(self,grid):
		self.disapp(grid)
		if self.__xco-self.__v >= 0:
			self.__xco=self.__xco-self.__v
			self.app(grid)
		else:
			self.__boos[0]=Back.CYAN+" "

	def exterm(self):
		self.__boos[0]=Back.CYAN+" "

	def speed(self,ob1,ob2,ob3):
		self.__ob1=ob1
		self.__ob2=ob2
		self.__ob3=ob3
		for x in self.__ob1:
			x.boost()
		for x in self.__ob2:
			x.boost()
		for x in self.__ob3:
			x.boost()
		
	def reset(self,ob1,ob2,ob3):
		self.__ob1=ob1
		self.__ob2=ob2
		self.__ob3=ob3
		for x in self.__ob1:
			x.revspeed()
		for x in self.__ob2:
			x.revspeed()
		for x in self.__ob3:
			x.revspeed()
		
	def cood(self):
		self.__cod.clear()
		self.__cod.append([self.__xco,self.__yco])
		return self.__cod

	def boost(self):
		self.__v=5

	def revspeed(self):
		self.__v=self.__oldv



	
	











