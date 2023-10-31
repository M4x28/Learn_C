#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#define BUFFERSIZE 512
#define PROTOPORT 57015 // Numero di porta predefinito

#define DATASIZE 410
#define OPERATORSIZE 51
#define OPTIONSIZE 51

typedef struct {
	char data[DATASIZE];
	char operator[OPERATORSIZE];
	char option[OPTIONSIZE];
} msg;

// Dichiarazioni dei prototipi delle funzioni
void errorhandler(char *error_message);
void clearwinsock();
int sendData(int, msg*);
void receiveData(int, int);
void closeConnection(int);
int createSocket(int);
struct sockaddr_in bindSocket(struct sockaddr_in);
int connectToServer(int, struct sockaddr_in);
void checkWindowDevice();
void inputStrings(msg*, int);

int main(int argc, char *argv[]) {
	// 0) Inizializzo libreria WSA nel caso in cui siamo su Windows
	checkWindowDevice();

	// 1) Creazione socket
	int c_socket = -1;
	c_socket = createSocket(c_socket);

	// 2) Binding
	struct sockaddr_in sad;
	sad = bindSocket(sad);

	// 3) Connessione al server
	connectToServer(c_socket, sad);

	// 4) Invio dei dati
	msg m;
	int n;
	printf("Inserisci il numero di dati da inviare: ");
	scanf("%d", &n);
	inputStrings(&m, n);
	sendData(c_socket, &m);

	// 5) Ricevere dati dal server
	receiveData(c_socket, sizeof(m));

	// 6) Chiusura della connessione
	closeConnection(c_socket);

	return 0;
}

void errorhandler(char *error_message) {
	printf("%s", error_message);
}

void clearwinsock() {
#if defined WIN32
	WSACleanup();
#endif
}

int sendData(int c_socket, msg *m) {
	// Inviare dati al server
	if (send(c_socket, m, sizeof(msg), 0) != sizeof(msg)) {
		errorhandler(
				"send() ha inviato un numero diverso di byte da quanto previsto.");
		closesocket(c_socket);
		clearwinsock();
		return -1;
	}
	return 1;
}

void receiveData(int c_socket, int string_len) {
	int bytes_rcvd;
	int total_bytes_rcvd = 0;
	char buf[BUFFERSIZE];   // Buffer per i dati dal server
	memset(buf, 0, BUFFERSIZE); // Assicura che i byte extra siano impostati a 0
	printf("Ricevuto: "); // Impostazione per stampare la stringa ricevuta

	while (total_bytes_rcvd < string_len) {
		if ((bytes_rcvd = recv(c_socket, buf, BUFFERSIZE - 1, 0)) <= 0) {
			errorhandler(
					"recv() ha fallito o la connessione si è chiusa prematuramente.");
			closesocket(c_socket);
			clearwinsock();
			return;
		}
		total_bytes_rcvd += bytes_rcvd; // Tieni traccia del totale dei byte ricevuti
	}
	buf[bytes_rcvd] = '\0'; // Ridondante, ma imposta il terminatore nullo

	char dataCopy[DATASIZE + 1]; // Copia del campo data
	strncpy(dataCopy, buf, DATASIZE);
	dataCopy[DATASIZE] = '\0'; // Assicura che sia null-terminated

	char *token = strtok(dataCopy, "()");
	while (token != NULL) {
		printf("Sottostringa: %s\n", token);
		token = strtok(NULL, "()");
	}
}

void closeConnection(int c_socket) {
	closesocket(c_socket);
	clearwinsock();
	printf("\n");    // Stampa un avanzamento di riga finale
	system("pause");
	getchar();
}

int createSocket(int c_socket) {
	c_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c_socket < 0) {
		errorhandler("Creazione della socket fallita.\n");
		closesocket(c_socket);
		clearwinsock();
		return -1;
	} else {
		printf("Creazione socket avvenuta con successo!\n");
	}
	return c_socket;
}

struct sockaddr_in bindSocket(struct sockaddr_in sad) {
	memset(&sad, 0, sizeof(sad));
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP del server
	sad.sin_port = htons(PROTOPORT); // Porta del server

	return sad;
}

int connectToServer(int c_socket, struct sockaddr_in sad) {
	if (connect(c_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {
		errorhandler("Connessione fallita.\n");
		closesocket(c_socket);
		clearwinsock();
		return -1;
	} else {
		printf("Connesso\n");
		return 1;
	}
}

void checkWindowDevice() {
#if defined WIN32
	WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != 0) {
		printf("Errore durante WSAStartup\n");
		return;
	}
#endif
}

void inputStrings(msg *m, int n) {
	// Inizializza tutti i campi a zero
	memset(m->data, 0, DATASIZE);
	memset(m->operator, 0, OPERATORSIZE);
	memset(m->option, 0, OPTIONSIZE);

	for (int i = 0; i < n; i++) {
		char input[DATASIZE];
		printf("Stringa %d: ", i + 1);
		scanf("%s", input);

		// Controlla se il buffer di data è pieno
		if (strlen(m->data) + strlen(input) + 1 >= DATASIZE) {
			printf(
					"Il buffer data è pieno. Non è possibile inserire altre stringhe.\n");
			break;
		}

		// Aggiungi la stringa al campo data con il carattere di escape
		strcat(m->data, input);
		strcat(m->data, "()"); // Usiamo il carattere di escape
	}

	// Richiedi all'utente di inserire il campo operator se è necessario
	printf("Inserisci il campo operator (massimo %d caratteri, opzionale): ",
	OPERATORSIZE - 1);
	scanf("%s", m->operator);

	// Controllo sulla massima lunghezza del campo operator
	if (strlen(m->operator) > OPERATORSIZE - 1) {
		printf(
				"Il campo operator è troppo lungo. Limite di %d caratteri. Verrà azzerato.\n",
				OPERATORSIZE - 1);
		memset(m->operator, 0, OPERATORSIZE); // Azzeramento del campo
	}

	// Richiedi all'utente di inserire il campo option se è necessario
	printf("Inserisci il campo option (massimo %d caratteri, opzionale): ",
	OPTIONSIZE - 1);
	scanf("%s", m->option);

	// Controllo sulla massima lunghezza del campo option
	if (strlen(m->option) > OPTIONSIZE - 1) {
		printf(
				"Il campo option è troppo lungo. Limite di %d caratteri. Verrà azzerato.\n",
				OPTIONSIZE - 1);
		memset(m->option, 0, OPTIONSIZE); // Azzeramento del campo
	}
}
