import socket


def client_prog():
    host = socket.gethostname() 
    port = 4025

    client_socket = socket.socket() 
    client_socket.connect((host, port)) 

    while True:
        try:
            message = input()
        except EOFError as e:
            return
        client_socket.send(message.encode())  
        data = client_socket.recv(2048).decode() 
        if data!="blank": 
            print(data) 



if __name__ == '__main__':
    client_prog()