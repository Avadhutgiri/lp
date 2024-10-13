import socket
import threading

# Define the IP address and port on which the server will listen
HOST = '127.0.0.1'  # localhost
PORT = 65432        # non-privileged port (>1023)

# Function to handle client connections
def handle_client(conn, addr):
    print(f"Connected by {addr}")
    with conn:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            print(f"Received from {addr}: {data.decode()}")
            conn.sendall(data)  # Echo the data back to the client
    print(f"Connection closed with {addr}")

def start_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))  # Bind the socket to the address
        s.listen()  # Listen for incoming connections
        print(f"Server started at {HOST}:{PORT}, waiting for clients...")
        
        while True:
            conn, addr = s.accept()  # Accept the connection
            thread = threading.Thread(target=handle_client, args=(conn, addr))  # Create new thread for each client
            thread.start()

if _name_ == "_main_":
    start_server()