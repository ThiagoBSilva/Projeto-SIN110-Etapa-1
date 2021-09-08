#include <stdio.h>
#include <string.h>

//Criação de estrutura de um quesito.
typedef struct sQuesito{
	char nomeQues[31];			//nomeQues = string com o nome do Quesito
	float notasJur[5];			//notasJur = vetor com cada nota de cada jurado para determinado Quesito
	float notaFQues;			//notaFQues = nota final do quesito (soma de todas as notas menos a maior e a menor nota)
}Quesito;

//Criação da estrutura de uma escola de samba.
typedef struct sEscolaSamba{
	char nomeEsc[31];			//nomeEsc = string com o nome da Escola de Samba
	char nomeResp[31];			//nomeResp = string com o nome do responsável pela Escola de Samba
	Quesito ques[13];			//ques = vetor do tipo quesito com cada um dos Quesitos avaliados e suas notas dos 5 jurados
	float mediaGeral;			//mediaGeral = nota final da escola (soma a nota final de cada um dos quesitos e divide pelo número de quesitos (13))
}EscolaSamba;

float media(float vet[]){		//Cálculo da nota final de cada quesito
	int i;
	float maNota, meNota;
	float media=0.0, soma=0.0;
	for(i=0;i<5;i++){
		if(i==0){
			meNota=vet[i];
			maNota=vet[i];
		}
		else{
			if(vet[i]>=maNota){
				maNota=vet[i];
			}
			if(vet[i]<=meNota){
				meNota=vet[i];
			}

		}
	}
	for(i=0;i<5;i++){
			soma+=vet[i];
	}
	media=soma-(maNota+meNota);
	return media;
}

int conta(char str[]){			//Contar quantos caracteres o nome da escola tem
	int c=0, i;
	for(i=0;str[i]!='\0';i++){
		c++;
	}
	return c;
}

int comp(char str[], char str1[]){		//Comparar a string de busca com o nome das escolas
	int flog=1,cont1=0,cont2=0,s;
	cont1=conta(str);
	cont2=conta(str1);
	if(cont1==cont2){
		for(s=0;str[s]!='\0';s++){
			if(str[s]!=str1[s]){
				flog=0;
				break;
			}
		}
	}else{
		flog=0;
	}
	return flog;
}

int main(){
	EscolaSamba esc[10];		//esc = vetor do tipo EscolaSamba com os dados de todas as 10 Escolas de Samba
	int i, flog=1;						//i = variável usada para percorrer os vetores
	//Inicialização do nome dos Quesitos
	for(i=0;i<10;i++){
		strcpy(esc[i].ques[0].nomeQues, "Bateria");
		strcpy(esc[i].ques[1].nomeQues, "Samba-Enredo");
		strcpy(esc[i].ques[2].nomeQues, "Harmonia");
		strcpy(esc[i].ques[3].nomeQues, "Evolução");
		strcpy(esc[i].ques[4].nomeQues, "Enredo");
		strcpy(esc[i].ques[5].nomeQues, "Conjunto");
		strcpy(esc[i].ques[6].nomeQues, "Alegorias e Adereços");
		strcpy(esc[i].ques[7].nomeQues, "Fantasias");
		strcpy(esc[i].ques[8].nomeQues, "Comissão de Frente");
		strcpy(esc[i].ques[9].nomeQues, "Mestre-Sala e Porta-Bandeira");
		strcpy(esc[i].ques[10].nomeQues, "Introdução");
		strcpy(esc[i].ques[11].nomeQues, "Performance");
		strcpy(esc[i].ques[12].nomeQues, "Finalização");
	}
	//Inicialização do vetor esc
	for(i=0;i<10;i++){
		strcpy(esc[i].nomeEsc, "Não Cadastrado");		//O nome da escola no vetor i é Não Cadastrado, isso significa que nenhuma escola foi cadastrada naquele índice do vetor
	}
	//Introdução ao menu do usuário.
	int opcao;											//opcao = variável que receberá o valor do código da operação escolhida no menu pelo usuário
	printf("\t\t\t\t\tBEM VINDO");
	printf("\n\n\t\tVocê está utilizando o programa de gerenciamento das\n\t\t\tescolas de samba do Rio Paranaíba!");
	printf("\n\nSelecione alguma funcionalidade do menu abaixo para começar.\n");
	printf("\n\n\t\t\t\t\tMENU DE OPÇÕES\n");
	printf("\n(1) - Sair do programa\t\t\t\t\t(5) - Mostrar todas as escolas de samba cadastradas");
	printf("\n(2) - Cadastrar uma escola de samba\t\t\t(6) - Mostrar a escola campeã e a vice-campeã");
	printf("\n(3) - Buscar por uma escola de samba\t\t\t(7) - Mostrar as escolas rebaixadas");
	printf("\n\nDigite a operação que deseja executar: ");
	scanf("%d", &opcao);
	//Construção do menu e suas respectivas funcionalidades						//VARIÁVEIS DO MENU
	int escCad=0, c;								//escCad = variável que representa quantas escolas foram cadastradas| c = contador de caracteres
	int e, q, n;									//e = variável que percorrerá o vetor da escola|q = o mesmo, só que para os quesitos|n = o mesmo, só que para as notas
	char NaoCadastrado[31];							//string para usada para comparar se a escola ainda não foi cadastrada
	float maNota, meNota, somaQues, somaGeral;	//maNota = maior nota do quesito| meNota = menor nota do quesito|somaQues = soma total do quesito|somaGeral = soma das notas finais dos quesitos
	float notaC, notaVC;							//notaC = maior dentre todas as médias gerais, define o campeão|notaVC = a segunda maior dentre as médias gerais, define o vice-campeão
	int iC, iVC;									//iC = índice da escola campeã|iVC = índice da escola vice-campeã
	float notaReb1, notaReb2;						//notaReb1 = menor dentre todas as médias gerais, define a escola rebaixada com a menor média|notaReb2 = segunda menor dentre todas as médias gerais, define a escola rebeixada com a segunda menor média
	int	iReb1, iReb2;								//iReb1 = índice da escola rebaixada com a menor média|iReb2 = índice da escola rebeixada com a segunda menor média
	char busca[31];									//busca = string inserida pelo usuário quando este pretende pesquisar uma escola cadastrada
	int encontrado;									//encontrado = se for igual a 1, foi encontrado um resultado para a busca, se for diferente de 1, não foram encontrados resultados para a busca
	strcpy(NaoCadastrado, "Não Cadastrado");		//A string NaoCadastrado só vai servir para a comparação com o nome das escolas, se ambas forem iguais, isso significa que a escola não foi cadastrada ainda
	int fst;										//fst = uma variável de uso único por funcionalidade do menu, com o propósito de inicializar valores para as segundas maiores e menores notas das escolas
	while(opcao!=1){		//Enquanto a opção selecionada não for para sair do programa...
		switch(opcao){
			case 1:				//case 1 = sair do programa
				break;
			case 2:				//case 2 = cadastrar uma escola
				while(escCad<10){			//Enquanto não forem cadastradas todas as 10 escolas, a operação de cadastramento ficará disponível
					printf("\n\n\t\tVOCÊ SELECIONOU A OPERAÇÃO DE CADASTRAMENTO");
					//O usuário irá informar o nome da escola de samba
					printf("\n\nInsira o nome da escola de samba que deseja cadastrar: ");
					fflush(stdin);
					gets(esc[escCad].nomeEsc);
					c=conta(esc[escCad].nomeEsc);		//A função contaCaracteres recebe a string a ser analisada e conta, inicializando um valor em 'c'
					if(c<8){									//Se o contador tiver um valor menor que 8, o usuário terá que reinserir o nome, até que contador seja maior ou igual a 8
						while(c<8){
							printf("\n\tERRO: Por favor, insira um nome com oito ou mais caracteres: ");
							gets(esc[escCad].nomeEsc);
							c=conta(esc[escCad].nomeEsc);
							}
					}
					//Depois de colocar um nome maior ou igual a 8 caracteres, o usuário poderá informar o nome do responsável
					printf("\nInsira o nome do responsável pela escola de samba: ");
					gets(esc[escCad].nomeResp);
					//Depois de inserir o nome do responsável, o usuário poderá inserir as notas dadas pelos jurados em cada quesito
					for(q=0;q<13;q++){
						printf("\nQuesito avaliado: %s\n\n", esc[escCad].ques[q].nomeQues);			//Para cada quesito, 5 notas serão armazenadas
						for(n=0;n<5;n++){
							printf("\tInsira a nota do jurado %d: ", n+1);
							scanf("%f", &esc[escCad].ques[q].notasJur[n]);
							if((esc[escCad].ques[q].notasJur[n]<7)||(esc[escCad].ques[q].notasJur[n]>10)){	//Se as notas forem <7 ou >10, o usuário terá de reinserir uma nota válida
								while((esc[escCad].ques[q].notasJur[n]<7)||(esc[escCad].ques[q].notasJur[n]>10)){
									printf("\n\tERRO: Insira uma nota válida (entre 7 e 10, inclusive): ");
									scanf("%f", &esc[escCad].ques[q].notasJur[n]);
									printf("\n");
								}
							}
						}
					}
					//Depois de cadastrar todas as notas dos jurados para cada um dos quesitos, o processo de cadastramento termina
					printf("\n\tA escola %s foi cadastrada com sucesso!\n", esc[escCad].nomeEsc);
					//A variável escCad é incrementada pois, a próxima vez que a operação de cadastro for utilizada, os dados serão armazenados no próximo endereço do vetor escola
					escCad++;
					break;
				}
				if(escCad==10){			//Se escCad=10, significa então que todas os 10 vetores das escolas foram preenchidos, então, aparecerá uma mensagem avisando isso
					printf("\nTodas as %d escolas foram cadastradas, escolha outra opção do menu.", escCad);
				}
				//O usuário poderá utilizar outra função do menu que desejar
				printf("\n\nDigite a operação que deseja executar: ");
				scanf("%d", &opcao);
				break;
			case 3:				//case 3 = buscar por uma escola
				printf("\n\n\t\tVOCÊ SELECIONOU A OPERAÇÃO DE BUSCAR POR UMA ESCOLA");
				printf("\n\nInsira o nome da escola que deseja pesquisar: ");
				fflush(stdin);
				gets(busca);
				encontrado = 0;
				for(e=0;e<10;e++){			//O programa vai percorrer o vetor das escolas
					flog=comp(esc[e].nomeEsc,busca);
					if(flog==1){			//Se o número de caracteres semelhantes for o mesmo que o número de caracteres do nome da escola "e", isso significa que as palavras são iguais
						encontrado = 1;
						printf("\n\n\t\tRESULTADOS DA PESQUISA");		//O programa irá mostrar os resultados da pesquisa se as palavras forem iguais
						printf("\n\nNome da escola: %s", esc[e].nomeEsc);			//Nome da escola
						printf("\n\nNome do responsável: %s", esc[e].nomeResp);			//Nome do responsável
						printf("\n\n\tNOTAS RECEBIDAS PELA ESCOLA:");							//Notas recebidas, por quesito
						for(q=0;q<13;q++){
							printf("\n\nQuesito avaliado: %s\n", esc[e].ques[q].nomeQues);
							for(n=0;n<5;n++){
								printf("\n\tNota do jurado %d: %.1f", n+1, esc[e].ques[q].notasJur[n]);
							}
						}
					}
					else{			//Se a escola analisada não for o resultado correspondente da busca, a próxima escola do vetor vai ser analisada e assim por diante
						continue;
					}
				}
				if(encontrado!=1){	//Se, após a verificação de todas as 10 escolas, nenhuma corresponder à busca, a variável "encontrado" não mudará de valor, logo, será diferente de um, o que significa que nenhuma escola foi encontrada na busca
					printf("\n\n\tO nome inserido não corresponde a uma escola válida, ou ela não foi cadastrada ainda!\n");
				}
				//O usuário poderá utilizar outra função do menu que desejar
				printf("\n\nPor favor, digite outra operação que deseja executar: ");
				scanf("%d", &opcao);
				break;
			case 5:				//case 5 = mostrar todas as escolas cadastradas
				printf("\n\n\t\tVOCÊ ESCOLHEU A OPERAÇÃO DE MOSTRAR AS ESCOLAS CADASTRADAS");
				if(escCad==0){
					printf("\n\n\tVocê não cadastrou nenhuma escola ainda!\n");
				}
				else{
					for(e=0;e<10;e++){			//Será analisado o vetor das escolas
						c=0;
						somaGeral=0;
						for(i=0;esc[e].nomeEsc[i]!='\0';i++){		//Será feito uma verificação, se o nome da escola é "Não Cadastrado"
							if(esc[e].nomeEsc[i]==NaoCadastrado[i]){		//Para isso, será feito uma comparação entre o nome da escola e a string NaoCadastrado
								c=c+1;										//Se elas tiverem caracteres em comum, o contador será incrementado em +1
							}
						}
						if(c==14){		//Se o contador for igual a 14, que é o tamanho da frase "Não Cadastrado", o programa irá verificar outra escola
							continue;
						}
						else{										//Caso contrário, será mostrado o nome da escola, o nome do responsável, a nota de cada jurado para cada quesito e a nota final de cada quesito
							printf("\n\n\n______________________________________________________\n\n\n");
							printf("\n\nNome da escola: %s", esc[e].nomeEsc);
							printf("\n\nNome do responsável: %s", esc[e].nomeResp);
							printf("\n\n\t\tNotas: ");
							for(q=0;q<13;q++){				//O programa vai percorrer o vetor dos quesitos
								printf("\n\nQuesito avaliado: %s\n", esc[e].ques[q].nomeQues);
								somaQues=0;
								for(n=0;n<5;n++){			//O programa vai percorrer o vetor das notas
									printf("\n\tNota do jurado %d: %.1f", n+1, esc[e].ques[q].notasJur[n]);
								}
								esc[e].ques[q].notaFQues = media(esc[e].ques[q].notasJur);
								somaGeral = somaGeral+esc[e].ques[q].notaFQues;			//A nota final do quesito é a soma total menos a maior e a menor nota
								printf("\n\nNota final no Quesito: %.1f", esc[e].ques[q].notaFQues);
							}
							esc[e].mediaGeral = somaGeral/13;
							printf("\n\n\tNota final da Escola: %.1f", esc[e].mediaGeral);
						}
					}
				}
				//O usuário poderá utilizar outra função do menu que desejar
				printf("\n\nDigite a operação que deseja executar: ");
				scanf("%d", &opcao);
				break;
			case 6:				//case 6 = mostrar a escola campeã e a vice-campeã
				printf("\n\n\t\tVOCÊ ESCOLHEU A OPERAÇÃO DE MOSTRAR A ESCOLA CAMPEÃ E VICE-CAMPEÃ");
				if(escCad!=10){			//Se escCad for diferente de 10, isso significa que nem todas as escolas foram cadastradas, logo, não dá pra saber as escolas campeãs e vice-campeãs
					printf("\n\n\tNem todas as escolas foram cadastradas ainda!");
					printf("\n\nPor favor, escolha outra opção: ");
					scanf("%d", &opcao);
					break;
				}
				else{					//Se todas as escolas foram cadastradas, será feita a verificação
					for(e=0;e<10;e++){			//O programa vai percorrer o vetor das escolas
						somaGeral=0;
						for(q=0;q<13;q++){			//O programa vai percorrer o vetor dos quesitos
							somaQues=0;
							esc[e].ques[q].notaFQues = media(esc[e].ques[q].notasJur);
							somaGeral = somaGeral + esc[e].ques[q].notaFQues;
						}
						//Faz-se o cálculo da média geral da escola "e" dividindo a soma geral dos quesitos por 13 (número de quesitos)
						esc[e].mediaGeral = somaGeral/13;
					}
					//Calculando todas as notas, para as respectivas escolas, será feito a comparação das médias gerais
					for(e=0;e<10;e++){						//Percorrerá o vetor das escolas, analisando e classificando as notas
						if(e==0){							//Se for a primeira escola, ela terá automaticamente a melhor dentre as médias, para comparação com as demais
							notaC = esc[e].mediaGeral;
							iC = e;
						}
						else{
							if(esc[e].mediaGeral>notaC){	//Se a média da escola "e" for maior que a maior nota anterior, a média da escola "e" passará a ser a maior nota
								notaC = esc[e].mediaGeral;
								iC = e;
							}
						}
					}
					//Após definir a escola campeã, será definida a escola vice-campeã
					fst=0;
					for(e=0;e<10;e++){
						if(e==iC){					//Se o índice da escola "e", for igual ao índice da escola campeã, o programa irá pular a verificação da escola, uma vez que ela já é a campeã
							continue;
						}
						else{
							if((fst==0)&&(esc[e].mediaGeral<notaC)){
								notaVC = esc[e].mediaGeral;
								iVC = e;
								fst++;
							}
							else{
								if((esc[e].mediaGeral>notaVC)&&(esc[e].mediaGeral<notaC)){		//Se a nota analisada for maior que a nota da atual vice-campeã e menor do que a nota campeã, a nota analisada passará a ser a vice-campeã
									notaVC = esc[e].mediaGeral;
									iVC = e;
								}
							}
						}
					}
					//Será impresso na tela as escolas campeã e vice-campeã
					printf("\n\nA escola campeã foi %s com %.1f pontos na média geral", esc[iC].nomeEsc, esc[iC].mediaGeral);
					printf("\n\nA escola vice-campeã foi %s com %.1f pontos na média geral", esc[iVC].nomeEsc, esc[iVC].mediaGeral);
				}
				//O usuário poderá então escolher outra opção do menu
				printf("\n\nDigite a operação que deseja executar: ");
				scanf("%d", &opcao);
				break;
			case 7:				//case 7 = mostrar as duas escolas rebaixadas
				printf("\n\n\t\tVOCÊ ESCOLHEU A OPERAÇÃO DE MOSTRAR AS DUAS ESCOLAS REBAIXADAS");
				if(escCad!=10){
					printf("\n\n\tNem todas as escolas foram cadastradas ainda!");
					printf("\n\nPor favor, escolha outra opção: ");
					scanf("%d", &opcao);
					break;
				}
				else{
					for(e=0;e<10;e++){			//O programa vai percorrer o vetor das escolas
						somaGeral=0;
						for(q=0;q<13;q++){			//O programa vai percorrer o vetor dos quesitos
							somaQues=0;
							esc[e].ques[q].notaFQues = media(esc[e].ques[q].notasJur);
							somaGeral = somaGeral + esc[e].ques[q].notaFQues;
						}
						//Faz-se o cálculo da média geral da escola "e" dividindo a soma geral dos quesitos por 13 (número de quesitos)
						esc[e].mediaGeral = somaGeral/13;
					}
					//Calculando todas as notas, para as respectivas escolas, será feito a comparação das médias gerais
					for(e=0;e<10;e++){					//Percorrerá o vetor das escolas, analisando e classificando as notas
						if(e==0){						//Se for a primeira escola, sua nota será automaticamente a pior, para comparação com as demais
							notaReb1=esc[e].mediaGeral;
							iReb1 = e;
						}
						else{
							if(esc[e].mediaGeral<notaReb1){			//Se a média da escola "e" for menor que a nota de rebaixamento, a nota de rebaixamento passará a ser a média da escola "e"
								notaReb1 = esc[e].mediaGeral;
								iReb1 = e;
							}
						}
					}
					//Após definir a escola rebaixada com menor média, será definida a escola rebaixada com a segunda menor média
					fst=0;
					for(e=0;e<10;e++){
						if(e==iReb1){		//Se o índice da escola "e" for igual ao da escola rebaixada com a pior média, o programa irá pular a verificação dessa escola
							continue;
						}
						else{
							if((fst==0)&&(esc[e].mediaGeral>notaReb1)){
								notaReb2 = esc[e].mediaGeral;
								iReb2 = e;
								fst++;
							}
							else{
								if((esc[e].mediaGeral<notaReb2)&&(esc[e].mediaGeral>notaReb1)){			//Se a média da escola "e" for menor que a segunda nota de rebaixamento e maior que a primeira nota de rebaixamento, a média da escola "e" passará a ser a segunda nota de rebaixamento
									notaReb2 = esc[e].mediaGeral;
									iReb2 = e;
								}
							}
						}
					}
					//Será impresso na tela as escolas rebaixadas com a menor nota e com a segunda menor nota, respectivamente
					printf("\n\nA escola rebaixada com a menor nota foi %s com %.1f pontos na média geral", esc[iReb1].nomeEsc, esc[iReb1].mediaGeral);
					printf("\n\nA escola rebaixada com a segunda menor nota foi %s com %.1f pontos na média geral", esc[iReb2].nomeEsc, esc[iReb2].mediaGeral);
				}
				//O usuário poderá então escolher outra opção do menu
				printf("\n\nDigite a operação que deseja executar: ");
				scanf("%d", &opcao);
				break;
			default:			//default = reinserir o valor da opção, já que a operação selecionada não existe
				printf("\n\nA operação desejada não existe ou não foi implementada ainda. Tente novamente.\n");
				printf("\n\n\tDigite a operação que deseja executar: ");
				scanf("%d", &opcao);
				break;
		}
	}
	printf("\n\n\tObrigado pela visita! Volte sempre.\n\n");
	return 0;
}
