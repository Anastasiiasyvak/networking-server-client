import socket
import time

def main():
    host = '10.120.55.208'
    port = 15000

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect((host, port))

        client_socket.sendall(b'Hello')

        wait_response = client_socket.recv(1024)
        print("Received from server:", wait_response.decode())

        ready_response = client_socket.recv(1024)
        print("Received from server:", ready_response.decode())

        message = input("Enter your message: ")
        client_socket.sendall(message.encode())

        ok_response = client_socket.recv(1024)
        print("Received from server:", ok_response.decode())


if __name__ == "__main__":
    main()

