#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main() {
	char cmd[100], comando[100], *parametros[20];
	char *envp[] = { (char *) "PATH=/bin", 0};
	while (1) {
		type_prompt();
		leer_comando (comando, parametros);
		if (fork() != 0)
			wait (NULL);
		else {
			strcpy (cmd, "/bin/");
			strcat (cmd, comando);
			execve (cmd, parametros, envp);
		}
		if (strcmp (comando, "exit") == 0)
			break;
	}
	return 0;
}

void type_prompt() {
	static int primera_vez = 1;
	if (primera_vez) {
		const char* CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
		write (STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
		primera_vez = 0;
	}

	printf("Terminal>");
}

void leer_comando (char cmd[], char *par[]) {
	char linea[1024];
	int cont = 0, i = 0, j = 0;
	char *arreglo[100], *pch;

	for (;;) {
		int c = fgetc (stdin);
		linea[cont++] = (char) c;
		if (c == '\n') 
			break;
	}
	
	if (cont == 1) 
		return;
	pch = strtok (linea, " \n");

	while (pch != NULL) {
		arreglo[i++] = strdup (pch);
		pch = strtok (NULL, " \n");
	}
	
	strcpy (cmd, arreglo[0]);
	for (int j = 0; j < i; j++)
		par[j] = arreglo[j];
	par[i] = NULL;
}
