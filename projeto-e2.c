#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//Criação da estrutura de um tipo Quesito
typedef struct sQuesito{
	char nomeQuesito[31];
	float notas[5];
	float notaFinalQuesito;
}Quesito;

//Criação da estrutura de um tipo Escola
typedef struct sEscola{
	char nomeEscola[31];
	char nomeResp[31];
	Quesito quesitos[13];
	float notasFinaisQuesitos[13];
	float notaFinalEscola;
}Escola;

//Função: Menu de Opções
void MenuOpcoes(){
	printf("\n\n\t\t\t\t\tMENU DE OPÇÕES\n");
	printf("\n1. Sair do programa.\t\t\t\t\t6. Mostrar a escola campeã e a vice-campeã.");
	printf("\n2. Cadastrar uma escola.\t\t\t\t7. Mostrar as duas escolas rebaixadas.");
	printf("\n3. Buscar por uma escola.\t\t\t\t8. Gravar o cadastro das escolas em um arquivo.");
	printf("\n4. Calcular a nota final das escolas\t\t\t9. Carregar o cadastros das escolas de um arquivo.");
	printf("\n5. Mostrar todas as escolas cadastradas.");
	return;
}

//Função: Contagem de caracteres no nome da escola
void contaCaracteres(char *str){
	int i,cont=0;
	for(i=0;str[i]!='\0';i++){
		cont++;
	}
	if(cont>=8){
		return;
	}
	else{
		printf("\n\tInsira um nome válido: ");
		gets(str);
		contaCaracteres(str);
		return;
	}
}

//Função: Calcular a nota final das escolas
float calcularNotaFinal(float *vet, int pos){
	if(pos==13){
		return 0;
	}
	else{
		return(vet[pos]+calcularNotaFinal(vet, pos+1));
	}
}

int main(){
	int opcao, nEscolas, primeiroCadastro=1, escCadastradas=0, e=0, q, n, i, contBusca, iBusca, contCompara, encontrado, erroFechamento, iCamp, iVice, iReb1, iReb2;
	int fst, c;
	float maiorNota, menorNota, somaGeralQuesito, somaGeral=0, notaCamp, notaVice, notaReb1, notaReb2;
	char confirmasaida='N', busca[31], placeHolder[31], placeHolderChar;
	FILE* arquivo;
	Escola *ptr;
	printf("\n\t\t\t\t\t  BEM-VINDO!\n");
	printf("\n\tVocê está usando o programa de gerenciamento de escolas de samba do Rio Paranaíba!\n");
	MenuOpcoes();
	printf("\n\nPara começar, insira o número de alguma das opções acima: ");
	scanf("%d", &opcao);
	while((confirmasaida!='s')||(confirmasaida!='S')){
		switch(opcao){
			
			//Funcionalidade: Sair do programa
			case 1:
				printf("\n\t\t\t\t\t    SAIR");
				printf("\n\n\tTem certeza que deseja sair? (S/N): ");
				fflush(stdin);
				scanf("%c", &confirmasaida);
				if((confirmasaida=='s')||(confirmasaida=='S')){
					printf("\n\t\t\t\t\t  OBRIGADO!\n\t\t\t\t\tVOLTE SEMPRE!");
					free(ptr);
					exit(1);
				}
				else{
					MenuOpcoes();
					printf("\n\n\tInsira uma opção do menu: ");
					scanf("%d", &opcao);
				}
				break;
			
			//Funcionalidade: Cadastrar uma escola
			case 2:
				printf("\n\n\t\t\t\t\tCADASTRAR UMA ESCOLA");
				if(primeiroCadastro==1){
					printf("\n\nInforme quantas escolas serão cadastradas no total: ");
					scanf("%d", &nEscolas);
					ptr=(Escola*)malloc(nEscolas*sizeof(Escola));
					if(ptr==NULL){
						printf("\n\n\tFalha ao alocar na memória!");
						exit(1);
					}
					for(i=0;i<nEscolas;i++){
						strcpy(ptr[i].quesitos[0].nomeQuesito, "Bateria");
						strcpy(ptr[i].quesitos[1].nomeQuesito, "Samba-Enredo");
						strcpy(ptr[i].quesitos[2].nomeQuesito, "Harmonia");
						strcpy(ptr[i].quesitos[3].nomeQuesito, "Evolução");
						strcpy(ptr[i].quesitos[4].nomeQuesito, "Enredo");
						strcpy(ptr[i].quesitos[5].nomeQuesito, "Conjunto");
						strcpy(ptr[i].quesitos[6].nomeQuesito, "Alegorias e Adereços");
						strcpy(ptr[i].quesitos[7].nomeQuesito, "Fantasias");
						strcpy(ptr[i].quesitos[8].nomeQuesito, "Comissão de Frente");
						strcpy(ptr[i].quesitos[9].nomeQuesito, "Mestre-Sala e Porta-Bandeira");
						strcpy(ptr[i].quesitos[10].nomeQuesito, "Introdução");
						strcpy(ptr[i].quesitos[11].nomeQuesito, "Performance");
						strcpy(ptr[i].quesitos[12].nomeQuesito, "Finalização");
					}
					primeiroCadastro=0;
				}
				while(e<nEscolas){
					printf("\nNome da escola: ");
					fflush(stdin);
					gets(ptr[e].nomeEscola);
					contaCaracteres(ptr[e].nomeEscola);
					printf("\nNome do responsável: ");
					gets(ptr[e].nomeResp);
					for(q=0;q<13;q++){
						printf("\nQuesito avaliado: %s\n\n", ptr[e].quesitos[q].nomeQuesito);
						for(n=0;n<5;n++){
							printf("\tInsira a nota do jurado %d: ", n+1);
							scanf("%f", &ptr[e].quesitos[q].notas[n]);
							if((ptr[e].quesitos[q].notas[n]<7.0)||(ptr[e].quesitos[q].notas[n]>10.0)){
								while((ptr[e].quesitos[q].notas[n]<7.0)||(ptr[e].quesitos[q].notas[n]>10.0)){
									printf("\n\t\tInsira um valor válido: ");
									scanf("%f", &ptr[e].quesitos[q].notas[n]);
								}
							}
						}
					}
					printf("\nA escola %s foi cadastrada com sucesso!", ptr[e].nomeEscola);
					for(q=0;q<13;q++){
						somaGeralQuesito=0;
						for(n=0;n<5;n++){
							if(n==0){
								maiorNota=ptr[e].quesitos[q].notas[n];
								menorNota=ptr[e].quesitos[q].notas[n];
							}
							else{
								if(ptr[e].quesitos[q].notas[n]>=maiorNota){
									maiorNota=ptr[e].quesitos[q].notas[n];
								}
								if(ptr[e].quesitos[q].notas[n]<=menorNota){
									menorNota=ptr[e].quesitos[q].notas[n];
								}
							}
							somaGeralQuesito=somaGeralQuesito+ptr[e].quesitos[q].notas[n];
						}
						ptr[e].quesitos[q].notaFinalQuesito=somaGeralQuesito-(maiorNota+menorNota);
						ptr[e].notasFinaisQuesitos[q]=ptr[e].quesitos[q].notaFinalQuesito;
					}
					e++;
					break;
				}
				if(e==nEscolas){
					printf("\n\n\tTodas as escolas foram cadastradas!");
					printf("\n\n\tInsira uma opção do menu: ");
					scanf("%d", &opcao);
					break;
				}
				MenuOpcoes();
				printf("\n\n\tInsira uma opção do menu: ");
				scanf("%d", &opcao);
				break;
			
			//Funcionalidade: Buscar e exibir os dados de uma escola pelo nome
			case 3:
				encontrado=0;
				printf("\n\n\t\t\t\t\tBUSCAR POR UMA ESCOLA");
				printf("\n\nInsira o nome da escola que deseja pesquisar: ");
				fflush(stdin);
				gets(busca);
				for(iBusca=0;iBusca<nEscolas;iBusca++){
					contBusca=0;
					for(i=0;ptr[iBusca].nomeEscola[i]!='\0';i++){
						contBusca++;
					}
					contCompara=0;
					for(i=0;busca[i]!='\0';i++){
						if(busca[i]==ptr[iBusca].nomeEscola[i]){
							contCompara++;
						}
					}
					if(contBusca==contCompara){
						encontrado=1;
						printf("\n\nResultados da busca:");
						printf("\n\nNome da escola: %s", ptr[iBusca].nomeEscola);
						printf("\n\nNome do responsável: %s", ptr[iBusca].nomeResp);
						printf("\n\n\tNotas recebidas:");
						for(q=0;q<13;q++){
							printf("\n\nQuesito: %s\n", ptr[iBusca].quesitos[q].nomeQuesito);
							for(n=0;n<5;n++){
								printf("\n\tNota do jurado %d: %.1f", n+1, ptr[iBusca].quesitos[q].notas[n]);
							}
						}
						break;
					}
					else{
						continue;
					}
				}
				if(encontrado!=1){
					printf("\n\tNão foi encontrado um resultado para sua pesquisa");
					printf("\n\n\tInsira uma opção do menu: ");
					scanf("%d", &opcao);
					break;
				}
				MenuOpcoes();
				printf("\n\n\tInsira uma opção do menu: ");
				scanf("%d", &opcao);
				break;
			
			//Funcionalidade: Calcular a nota final de uma escola de samba
			case 4:
				printf("\n\n\t\t\t\tCALCULAR A NOTA FINAL DAS ESCOLAS\n");
				if(e==0){
					printf("\n\n\tNENHUMA ESCOLA FOI CADASTRADA AINDA!");
					printf("\n\n\tInsira uma opção do menu: ");
					scanf("%d", &opcao);
					break;
				}
				for(i=0;i<e;i++){
					q=0;
					ptr[i].notaFinalEscola=calcularNotaFinal(ptr[i].notasFinaisQuesitos, q)/13;
					printf("\n\tNota final da escola %s: %.1f", ptr[i].nomeEscola, ptr[i].notaFinalEscola);
				}
				MenuOpcoes();
				printf("\n\n\tInsira uma opção do menu: ");
				scanf("%d", &opcao);
				break;
			
			//Funcionalidade: Exibir todas as escolas cadastradas e seus respectivos dados
			case 5:
				printf("\n\n\t\t\t\tEXIBIR AS ESCOLAS CADASTRADAS");
				if(e==0){
					printf("\n\n\tNENHUMA ESCOLA FOI CADASTRADA AINDA!");
					printf("\n\n\tInsira uma opção do menu: ");
					scanf("%d", &opcao);
					break;
				}
				for(i=0;i<e;i++){
					printf("\n\nNome da escola: %s", ptr[i].nomeEscola);
					printf("\n\nNome do responsável: %s", ptr[i].nomeResp);
					printf("\n\n\tNotas recebidas:");
					for(q=0;q<13;q++){
						printf("\n\nQuesito: %s\n", ptr[i].quesitos[q].nomeQuesito);
						for(n=0;n<5;n++){
							printf("\n\tNota do jurado %d: %.1f", n+1, ptr[i].quesitos[q].notas[n]);
						}
						printf("\n\nNota final do quesito: %.1f", ptr[i].quesitos[q].notaFinalQuesito);
					}
				}
				MenuOpcoes();
				printf("\n\n\tInsira uma opção do menu: ");
				scanf("%d", &opcao);
				break;
			
			//Funcionalidade: Mostrar as escolas campeã e vice-campeã
			case 6:
				printf("\n\n\t\t\t\tMOSTRAR AS ESCOLAS CAMPEÃ E VICE-CAMPEÃ");
				if((e!=nEscolas)||(e==0)){
					printf("\n\n\tNEM TODAS AS ESCOLAS FORAM CADASTRADAS!");
					printf("\n\n\tInsira uma opção do menu: ");
					scanf("%d", &opcao);
					break;
				}
				else{
					for(i=0;i<nEscolas;i++){
						q=0;
						ptr[i].notaFinalEscola=calcularNotaFinal(ptr[i].notasFinaisQuesitos, q)/13;
					}
					for(i=0;i<nEscolas;i++){
						if(i==0){
							notaCamp=ptr[i].notaFinalEscola;
							iCamp=i;
						}
						else{
							if(ptr[i].notaFinalEscola>=notaCamp){
								notaCamp=ptr[i].notaFinalEscola;
								iCamp=i;
							}
						}
					}
					fst=0;
					for(i=0;i<nEscolas;i++){
						if(i==iCamp){
							continue;
						}
						else{
							if((fst==0)&&(ptr[i].notaFinalEscola<notaCamp)){
								notaVice=ptr[i].notaFinalEscola;
								iVice=i;
								fst++;
							}
							else{
								if((ptr[i].notaFinalEscola>notaVice)&&(ptr[i].notaFinalEscola<notaCamp)){
									notaVice=ptr[i].notaFinalEscola;
									iVice=i;
								}
							}
						}
					}
					printf("\n\nA escola campeã foi %s com %.1f pontos na média geral", ptr[iCamp].nomeEscola, ptr[iCamp].notaFinalEscola);
					printf("\n\nA escola vice-campeã foi %s com %.1f pontos na média geral", ptr[iVice].nomeEscola, ptr[iVice].notaFinalEscola);
				}
				printf("\n\n\tInsira uma opção do menu: ");
				scanf("%d", &opcao);
				break;
			
			//Funcionalidade: Mostrar as duas escolas rebaixadas
			case 7:
				printf("\n\n\t\t\t\tMOSTRAR AS ESCOLAS REBAIXADAS");
				if((e!=nEscolas)||(e==0)){
					printf("\n\n\tNEM TODAS AS ESCOLAS FORAM CADASTRADAS!");
					printf("\n\n\tInsira uma opção do menu: ");
					scanf("%d", &opcao);
					break;
				}
				else{
					for(i=0;i<nEscolas;i++){
						q=0;
						ptr[i].notaFinalEscola=calcularNotaFinal(ptr[i].notasFinaisQuesitos, q)/13;
					}
					for(i=0;i<nEscolas;i++){
						if(i==0){
							notaReb1=ptr[i].notaFinalEscola;
							iReb1=i;
						}
						else{
							if(ptr[i].notaFinalEscola<=notaReb1){
								notaReb1=ptr[i].notaFinalEscola;
								iReb1=i;
							}
						}
					}
					fst=0;
					for(i=0;i<nEscolas;i++){
						if(i==iReb1){
							continue;
						}
						else{
							if((fst==0)&&(ptr[i].notaFinalEscola>notaReb1)){
								notaReb2=ptr[i].notaFinalEscola;
								iReb2=i;
								fst++;
							}
							else{
								if((ptr[i].notaFinalEscola<notaReb2)&&(ptr[i].notaFinalEscola>notaReb1)){
									notaReb2=ptr[i].notaFinalEscola;
									iReb2=i;
								}
							}
						}
					}
					printf("\n\nA escola rebaixadas com a menor nota foi %s com %.1f pontos na média geral", ptr[iReb1].nomeEscola, ptr[iReb1].notaFinalEscola);
					printf("\n\nA escola rebaixada com a segunda menor nota foi %s com %.1f pontos na média geral", ptr[iReb2].nomeEscola, ptr[iReb2].notaFinalEscola);
				}
				printf("\n\n\tInsira uma opção do menu: ");
				scanf("%d", &opcao);
				break;
				
			//Funcionalidade: Gravar os dados das escolas em um arquivo no disco
			case 8:
				printf("\n\n\t\t\t\tGRAVAR OS CADASTROS DAS ESCOLAS");
				erroFechamento=1;
				arquivo=fopen("Cadastro das escolas.txt", "w");
				if(arquivo==NULL){
					printf("\n\n\tFalha ao abrir o arquivo!");
					exit(1);
				}
				for(i=0;i<nEscolas;i++){
					fprintf(arquivo, "Nome da escola: %s", ptr[i].nomeEscola);
					fprintf(arquivo, "\n\nNome do responsável: %s", ptr[i].nomeResp);
					for(q=0;q<13;q++){
						fprintf(arquivo, "\n\nQuesito: %s\n", ptr[i].quesitos[q].nomeQuesito);
						for(n=0;n<5;n++){
							fprintf(arquivo, "\n\tNota do jurado %d: %.1f", n+1, ptr[i].quesitos[q].notas[n]);
						}
					}
					fprintf(arquivo, "\n\n");
				}
				erroFechamento=fclose(arquivo);
				if(erroFechamento!=0){
					printf("\n\n\tFalha ao fechar o arquivo!");
				}
				else{
					printf("\n\n\tArquivo salvo com sucesso!");
				}
				MenuOpcoes();
				printf("\n\n\tInsira uma opção do menu: ");
				scanf("%d", &opcao);
				break;
				
			//Funcionalidade: Carregar os dados das escolas de um arquivo no disco
			case 9:
				printf("\n\n\t\t\t\tCARREGAR OS CADASTROS DAS ESCOLAS");
				printf("\n\nInforme quantas escolas foram cadastradas: ");
				scanf("%d", &nEscolas);
				e=nEscolas;
				ptr=(Escola*)malloc(nEscolas*sizeof(Escola));
				if(ptr==NULL){
					printf("\n\n\tFalha ao alocar na memória!");
					exit(1);
				}
				erroFechamento=1;
				arquivo=fopen("Cadastro das escolas.txt", "r");
				if(arquivo==NULL){
					printf("\n\n\tFalha ao abrir o arquivo!");
					exit(1);
				}
				for(i=0;i<nEscolas;i++){
					fscanf(arquivo, "%s %s %s", placeHolder, placeHolder, placeHolder);
					placeHolderChar = fgetc(arquivo);
					fgets(ptr[i].nomeEscola, 31, arquivo);
					for(c=0;c<31;c++){
						if(ptr[i].nomeEscola[c]=='\n'){
							ptr[i].nomeEscola[c]='\0';
						}
					}
					fscanf(arquivo, "%s %s %s", placeHolder, placeHolder, placeHolder);
					placeHolderChar = fgetc(arquivo);
					fgets(ptr[i].nomeResp, 31, arquivo);
					for(c=0;c<31;c++){
						if(ptr[i].nomeResp[c]=='\n'){
							ptr[i].nomeResp[c]='\0';
						}
					}
					printf("\n\tCadastro da escola %s carregado com sucesso!", ptr[i].nomeEscola);
					for(q=0;q<13;q++){
						fscanf(arquivo, "%s", placeHolder);
						placeHolderChar = fgetc(arquivo);
						fgets(ptr[i].quesitos[q].nomeQuesito, 31, arquivo);
						for(c=0;c<31;c++){
							if(ptr[i].quesitos[q].nomeQuesito[c]=='\n'){
								ptr[i].quesitos[q].nomeQuesito[c]='\0';
							}
						}
						for(n=0;n<5;n++){
							fscanf(arquivo, "%s %s %s %s", placeHolder, placeHolder, placeHolder, placeHolder);
							placeHolderChar = fgetc(arquivo);
							fscanf(arquivo, "%f", &(ptr[i].quesitos[q].notas[n]));
						}
					}
					for(q=0;q<13;q++){
						somaGeralQuesito=0;
						for(n=0;n<5;n++){
							if(n==0){
								maiorNota=ptr[i].quesitos[q].notas[n];
								menorNota=ptr[i].quesitos[q].notas[n];
							}
							else{
								if(ptr[i].quesitos[q].notas[n]>=maiorNota){
									maiorNota=ptr[i].quesitos[q].notas[n];
								}
								if(ptr[i].quesitos[q].notas[n]<=menorNota){
									menorNota=ptr[i].quesitos[q].notas[n];
								}
							}
							somaGeralQuesito=somaGeralQuesito+ptr[i].quesitos[q].notas[n];
						}
						ptr[i].quesitos[q].notaFinalQuesito=somaGeralQuesito-(maiorNota+menorNota);
						ptr[i].notasFinaisQuesitos[q]=ptr[i].quesitos[q].notaFinalQuesito;
					}
				}
				erroFechamento=fclose(arquivo);
				if(erroFechamento!=0){
					printf("\n\n\tFalha ao fechar o arquivo!");
				}
				MenuOpcoes();
				printf("\n\n\tInsira uma opção do menu: ");
				scanf("%d", &opcao);
				break;
				
			default:
				printf("\n\n\tOpção inválida, escolha outra opção do menu: ");
				scanf("%d", &opcao);
				break;
			}
	}
}
