from board import board
from input1 import Get,input_to
from mando import *
from scen import * 
from zap import beam
import os
import time
it=0
boos_act=0
shi_act=0
bo=board()
vx=2
vy=1
life=11
t_boos=-10
t_shi=-10
playa=mando(10,10,vx,vy,life)
playa.app(bo.matt())
coin=[]
bu=[]
enbu=[]
boost=[]
mag=[]
zapp=[]
zapp_cod=[]
coin_cod=[]
boost_cod=[]
playa_cod=[]
playa_cod.append(playa.codlist())
mag_cod=[]


# for x in range(1,2):
# 	ma=magnet(bo.mat)
# 	mag.append(ma)
# 	mag_cod.append(ma.cood())




stime=time.time()
dragon_start=0
dragon_life=3
dragon_cod=[]



while True:
	print('\033[0;0H')
	get = Get()
	ch = input_to(get)

	ti=110-(time.time()-stime)
	print("time remaining = ", round(ti), end =" ")


	if time.time()-stime >110:
		exit()

	if time.time()-stime > 75:
		if dragon_start == 0:
			dragon=enemy(dragon_life)
			dragon.app(bo.matt())
			dragon_start=1
			dragon_cod.append(dragon.codlist())


	# if time.time()-stime > 10:
	if random.random() >0.95 and time.time()-stime < 65:
		if it%16==0:
			ma=magnet(bo.matt())
			mag.append(ma)
			mag_cod.append(ma.cod())

		co=coins()
		coin.append(co)
		coin_cod.append(co.codlist())
		co.app(bo.matt())
		za=beam()
		zapp.append(za)
		zapp_cod.append(za.codlist())
		za.app(bo.matt())
		if it%16==0:
			boos=playa.boo(bo.matt())
			boost.append(boos)
			boost_cod.append(boos.cood())

	

			

	if shi_act == 1:
		if time.time()-t_shi >= 10:
			shi_act=2
			playa.remake()

	if shi_act == 2:
		if time.time()-t_shi>=60:
			shi_act=0

	if boos_act == 1:
		for x in zapp:
			x.boost()
		for x in coin:
			x.boost()
		for x in bu:
			x.boost()
		for x in boost:
			x.boost()
		for x in mag:
			x.boost()
		playa.boost()
		if time.time()-t_boos > 10:
			boos_act=0
			for x in zapp:
				x.revspeed()
			for x in coin:
				x.revspeed()
			for x in bu:
				x.revspeed()
			for x in boost:
				x.revspeed()
			for x in mag:
				x.revspeed()
			playa.revspeed()



	

	for x in range(1,len(coin)+1):
		if playa.coll_check_coin(bo.matt(),coin_cod[x-1],coin[x-1]) == 1:
			pass

	lzapp=len(zapp)
	for x in range(1,lzapp+1):
		if playa.coll_check_zap(bo.matt(),zapp_cod[x-1],zapp[x-1],shi_act) == 1: 
			zapp_cod.remove(zapp_cod[x-1])
			zapp.remove(zapp[x-1])
			break
	

	lboost=len(boost)
	for x in range(1,lboost+1):
		if playa.coll_check_boost(bo.matt(),boost_cod[x-1],boost[x-1]) ==1:
			# boost[x-1].speed(zapp,coin,bu)
			boos_act=1
			t_boos=time.time()
			boost_cod.remove(boost_cod[x-1])
			boost.remove(boost[x-1])
			break

	


	if dragon_start ==1:
		if it%10==0:
			enbull=dragon.fire(bo.matt())
			enbu.append(enbull)
		for x in range(0,len(enbu)):
			enbu[x].back(bo.matt(),playa_cod[0],playa)
		dragon.follow(playa,bo.matt())
		dragon_cod.append(dragon.codlist())
		dragon.printscore()
		dragon.end_check(playa)	
	# else:
	


	playa.printscore()
	print()
	print()
	playa.end_check()
	bo.printboard()

	if ch == ' ':
		if shi_act==0:
			playa.shield()
			t_shi=time.time()
			shi_act=1

	if ch == '1':
		bull=playa.bull(bo.matt())
		bu.append(bull)

	if ch == 'w':
		playa.moveup(bo.matt())
		playa.resetime()
		
	if ch == 'd':
		playa.moveright(bo.matt())
	if ch == 'a':
		playa.moveleft(bo.matt())
	if ch == 'q':
		exit()
	if ch != 'w':
		playa.inctime()
		playa.gravity(bo.matt())
		

	lbu=len(bu)
	if dragon_start == 0:
		for x in range(0,lbu):
			for y in range(1,len(zapp)+1):
				bu[x].front(bo.matt(),zapp_cod[y-1],zapp[y-1])

	if dragon_start == 1:
		for x in range(0,len(bu)):
			for y in range(1,2):
				bu[x].front2(bo.matt(),dragon_cod[y-1],dragon)


	for x in range(1,len(mag)+1): 
		mag[x-1].attract(bo.matt(),playa,ch)
			# mag_cod.remove(mag_cod[x-1])
			# mag.remove(mag[x-1])
			# break




	
	zapp_cod.clear()
	coin_cod.clear()
	boost_cod.clear()
	mag_cod.clear()
	dragon_cod.clear()
	playa_cod.clear()

	for x in range(1,len(coin)+1):
		coin[x-1].back(bo.matt())
		coin_cod.append(coin[x-1].codlist())
	for x in range(1,len(zapp)+1):
		zapp[x-1].back(bo.matt())
		zapp_cod.append(zapp[x-1].codlist())
	for x in range(1,len(boost)+1):
		boost[x-1].back(bo.matt())
		boost_cod.append(boost[x-1].cood())

	for x in range(1,len(mag)+1):
		mag[x-1].back(bo.matt())
		mag_cod.append(mag[x-1].cod())
	playa_cod.append(playa.codlist())

	
	it=it+1
	







