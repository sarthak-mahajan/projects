import socket

gdict={ }
gid=0


class graph():
    def __init__(self,v):
        self.v=v
        self.g=[]
        for i in range(v):
            self.g.append([])
        for i in range(v):
            for j in range(v):
                self.g[i].append(0)
        self.cost=0
        self.cnt=0
        self.mark=[]
        for i in range(self.v):
            self.mark.append(0)
        self.edges=0
        self.min=10001
        self.x=0
        self.flag=0




    def add_edge(self,u,v,e):
        if u!=v:
            self.g[u][v]=e
            self.g[v][u]=e

    def mst(self):
        self.cnt=0
        for i in range(self.v):
            self.mark[i]=0
        self.cost=0
        self.edges=0
        self.x=0

        for i in range(self.v):
            if self.cnt == self.v:
                break
            self.cnt=0
            for j in range(self.v):
                if self.g[i][j]==0:
                    self.cnt=self.cnt+1
        
        if self.v==1 or self.v==0:
            self.cost=0

        elif self.cnt==self.v:
            self.cost=-1

        else:
            
            self.mark[0]=1

            while self.edges < self.v-1:
                self.min=10001
                self.flag=0
                for i in range(self.v):
                    if self.mark[i]==1:
                        for j in range(self.v):
                            if self.mark[j]==0 and self.g[i][j]!=0:
                                self.flag=1
                                if self.min > self.g[i][j]:
                                    self.min=self.g[i][j]
                                    self.x=j

                if self.flag ==0:
                    self.cost=-1
                    break
                

                self.cost=self.cost+self.min
                self.edges=self.edges+1

                self.mark[self.x]=1



def operate(val):
    val=val.split( )

    if val[0]=="add_graph":
        n=int(val[2])
        ob=graph(n)
        gid=int(val[1][5])
        gdict.update({gid:ob})



    elif val[0]=="add_edge":
        gid=int(val[1][5])
        u=int(val[2])-1
        v=int(val[3])-1
        e=int(val[4])
        gdict[gid].add_edge(u,v,e)

    elif val[0]=="get_mst":
        gid=int(val[1][5])
        gdict[gid].mst()
        return gdict[gid].cost

    




def server_prog():
    host = socket.gethostname()
    port = 4025

    server_socket = socket.socket()  
    server_socket.bind((host, port))  

    server_socket.listen()
    conn, address = server_socket.accept()  
    

    while True:

        # for i in gdict:
        #     print(i,gdict.get(i).g) 


        data = conn.recv(2048).decode()
        data=str(data)
        # print("len data= ",len(data))
        # print("data=",data)

        
        ans=operate(data)
        dat=data.split( )
        # print(dat[0])
        if dat[0]=="get_mst":
            ans=str(ans)
            # print("ans= ",ans)
            conn.send(ans.encode())
        else:
            ans="blank"
            conn.send(ans.encode())




if __name__ == '__main__':
    server_prog()