1. write dependencies
2. warnings/errors to ignore




The code is written in python: there are 2 files server.py and client.py.

1. Dependencies: install python 3 using: sudo apt install python3
2. How to execute code: 
	open terminal and type: python3 server.py 
	to start the server
	
	open another terminal and type: python3 client.py
	to run the client. You can start giving instructions continiously to the client and it keeps returning the appropriate responses from the server. If you exit from the client using Cntrl+C, the server also stops execution.
	
	You can also pass an input file 'in' to the client using: python3 client.py < in
	This gives the output directly and stops execution of both the client and server on reaching EOF. Ignore the messages given by the server in such cases.

3. Warnings to ignore: 
		Ignore the messages given by the server when the client inputs a redirected file or when the client is halted using inputs like Cntl+C or Cntrl + D

4. Code flow:
	In server.py,In server.prog(), We set the ip address and port of the server, we 'listen' for a client, and accept a client when it appears
	In a while loop, we recieve data from the client, apply the operate() function on recieved data to receive the answer which is passed to the client. In case of add_graph or add_edge where there is no data to be sent, we send a "blank" to
	the client. 
	In the client.py, We set same ip address and port as server.py and then connect to that server with specified address and port. In a while loop we take input from the user, pass it to the server and receive the server's response, we print the response if it isn't "blank". We have a try and except in case of End of line. This is for the case of redirected input files, so that in their case the client stops on reaching EOF. 
	In server.py, graph class helps define each graph, it has 3 methods, the __init__(self,v) method initializes the graph and the quantites related to it like the adjacency matrix etcetra. It needs the number of vertices as an input to create a graph of speified number of vertices and no edge. self.v = number of verices in graph, self.g=adjacency matrix of graph with 0 based indexing(vertix 1 of input is represented as 0 and so on)
	The add_edge(self,u,v,e) method addes edge to the graph by editing the adjacency matrix self.g of the graph class only when there are no self loops(u!=v). It also edits the earlier edgeweight between the specified vertices if it already exists.
	The mst(self) method constructs the MST and finds the cost of this MST. It uses the Prim's Algorithm to achieve this.
	Self.mark[i], denotes whether vertice i has been selected as part of the spanning tree as of yet or not, if self.mark[i]=1, verice i is already in the selected set. self.edges keeps a count of edges selected by the algorithm as part of the MST, the algorithm runs till self.v -1 edges are selected if MST is possible. self.cost is the cost of the MST of the graph, its -1 if MST doesn't exist. self.cnt counts whether any row of the adjaceny matrix is entirely 0's, if so MST doesn't exist and it outputs -1, there's also a condition to check for 1 or 0 vertices to return 0. The Prim's algo runs while no. of eges(self.edges) is not equal to self.v -1, as MST has that many edges, in the while loop, we have 2 nested for loops, the fist loop selects a vertice in the selected cut and the second loop selects a vertice in the unselected cut if it has an edge with the selected vertice, the self.flag is set to 1(its set to 0 at the start of each while loop) if such a combination exists(selected cut verice and unselected cut vertice have an edge between them). We use self.min as a comparison variable whose value is added to the self.cost(cost of MST) in each iteration of the while loop if a edge is added to the MST and self.cost, self.edges is updated. self.x denotes the unselected vertice which has been selected in this iteration and hence we mark this vertice as self.mark[self.x]=1. self.flag basically checks whether an edge can possibly be added to the MST, that is if there is any edge between the set of selected and unselected vertices. If self.flag=0 at the end of nested for loops, it , means no new edge was selected, hence no MST exists thus it breaks the while loop and output -1, otherwise the while loop kees going.
	The operate(val) function checks which operation is to be performed, add_edge, add_graph or get_mst. In case of add_graph, a graph object is iniatialized and added to the divtionary of graphs gdict, In case of add_edge we call the graph.add_edge(self,u,v,e) method and for get_mst we call the graph.mst() method and output graph.cost, the cost of the MST.

	



