import socket

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 65432        # The port used by the server

def start_client():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))  # Connect to the server
        print("Connected to the server. Type your message:")
        
        while True:
            message = input("You: ")
            if message.lower() == 'exit':
                print("Disconnecting...")
                break
            s.sendall(message.encode())  # Send the message
            data = s.recv(1024)  # Receive echoed data from the server
            print(f"Server echoed: {data.decode()}")

if _name_ == "_main_":
    start_client()