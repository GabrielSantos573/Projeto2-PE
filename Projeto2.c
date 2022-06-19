//Nome: Gabriel Oliveira Santos / Matrícula: UC21100452


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_PRE 45
#define MAX_JOGOS 450
#define TAM_CIDADE 120

typedef struct{
		int id;
		float valor;
		char cidade[TAM_CIDADE];
	}Jogo;

void le_valida_pre(char  ptrPre[], int tam);
void le_valida_id(Jogo jogo[], int index);
void le_valida_valor(Jogo jogo[],int index);
void le_valida_cidade(Jogo jogo[], int index);
void apresenta_jogos(Jogo jogo[], int index, char pre[]);
void consulta_jogos(Jogo jogo[], int index);
void ordena_jogos(Jogo jogo[], int index);

int main() {
	setlocale(LC_ALL, "Portuguese");
	FILE *arq;
	char nomePre[MAX_PRE], opcao;
	int i = 0, a = 0,tamanho = 0, espaco = 0, cont = 0;
	
	Jogo jogo[MAX_JOGOS];
	
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
			fflush(stdin);
			
			tamanho=strlen(nomePre);
			
			le_valida_pre(nomePre,tamanho);
				
			for(i=0; i<tamanho; i++){
				nomePre[i] = tolower(nomePre[i]);
			}
			
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
	do{
		
		getch("");
		system("cls");
		
		printf("\nPara cadastrar jogos(a)");
		printf("\nApresentação dos jogos cadastrados(b)");
		printf("\nConsulta dos jogos cadastrados em uma cidade(c)");
		printf("\nSair(d)\n");
		scanf("%c", &opcao);
		
		switch(opcao){
			case 'a':
				le_valida_id(&jogo, cont);
				
				le_valida_valor(&jogo, cont);
				
				le_valida_cidade(&jogo, cont);
				
				cont++;
			break;
			
			case 'b':
				ordena_jogos(&jogo, cont);
				apresenta_jogos(&jogo, cont, nomePre);
			break;
			
			case 'c':
				consulta_jogos(&jogo, cont);
			break;
			
			case 'd':
				
			break;
		}
	}while(opcao!='d' );
	
	return 0;
}

	void le_valida_pre(char ptrPre[], int  tam){// 'char ptrPre[]' é a mesma coisa que 'char * ptrPre', continua sendo por referência
		
		while(tam<4 || tam > MAX_PRE){
			printf("O nome não pode ser vazio e nem maior que 45:");
			scanf("%[^\n]s", &(*ptrPre));
			
			tam=strlen(ptrPre); 
			fflush(stdin);
		}
	}
	
	void le_valida_id(Jogo jogo[], int index){ 
		int unId=0;
		do{
			printf("\nIndentificação do jogo(300-10.000):");
			scanf("%d", &jogo[index].id);
			
			for(unId; unId<index; unId++){
				if(jogo[index].id == jogo[unId].id){
					printf("O número não deve ser repetido!");
					printf("\nIndentificação do jogo(300-10.000):");
					scanf("%d", &jogo[index].id);
					//break;
				}
			}
			
		}while(jogo[index].id<300 || jogo[index].id>10000);
	}
	
	void le_valida_valor(Jogo jogo[], int index){ 
		
		do{
			printf("\nValor Arrecadado(1.000 - 1.000.000):");
			scanf("%f", &jogo[index].valor);
		}while(jogo[index].valor<1000 || jogo[index].valor>1000000);
		
	}
	
	void le_valida_cidade(Jogo jogo[], int index){ 
		int size, j = 0, espaco;
		do{
			fflush(stdin);
			
			printf("\nCidade:");
			scanf("%[^\n]s", &jogo[index].cidade);
			size = strlen(jogo[index].cidade);
			
			fflush(stdin);
			
			for(j; j<size;j++){
				jogo[index].cidade[j] = tolower(jogo[index].cidade[j]);
			}
			
			jogo[index].cidade[0] = toupper(jogo[index].cidade[0]);
			for(j=0; j<size; j++){
					if(jogo[index].cidade[j]==' '){
						espaco = j; 
						jogo[index].cidade[espaco+1] = toupper(jogo[index].cidade[espaco+1]);
					}
				}
		}while(size<1 || size>TAM_CIDADE);
		
	}
void ordena_jogos(Jogo jogo[], int index){
	char auxCidade[80];
	int f = 0, p = 0;
	int auxId, auxValor;
	
	for(f; f<index; f++){
		for(p=f+1; p < index; p++){
			if(strcmp(jogo[f].cidade,jogo[p].cidade) > 0){
				strcpy(auxCidade, jogo[f].cidade);
				strcpy(jogo[f].cidade, jogo[p].cidade);
				strcpy(jogo[p].cidade, auxCidade);
				
				auxId = jogo[f].id;
				jogo[f].id = jogo[p].id;
				jogo[p].id = auxId;
				
				auxValor = jogo[f].valor;
				jogo[f].valor = jogo[p].valor;
				jogo[p].valor = auxValor;
			}
		}
	}
	}
	
void apresenta_jogos(Jogo jogo[], int index, char pre[]){
	int a=0;
	if(index > 0){
		printf("\t%s\n\n", pre);
		printf("Cidade. - Identificador. - Valor Arrecadado.");
		for(a; a < index; a++){	
			printf("\n%s - %d - R$%.2f", jogo[a].cidade, jogo[a].id, jogo[a].valor);
		}
	
	}else printf("Cadastre ao menos um jogo!");
}

void consulta_jogos(Jogo jogo[], int index){
	fflush(stdin);
	char Cidade[TAM_CIDADE];
	int espaco, tamanho = 0, i = 0, g = 0;
	int else_do_if = 0;
	
	if(index > 0){
		printf("Cidade a ser consultada:");
		scanf("%[^\n]s", &Cidade);
		fflush(stdin);
		
		tamanho = strlen(Cidade);
		
		for(i=0; i<tamanho; i++){
				Cidade[i] = tolower(Cidade[i]);
			}
			
		Cidade[0] = toupper(Cidade[0]);
		for(i=0; i<tamanho; i++){
			if(Cidade[i]==' '){
				espaco = i; 
				Cidade[espaco+1] = toupper(Cidade[espaco+1]);
			}
		}
		
		for(g; g < index; g++){
			if(strcmp(jogo[g].cidade, Cidade)==0){
				printf("\nCidade:%s - Identificador:%d - Valor Arrecadado:R$%.2f", jogo[g].cidade, jogo[g].id, jogo[g].valor);
				else_do_if = 24; //numero aleatório pq o else do if(linha 234) tem que estar fora do for. 
			}
		}
		
		if(else_do_if != 24){
			printf("\nNão encontrado\n. Dica: tente sem assento!");
		}
		
	}else printf("\nNão há jogos cadastrados. Cadastre um jogo primeiro!");
	
}
