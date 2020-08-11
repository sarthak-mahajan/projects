from colorama import *
from scen import *
import random
import os

# class player:
# 	def __init__(self,x,y,life):
# 		self.__xco=x
# 		self.__yco=y
# 		self.__life=life

class mando:
	def __init__(self,x,y,velx,vely,life):
		self.__xco=x
		self.__yco=y
		self.__co=[]
		self.__co2=[]
		self.__flag=0
		self.__flag2=0
		self.__flag3=0
		self.__life=life
		self.__score=0
		self.__vely=vely
		self.__oldvely=vely
		self.__t=1
		self.__velx=velx
		self.__oldvelx=self.__velx
		self.__g=0.08
		self.__form = [ [Back.GREEN+"*", Back.GREEN+"*", Back.GREEN+"*"], [Back.GREEN+"<", Back.GREEN+"%", Back.GREEN+">"], [Back.GREEN+"^", Back.GREEN+":", Back.GREEN+"^"] ]
	
	def app(self,grid):
		for x in range(0,3):
			for y in range(0,3):
				grid[y+self.__yco][x+self.__xco]=self.__form[y][x]
	
	def disapp(self,grid):
		for x in range(0,3):
			for y in range(0,3):
				grid[y+self.__yco][x+self.__xco]=Back.CYAN+" "
		
	def moveright(self,grid):
		if self.__xco+self.__velx <= 89:
			self.disapp(grid)
			self.__xco=self.__xco+self.__velx
			self.app(grid)
		else:
			self.disapp(grid)
			self.__xco=89
			self.app(grid)


	def moveleft(self,grid):
		if self.__xco-self.__velx >= 0:
			self.disapp(grid)
			self.__xco=self.__xco-self.__velx
			self.app(grid)
		else:
			self.disapp(grid)
			self.__xco=0
			self.app(grid)

	# def magmoveleft(self,grid,arr,ch,fl):
	# 	self.fl=fl
	# 	self.arr=arr
	# 	self.ch=ch
	# 	if self.xco > self.arr[0][0] and self.ch != 'a' and self.ch != 'd' and self.fl ==0:
	# 		self.disapp(grid)
	# 		self.xco=self.arr[0][0]
	# 		self.app(grid)
			
	# def magmoveright(self,grid,arr,ch,fl) :
	# 	self.fl=fl
	# 	self.arr=arr
	# 	self.ch=ch
	# 	if self.xco <self.arr[0][0] and self.ch != 'a' and self.ch != 'd' and self.fl ==0 :
	# 		self.disapp(grid)
	# 		self.xco=self.arr[0][0]
	# 		self.app(grid)

	def magmoveleft(self,grid,arr,ch,fl):
		self.__fl=fl
		self.__arr=arr
		self.__ch=ch
		if self.__xco > self.__arr[0][0] and self.__ch != 'a' and self.__ch != 'd' and self.__fl ==0:
			self.disapp(grid)
			self.__xco=self.__xco-1
			self.app(grid)
			
	def magmoveright(self,grid,arr,ch,fl) :
		self.__fl=fl
		self.__arr=arr
		self.__ch=ch
		if self.__xco <self.__arr[0][0] and self.__ch != 'a' and self.__ch != 'd' and self.__fl ==0 :
			self.disapp(grid)
			self.__xco=self.__xco+1
			self.app(grid)


		
	def moveup(self,grid):
		if self.__yco-self.__vely >= 1:
			self.disapp(grid)
			self.__yco=self.__yco-self.__vely
			self.app(grid)
		else:
			self.disapp(grid)
			self.__yco=1
			self.app(grid)	

	def coll_check_coin(self,grid,coin_cod,obj2):
		for y in range(0,3):
			for x in range(0,3):
				if [x+self.__xco,y+self.__yco] in coin_cod :
					self.__ob=obj2
					self.__ob.disapp(grid)
					self.__ob.delete(grid)
					self.__score=self.__score+1
					self.__flag3=1
					return self.__flag3

	def coll_check_zap(self,grid,zapp_cod,obj,shi):
		self.__shi=shi
		for y in range(0,3):
			for x in range(0,3):
				if [x+self.__xco,y+self.__yco] in zapp_cod :
					self.__ob=obj
					self.__ob.disapp(grid)
					self.__ob.exterm()
					self.__flag2=1
					if self.__shi != 1:
						self.die()
					return self.__flag2

	def coll_check_boost(self,grid,boost_cod,obj):
		for y in range(0,3):
			for x in range(0,3):
				if [x+self.__xco,y+self.__yco] in boost_cod :
					self.__ob=obj
					self.__ob.disapp(grid)
					self.__ob.exterm()
					self.__flag=1
					return self.__flag

	def coll_check_mag(self,grid,mag_cod,obj):
		for y in range(0,3):
			for x in range(0,3):
				if [x+self.__xco,y+self.__yco] in mag_cod :
					self.__ob=obj
					self.__ob.disapp(grid)
					self.__ob.exterm()

	def shield(self):
		self.__form = [ [Back.GREEN+"*", Back.GREEN+"*", Back.RED+"*"], [Back.GREEN+"<", Back.GREEN+"%", Back.RED+">"], [Back.GREEN+"^", Back.GREEN+":", Back.RED+"^"] ]

	def remake(self):
		self.__form = [ [Back.GREEN+"*", Back.GREEN+"*", Back.GREEN+"*"], [Back.GREEN+"<", Back.GREEN+"%", Back.GREEN+">"], [Back.GREEN+"^", Back.GREEN+":", Back.GREEN+"^"] ]


	def end_check(self):
		if self.__life <= 0:
			
			exit()
	
	def printscore(self):
		print("score = ", self.__score,end=" ") 
		print("life = ", self.__life,end=" ") 

	def gravity(self,grid):
		self.__vd=self.__g*self.__t
		if round(self.__yco+self.__vd) <= 29 :
			self.disapp(grid)
			self.__yco=round(self.__yco+self.__vd)
			self.app(grid)
		else:
			self.disapp(grid)
			self.__yco=29
			self.app(grid)

	
	def die(self):
		if self.__life >0: 
			self.__life=self.__life-1


	def inctime(self):
		self.__t=self.__t+1

	def resetime(self):
		self.__t=1

	def bull(self,grid):
		self.__bu=bullet(self.__xco,self.__yco,grid)
		return self.__bu

	def boo(self,grid):
		self.__booster=boost(grid)
		return self.__booster

	def cod(self):
		self.__co.clear()
		self.__co=[self.__xco,self.__yco]
		return self.__co

	def codlist(self):
		self.__co2.clear()
		for x in range(0,3):
			for y in range(0,3):
				self.__co2.append([self.__xco+x,self.__yco+y])
		return self.__co2

	def boost(self):
		self.__velx=3
		self.__vely=3

	def revspeed(self):
		self.__velx=self.__oldvelx
		self.__vely=self.__oldvely

	def sco(self):
		self.__score=self.__score+10

	


class enemy:
	def __init__(self,life):
		self.__vely=1
		self.__cod=[]
		self.__life=life
		self.__xco=random.randint(70,75)
		self.__yco=random.randint(2,26)
		# self.__form=[ [Back.GREEN+"D", Back.GREEN+"D", Back.GREEN+"D"], [Back.GREEN+"D", Back.GREEN+"D", Back.GREEN+"D"], [Back.GREEN+"D", Back.GREEN+"D", Back.GREEN+"D"] ]
#  		self.__form="""
#   _a' /(     ,>
# ~~_}\\ \\(    (
#      \\(,_(,)' 
#       _>, _>,  
#       """     
		self.__form=[]
		self.__form.append("  _a  /(     ,>")
		self.__form.append("~~_}\\ \\(    (")
		self.__form.append("     \\(,_(,)  ")
		self.__form.append("      _>, _>,  ")

	def app(self,grid):
		for y in range(0,4):
			for x in range(0,len(self.__form[y])):
				grid[y+self.__yco][x+self.__xco]=self.__form[y][x]

	def disapp(self,grid):
		for y in range(0,4):
			for x in range(0,len(self.__form[y])):
				grid[y+self.__yco][x+self.__xco]=Back.CYAN+" "

	def follow(self,ob,grid):
		self.__ob=ob
		if self.__ob.cod()[1]>self.__yco:
			self.movedown(grid)
		else: 
			self.moveup(grid)

	def moveup(self,grid):
		self.__vely=random.randint(1,3)
		if self.__yco-self.__vely > 1:
			self.disapp(grid)
			self.__yco=self.__yco-self.__vely
			self.app(grid)
		else:
			self.disapp(grid)
			self.__yco=2
			self.app(grid)

	def movedown(self,grid):
		self.__vely=random.randint(1,3)
		if self.__yco+self.__vely <= 28:
			self.disapp(grid)
			self.__yco=self.__yco+self.__vely
			self.app(grid)
		else:
			self.disapp(grid)
			self.__yco=28
			self.app(grid)

	def end_check(self,ob):
		self.__ob=ob
		if self.__life <= 0:
			self.exterm()
			self.__ob.sco()
			os.system('clear')
			self.__ob.printscore()
			# print("YOU WIN",end=" ")
			exit()

	def die(self):
		if self.__life >0:
			self.__life=self.__life-1

	def fire(self,grid):
		self.__enbu=enbullet(self.__xco,self.__yco,grid)
		return self.__enbu

	def exterm(self):
		self.__form=[[Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" "],[Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" "],[Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" "],[Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" ",Back.CYAN+" "]]

	def codlist(self):
		self.__cod.clear()
		for y in range(0,4):
			for x in range(0,len(self.__form[y])):
				self.__cod.append([self.__xco+x,self.__yco+y])
		return self.__cod

	def printscore(self):
		print("dragon life =",self.__life,end=" ") 




















		