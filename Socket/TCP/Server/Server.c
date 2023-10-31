#if defined WIN32
#include <winsock.h>
#else
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#define closesocket close
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PROTOPORT 57015
#define BUFFERSIZE 512
#define CODA 6

void errorhandler(char *messaggioErrore) {
	printf("%s", messaggioErrore);
}

void convertiInMaiuscolo(char *str) {
	while (*str != '\0') {
		*str = toupper(*str);
		str++;
	}
}

void convertiInMinuscolo(char *str) {
	while (*str != '\0') {
		*str = tolower(*str);
		str++;
	}
}

#define NO_ERROR 0

void clearwinsock() {
#if defined WIN32
	WSACleanup();
#endif
}

#define DATASIZE 410
#define OPERATORSIZE 51
#define OPTIONSIZE 51

typedef struct {
	char data[DATASIZE];
	char operator[OPERATORSIZE];
	char option[OPTIONSIZE];
} msg;

void checkWindowDevice();
int createSocket(int my_socket);
void processData(msg *m);
struct sockaddr_in bindSocket(int my_socket, struct sockaddr_in);
void setSocketOnListen(int my_socket);

int main(int argc, char *argv[]) {
	// 0) Inizializzo libreria WSA nel caso in cui siamo su Windows
	checkWindowDevice();

	// 1) Creazione socket
	int my_socket = -1;
	my_socket = createSocket(my_socket);

	// 2) Binding
	struct sockaddr_in sad;
	sad = bindSocket(my_socket, sad);

	// 3) Impostiamo la socket in modalità ascolto
	setSocketOnListen(my_socket);

	struct sockaddr_in cad;    //struttura per l'indirizzo del client
	int client_socket;     //descrittore della socket per il client
	int client_len;     //dimensione dell'indirizzo del client

	char *input_string = "Connessione Avvenuta!"; //stringa da inviare
	int lunghezza_stringa = strlen(input_string); //calcola la lunghezza

	while (1) {
		printf("\nRicerca del client...");
		client_len = sizeof(cad); //impostiamo la dimensione del client

		// 4) Accetta connessione
		if ((client_socket = accept(my_socket, (struct sockaddr*) &cad,
				&client_len)) < 0) {
			errorhandler("accept() non riuscita.\n");

			closesocket(client_socket);
			clearwinsock();
			return 0;
		}

		// 5) Il server invia una stringa di connessione
		send(client_socket, input_string, lunghezza_stringa, 0);
		printf("\nGestione del client %s\n", inet_ntoa(cad.sin_addr));

		// 6) Ricevere dati dal Client
		msg m;
		if ((recv(client_socket, &m, sizeof(msg), 0)) <= 0) {
			errorhandler("recv() failed or connection closed prematurely");
			closesocket(my_socket);
			clearwinsock();
		}

		// Stampa dati inviati dal client
		char dataCopy[DATASIZE + 1]; // Copia del campo data
		strncpy(dataCopy, m.data, DATASIZE);
		dataCopy[DATASIZE] = '\0'; // Assicura che sia null-terminated

		char *token = strtok(dataCopy, "()");
		while (token != NULL) {
			printf("Sottostringa: %s\n", token);
			token = strtok(NULL, "()");
		}

		// 7) Processa dati sencondo la logica definita nella funzione
		processData(&m);

		// 8) Invia dati processati al client
		if (send(client_socket, &m, sizeof(msg), 0) != sizeof(msg)) {
			errorhandler(
					"send() sent a different number of bytes than expected");
			closesocket(my_socket);
			clearwinsock();
		}

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

int createSocket(int my_socket) {
	my_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (my_socket < 0) {
		errorhandler("Creazione della socket fallita.\n");
		closesocket(my_socket);
		clearwinsock();
		return -1;
	} else {
		printf("Creazione socket avvenuta con successo!\n");
	}
	return my_socket;
}

struct sockaddr_in bindSocket(int my_socket, struct sockaddr_in sad) {
	//assegnamento di un indirizzo alla socket appena creata
	memset(&sad, 0, sizeof(sad));
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	sad.sin_port = htons(PROTOPORT);

	if (bind(my_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) { //si associa l’indirizzo alla socket
		errorhandler("bind() non riuscita.\n");
		closesocket(my_socket);
		clearwinsock();
	}

	return sad;
}

void setSocketOnListen(int my_socket) {
	if (listen(my_socket, CODA < 0)) {
		errorhandler("listen() non riuscita. \n");
		closesocket(my_socket);
		clearwinsock();
		return;
	}
}

void processData(msg *m) {
	char dataCopy[DATASIZE + 1]; // Copia del campo data
	strncpy(dataCopy, m->data, DATASIZE);
	dataCopy[DATASIZE] = '\0'; // Assicura che sia null-terminated

	// Trova la prima stringa all'interno di DATASIZE
	char *firstString = strtok(dataCopy, "()");

	// Trova la seconda stringa all'interno di DATASIZE
	char *secondString = strtok(NULL, "()");

	// Converte la prima stringa in maiuscolo
	for (int i = 0; firstString[i]; i++) {
		firstString[i] = toupper(firstString[i]);
	}

	// Converte la seconda stringa in minuscolo
	for (int i = 0; secondString[i]; i++) {
		secondString[i] = tolower(secondString[i]);
	}

	// Copia le stringhe convertite nelle rispettive posizioni in data
	memset(m->data, 0, DATASIZE);
	snprintf(m->data, DATASIZE, "%s()%s()", firstString, secondString);
}
