#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {
	struct tm birth;
	char birthDate[50];    
	char *ptrStrDate;
	char strDate[3][5];
	
	int i;

	printf("Informe a data de nascimento (dd/mm/aaa): ");
	scanf("%s", birthDate);

	ptrStrDate = strtok(birthDate, "/");

	i = 0;
	while (ptrStrDate != NULL) {
		strcpy(strDate[i], ptrStrDate);
		//printf("%s\n", strDate[i]);
		i++;

		ptrStrDate = strtok(NULL, "/");
	}

	birth.tm_hour = 0;
	birth.tm_min = 0;
	birth.tm_sec = 0;
	
	birth.tm_mday = atoi(strDate[0]);
	birth.tm_mon = atoi(strDate[1]);
	birth.tm_year = 1900 - atoi(strDate[2]);

	//Taking the birth date and converting to time_t.
	//double birthSecs = difftime(time(NULL), mktime(&birth));

	printf("A quantidade de segundos que você já viveu foi: %ld", (time(NULL) - mktime(&birth))); //birthSecs);
	
	printf("\n\n\n\n");

	return 0;
}
