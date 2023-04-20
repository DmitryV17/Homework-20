#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

using namespace std;

#define MESSAGE_LENGTH 1024 // ������������ ������ ������ ��� ������
#define PORT 7777 // ����� ������������ ���� ����� �����

struct sockaddr_in serveraddress, client;
socklen_t length;
int sockert_file_descriptor, connection, bind_status, connection_status;
char message[MESSAGE_LENGTH];

int main() {
    // �������� �����
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor == -1) {
        cout << "Socket creation failed.!" << endl;
        exit(1);
    }
    // 
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // ������� ����� ����� ��� �����
    serveraddress.sin_port = htons(PORT);
    // ���������� IPv4
    serveraddress.sin_family = AF_INET;
    // �������� �����
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
        sizeof(serveraddress));
    if (bind_status == -1) {
        cout << "Socket binding failed.!" << endl;
        exit(1);
    }
    // �������� ������ �� ����� ������ 
    connection_status = listen(sockert_file_descriptor, 5);
    if (connection_status == -1) {
        cout << "Socket is unable to listen for new connections.!" << endl;
        exit(1);
    }
    else {
        cout << "Welcome to console chat server: " << endl;
        cout << "======================================= " << endl;
        cout << "Server is listening for new connection: " << endl;
    }
    length = sizeof(client);
    connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);
    if (connection == -1) {
        cout << "Server is unable to accept the data from client.!" << endl;
        exit(1);
    }

    // Communication Establishment
    while (1) {
        bzero(message, MESSAGE_LENGTH);
        read(connection, message, sizeof(message));
        if (strncmp("end", message, 3) == 0) {
            cout << "Client Exited." << endl;
            cout << "Server is Exiting..!" << endl;
            break;
        }
        cout << "Data received from client: " << message << endl;
        bzero(message, MESSAGE_LENGTH);
        cout << "Enter the message you want to send to the client: " << endl;
        cin >> message;
        ssize_t bytes = write(connection, message, sizeof(message));
        // ���� �������� >= 0  ����, ������ ��������� ������ �������
        if (bytes >= 0) {
            cout << "Data successfully sent to the client.!" << endl;
        }
    }
    // ��������� �����, ��������� ����������
    close(sockert_file_descriptor);
    return 0;
}
