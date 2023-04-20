#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

#define MESSAGE_LENGTH 1024 // ������������ ������ ������ ��� ������
#define PORT 7777 // ����� ������������ ���� ����� �����

int socket_file_descriptor, connection;
struct sockaddr_in serveraddress, client;
char message[MESSAGE_LENGTH];
int main() {
    // �������� �����
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        cout << "Creation of Socket failed!" << endl;
        exit(1);
    }

    // ��������� ����� �������
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // ������� ����� �����
    serveraddress.sin_port = htons(PORT);
    // ���������� IPv4
    serveraddress.sin_family = AF_INET;
    // ��������� ���������� � ��������
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        cout << "Connection with the server failed.!" << endl;
        exit(1);
    }
    // �������������� � ��������
    while (1) {
        bzero(message, sizeof(message));
        cout << "Welcome to Console Chat Cloent: " << endl;
        cout << "================================================= " << endl;
        cout << "Enter the message you want to send to the server: " << endl;
        cin >> message;
        if ((strncmp(message, "end", 3)) == 0) {
            write(socket_file_descriptor, message, sizeof(message));
            cout << "Client Exit." << endl;
            break;
        }
        ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
        // ���� �������� >= 0  ����, ������ ��������� ������ �������
        if (bytes >= 0) {
            cout << "Data send to the server successfully.!" << endl;
        }
        bzero(message, sizeof(message));
        // ���� ������ �� �������
        read(socket_file_descriptor, message, sizeof(message));
        cout << "Data received from server: " << message << endl;
    }
    // ��������� �����, ��������� ����������
    close(socket_file_descriptor);
    return 0;
}