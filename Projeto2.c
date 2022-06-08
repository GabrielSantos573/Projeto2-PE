//Nome: Gabriel Oliveira Santos / Matrícula: UC21100452

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_PRE 45//comecar a validar

int main() {
	setlocale(LC_ALL, "Portuguese");
	FILE *arq;
	char nomePre[MAX_PRE];
	int i = 0, tamanho = 0, espaco = 0;
	
	arq = fopen("Nome_Presidente.txt", "r");
	
	if(fgets(nomePre, MAX_PRE, arq) != NULL)
		printf("%s", nomePre);
	else{
		if(arq == NULL){
  			printf("Erro na abertura do arquivo!");
  			return 1;
		}else{
			printf("Nome do Presidente CBF:");
			scanf("%[^\n]s", &nomePre);
			
			tamanho=strlen(nomePre);
			
			nomePre[0] = toupper(nomePre[0]);
			
			for(i=0; i<tamanho; i++){
				if(nomePre[i]==' '){
					espaco = i; 
					nomePre[espaco+1] = toupper(nomePre[espaco+1]);
				}
			}
			
			fprintf(arq, "%s", nomePre);
			fclose(arq);
 			
		}
	}
	
	return 0;
}
