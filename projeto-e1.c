#include <stdio.h>
#include <string.h>

//Cria��o de estrutura de um quesito.
typedef struct sQuesito{
	char nomeQues[31];			//nomeQues = string com o nome do Quesito
	float notasJur[5];			//notasJur = vetor com cada nota de cada jurado para determinado Quesito
	float notaFQues;			//notaFQues = nota final do quesito (soma de todas as notas menos a maior e a menor nota)
}Quesito;

//Cria��o da estrutura de uma escola de samba.
typedef struct sEscolaSamba{
	char nomeEsc[31];			//nomeEsc = string com o nome da Escola de Samba
	char nomeResp[31];			//nomeResp = string com o nome do respons�vel pela Escola de Samba
	Quesito ques[13];			//ques = vetor do tipo quesito com cada um dos Quesitos avaliados e suas notas dos 5 jurados
	float mediaGeral;			//mediaGeral = nota final da escola (soma a nota final de cada um dos quesitos e divide pelo n�mero de quesitos (13))
}EscolaSamba;

float media(float vet[]){		//C�lculo da nota final de cada quesito
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
	int i, flog=1;						//i = vari�vel usada para percorrer os vetores
	//Inicializa��o do nome dos Quesitos
	for(i=0;i<10;i++){
		strcpy(esc[i].ques[0].nomeQues, "Bateria");
		strcpy(esc[i].ques[1].nomeQues, "Samba-Enredo");
		strcpy(esc[i].ques[2].nomeQues, "Harmonia");
		strcpy(esc[i].ques[3].nomeQues, "Evolu��o");
		strcpy(esc[i].ques[4].nomeQues, "Enredo");
		strcpy(esc[i].ques[5].nomeQues, "Conjunto");
		strcpy(esc[i].ques[6].nomeQues, "Alegorias e Adere�os");
		strcpy(esc[i].ques[7].nomeQues, "Fantasias");
		strcpy(esc[i].ques[8].nomeQues, "Comiss�o de Frente");
		strcpy(esc[i].ques[9].nomeQues, "Mestre-Sala e Porta-Bandeira");
		strcpy(esc[i].ques[10].nomeQues, "Introdu��o");
		strcpy(esc[i].ques[11].nomeQues, "Performance");
		strcpy(esc[i].ques[12].nomeQues, "Finaliza��o");
	}
	//Inicializa��o do vetor esc
	for(i=0;i<10;i++){
		strcpy(esc[i].nomeEsc, "N�o Cadastrado");		//O nome da escola no vetor i � N�o Cadastrado, isso significa que nenhuma escola foi cadastrada naquele �ndice do vetor
	}
	//Introdu��o ao menu do usu�rio.
	int opcao;											//opcao = vari�vel que receber� o valor do c�digo da opera��o escolhida no menu pelo usu�rio
	printf("\t\t\t\t\tBEM VINDO");
	printf("\n\n\t\tVoc� est� utilizando o programa de gerenciamento das\n\t\t\tescolas de samba do Rio Parana�ba!");
	printf("\n\nSelecione alguma funcionalidade do menu abaixo para come�ar.\n");
	printf("\n\n\t\t\t\t\tMENU DE OP��ES\n");
	printf("\n(1) - Sair do programa\t\t\t\t\t(5) - Mostrar todas as escolas de samba cadastradas");
	printf("\n(2) - Cadastrar uma escola de samba\t\t\t(6) - Mostrar a escola campe� e a vice-campe�");
	printf("\n(3) - Buscar por uma escola de samba\t\t\t(7) - Mostrar as escolas rebaixadas");
	printf("\n\nDigite a opera��o que deseja executar: ");
	scanf("%d", &opcao);
	//Constru��o do menu e suas respectivas funcionalidades						//VARI�VEIS DO MENU
	int escCad=0, c;								//escCad = vari�vel que representa quantas escolas foram cadastradas| c = contador de caracteres
	int e, q, n;									//e = vari�vel que percorrer� o vetor da escola|q = o mesmo, s� que para os quesitos|n = o mesmo, s� que para as notas
	char NaoCadastrado[31];							//string para usada para comparar se a escola ainda n�o foi cadastrada
	float maNota, meNota, somaQues, somaGeral;	//maNota = maior nota do quesito| meNota = menor nota do quesito|somaQues = soma total do quesito|somaGeral = soma das notas finais dos quesitos
	float notaC, notaVC;							//notaC = maior dentre todas as m�dias gerais, define o campe�o|notaVC = a segunda maior dentre as m�dias gerais, define o vice-campe�o
	int iC, iVC;									//iC = �ndice da escola campe�|iVC = �ndice da escola vice-campe�
	float notaReb1, notaReb2;						//notaReb1 = menor dentre todas as m�dias gerais, define a escola rebaixada com a menor m�dia|notaReb2 = segunda menor dentre todas as m�dias gerais, define a escola rebeixada com a segunda menor m�dia
	int	iReb1, iReb2;								//iReb1 = �ndice da escola rebaixada com a menor m�dia|iReb2 = �ndice da escola rebeixada com a segunda menor m�dia
	char busca[31];									//busca = string inserida pelo usu�rio quando este pretende pesquisar uma escola cadastrada
	int encontrado;									//encontrado = se for igual a 1, foi encontrado um resultado para a busca, se for diferente de 1, n�o foram encontrados resultados para a busca
	strcpy(NaoCadastrado, "N�o Cadastrado");		//A string NaoCadastrado s� vai servir para a compara��o com o nome das escolas, se ambas forem iguais, isso significa que a escola n�o foi cadastrada ainda
	int fst;										//fst = uma vari�vel de uso �nico por funcionalidade do menu, com o prop�sito de inicializar valores para as segundas maiores e menores notas das escolas
	while(opcao!=1){		//Enquanto a op��o selecionada n�o for para sair do programa...
		switch(opcao){
			case 1:				//case 1 = sair do programa
				break;
			case 2:				//case 2 = cadastrar uma escola
				while(escCad<10){			//Enquanto n�o forem cadastradas todas as 10 escolas, a opera��o de cadastramento ficar� dispon�vel
					printf("\n\n\t\tVOC� SELECIONOU A OPERA��O DE CADASTRAMENTO");
					//O usu�rio ir� informar o nome da escola de samba
					printf("\n\nInsira o nome da escola de samba que deseja cadastrar: ");
					fflush(stdin);
					gets(esc[escCad].nomeEsc);
					c=conta(esc[escCad].nomeEsc);		//A fun��o contaCaracteres recebe a string a ser analisada e conta, inicializando um valor em 'c'
					if(c<8){									//Se o contador tiver um valor menor que 8, o usu�rio ter� que reinserir o nome, at� que contador seja maior ou igual a 8
						while(c<8){
							printf("\n\tERRO: Por favor, insira um nome com oito ou mais caracteres: ");
							gets(esc[escCad].nomeEsc);
							c=conta(esc[escCad].nomeEsc);
							}
					}
					//Depois de colocar um nome maior ou igual a 8 caracteres, o usu�rio poder� informar o nome do respons�vel
					printf("\nInsira o nome do respons�vel pela escola de samba: ");
					gets(esc[escCad].nomeResp);
					//Depois de inserir o nome do respons�vel, o usu�rio poder� inserir as notas dadas pelos jurados em cada quesito
					for(q=0;q<13;q++){
						printf("\nQuesito avaliado: %s\n\n", esc[escCad].ques[q].nomeQues);			//Para cada quesito, 5 notas ser�o armazenadas
						for(n=0;n<5;n++){
							printf("\tInsira a nota do jurado %d: ", n+1);
							scanf("%f", &esc[escCad].ques[q].notasJur[n]);
							if((esc[escCad].ques[q].notasJur[n]<7)||(esc[escCad].ques[q].notasJur[n]>10)){	//Se as notas forem <7 ou >10, o usu�rio ter� de reinserir uma nota v�lida
								while((esc[escCad].ques[q].notasJur[n]<7)||(esc[escCad].ques[q].notasJur[n]>10)){
									printf("\n\tERRO: Insira uma nota v�lida (entre 7 e 10, inclusive): ");
									scanf("%f", &esc[escCad].ques[q].notasJur[n]);
									printf("\n");
								}
							}
						}
					}
					//Depois de cadastrar todas as notas dos jurados para cada um dos quesitos, o processo de cadastramento termina
					printf("\n\tA escola %s foi cadastrada com sucesso!\n", esc[escCad].nomeEsc);
					//A vari�vel escCad � incrementada pois, a pr�xima vez que a opera��o de cadastro for utilizada, os dados ser�o armazenados no pr�ximo endere�o do vetor escola
					escCad++;
					break;
				}
				if(escCad==10){			//Se escCad=10, significa ent�o que todas os 10 vetores das escolas foram preenchidos, ent�o, aparecer� uma mensagem avisando isso
					printf("\nTodas as %d escolas foram cadastradas, escolha outra op��o do menu.", escCad);
				}
				//O usu�rio poder� utilizar outra fun��o do menu que desejar
				printf("\n\nDigite a opera��o que deseja executar: ");
				scanf("%d", &opcao);
				break;
			case 3:				//case 3 = buscar por uma escola
				printf("\n\n\t\tVOC� SELECIONOU A OPERA��O DE BUSCAR POR UMA ESCOLA");
				printf("\n\nInsira o nome da escola que deseja pesquisar: ");
				fflush(stdin);
				gets(busca);
				encontrado = 0;
				for(e=0;e<10;e++){			//O programa vai percorrer o vetor das escolas
					flog=comp(esc[e].nomeEsc,busca);
					if(flog==1){			//Se o n�mero de caracteres semelhantes for o mesmo que o n�mero de caracteres do nome da escola "e", isso significa que as palavras s�o iguais
						encontrado = 1;
						printf("\n\n\t\tRESULTADOS DA PESQUISA");		//O programa ir� mostrar os resultados da pesquisa se as palavras forem iguais
						printf("\n\nNome da escola: %s", esc[e].nomeEsc);			//Nome da escola
						printf("\n\nNome do respons�vel: %s", esc[e].nomeResp);			//Nome do respons�vel
						printf("\n\n\tNOTAS RECEBIDAS PELA ESCOLA:");							//Notas recebidas, por quesito
						for(q=0;q<13;q++){
							printf("\n\nQuesito avaliado: %s\n", esc[e].ques[q].nomeQues);
							for(n=0;n<5;n++){
								printf("\n\tNota do jurado %d: %.1f", n+1, esc[e].ques[q].notasJur[n]);
							}
						}
					}
					else{			//Se a escola analisada n�o for o resultado correspondente da busca, a pr�xima escola do vetor vai ser analisada e assim por diante
						continue;
					}
				}
				if(encontrado!=1){	//Se, ap�s a verifica��o de todas as 10 escolas, nenhuma corresponder � busca, a vari�vel "encontrado" n�o mudar� de valor, logo, ser� diferente de um, o que significa que nenhuma escola foi encontrada na busca
					printf("\n\n\tO nome inserido n�o corresponde a uma escola v�lida, ou ela n�o foi cadastrada ainda!\n");
				}
				//O usu�rio poder� utilizar outra fun��o do menu que desejar
				printf("\n\nPor favor, digite outra opera��o que deseja executar: ");
				scanf("%d", &opcao);
				break;
			case 5:				//case 5 = mostrar todas as escolas cadastradas
				printf("\n\n\t\tVOC� ESCOLHEU A OPERA��O DE MOSTRAR AS ESCOLAS CADASTRADAS");
				if(escCad==0){
					printf("\n\n\tVoc� n�o cadastrou nenhuma escola ainda!\n");
				}
				else{
					for(e=0;e<10;e++){			//Ser� analisado o vetor das escolas
						c=0;
						somaGeral=0;
						for(i=0;esc[e].nomeEsc[i]!='\0';i++){		//Ser� feito uma verifica��o, se o nome da escola � "N�o Cadastrado"
							if(esc[e].nomeEsc[i]==NaoCadastrado[i]){		//Para isso, ser� feito uma compara��o entre o nome da escola e a string NaoCadastrado
								c=c+1;										//Se elas tiverem caracteres em comum, o contador ser� incrementado em +1
							}
						}
						if(c==14){		//Se o contador for igual a 14, que � o tamanho da frase "N�o Cadastrado", o programa ir� verificar outra escola
							continue;
						}
						else{										//Caso contr�rio, ser� mostrado o nome da escola, o nome do respons�vel, a nota de cada jurado para cada quesito e a nota final de cada quesito
							printf("\n\n\n______________________________________________________\n\n\n");
							printf("\n\nNome da escola: %s", esc[e].nomeEsc);
							printf("\n\nNome do respons�vel: %s", esc[e].nomeResp);
							printf("\n\n\t\tNotas: ");
							for(q=0;q<13;q++){				//O programa vai percorrer o vetor dos quesitos
								printf("\n\nQuesito avaliado: %s\n", esc[e].ques[q].nomeQues);
								somaQues=0;
								for(n=0;n<5;n++){			//O programa vai percorrer o vetor das notas
									printf("\n\tNota do jurado %d: %.1f", n+1, esc[e].ques[q].notasJur[n]);
								}
								esc[e].ques[q].notaFQues = media(esc[e].ques[q].notasJur);
								somaGeral = somaGeral+esc[e].ques[q].notaFQues;			//A nota final do quesito � a soma total menos a maior e a menor nota
								printf("\n\nNota final no Quesito: %.1f", esc[e].ques[q].notaFQues);
							}
							esc[e].mediaGeral = somaGeral/13;
							printf("\n\n\tNota final da Escola: %.1f", esc[e].mediaGeral);
						}
					}
				}
				//O usu�rio poder� utilizar outra fun��o do menu que desejar
				printf("\n\nDigite a opera��o que deseja executar: ");
				scanf("%d", &opcao);
				break;
			case 6:				//case 6 = mostrar a escola campe� e a vice-campe�
				printf("\n\n\t\tVOC� ESCOLHEU A OPERA��O DE MOSTRAR A ESCOLA CAMPE� E VICE-CAMPE�");
				if(escCad!=10){			//Se escCad for diferente de 10, isso significa que nem todas as escolas foram cadastradas, logo, n�o d� pra saber as escolas campe�s e vice-campe�s
					printf("\n\n\tNem todas as escolas foram cadastradas ainda!");
					printf("\n\nPor favor, escolha outra op��o: ");
					scanf("%d", &opcao);
					break;
				}
				else{					//Se todas as escolas foram cadastradas, ser� feita a verifica��o
					for(e=0;e<10;e++){			//O programa vai percorrer o vetor das escolas
						somaGeral=0;
						for(q=0;q<13;q++){			//O programa vai percorrer o vetor dos quesitos
							somaQues=0;
							esc[e].ques[q].notaFQues = media(esc[e].ques[q].notasJur);
							somaGeral = somaGeral + esc[e].ques[q].notaFQues;
						}
						//Faz-se o c�lculo da m�dia geral da escola "e" dividindo a soma geral dos quesitos por 13 (n�mero de quesitos)
						esc[e].mediaGeral = somaGeral/13;
					}
					//Calculando todas as notas, para as respectivas escolas, ser� feito a compara��o das m�dias gerais
					for(e=0;e<10;e++){						//Percorrer� o vetor das escolas, analisando e classificando as notas
						if(e==0){							//Se for a primeira escola, ela ter� automaticamente a melhor dentre as m�dias, para compara��o com as demais
							notaC = esc[e].mediaGeral;
							iC = e;
						}
						else{
							if(esc[e].mediaGeral>notaC){	//Se a m�dia da escola "e" for maior que a maior nota anterior, a m�dia da escola "e" passar� a ser a maior nota
								notaC = esc[e].mediaGeral;
								iC = e;
							}
						}
					}
					//Ap�s definir a escola campe�, ser� definida a escola vice-campe�
					fst=0;
					for(e=0;e<10;e++){
						if(e==iC){					//Se o �ndice da escola "e", for igual ao �ndice da escola campe�, o programa ir� pular a verifica��o da escola, uma vez que ela j� � a campe�
							continue;
						}
						else{
							if((fst==0)&&(esc[e].mediaGeral<notaC)){
								notaVC = esc[e].mediaGeral;
								iVC = e;
								fst++;
							}
							else{
								if((esc[e].mediaGeral>notaVC)&&(esc[e].mediaGeral<notaC)){		//Se a nota analisada for maior que a nota da atual vice-campe� e menor do que a nota campe�, a nota analisada passar� a ser a vice-campe�
									notaVC = esc[e].mediaGeral;
									iVC = e;
								}
							}
						}
					}
					//Ser� impresso na tela as escolas campe� e vice-campe�
					printf("\n\nA escola campe� foi %s com %.1f pontos na m�dia geral", esc[iC].nomeEsc, esc[iC].mediaGeral);
					printf("\n\nA escola vice-campe� foi %s com %.1f pontos na m�dia geral", esc[iVC].nomeEsc, esc[iVC].mediaGeral);
				}
				//O usu�rio poder� ent�o escolher outra op��o do menu
				printf("\n\nDigite a opera��o que deseja executar: ");
				scanf("%d", &opcao);
				break;
			case 7:				//case 7 = mostrar as duas escolas rebaixadas
				printf("\n\n\t\tVOC� ESCOLHEU A OPERA��O DE MOSTRAR AS DUAS ESCOLAS REBAIXADAS");
				if(escCad!=10){
					printf("\n\n\tNem todas as escolas foram cadastradas ainda!");
					printf("\n\nPor favor, escolha outra op��o: ");
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
						//Faz-se o c�lculo da m�dia geral da escola "e" dividindo a soma geral dos quesitos por 13 (n�mero de quesitos)
						esc[e].mediaGeral = somaGeral/13;
					}
					//Calculando todas as notas, para as respectivas escolas, ser� feito a compara��o das m�dias gerais
					for(e=0;e<10;e++){					//Percorrer� o vetor das escolas, analisando e classificando as notas
						if(e==0){						//Se for a primeira escola, sua nota ser� automaticamente a pior, para compara��o com as demais
							notaReb1=esc[e].mediaGeral;
							iReb1 = e;
						}
						else{
							if(esc[e].mediaGeral<notaReb1){			//Se a m�dia da escola "e" for menor que a nota de rebaixamento, a nota de rebaixamento passar� a ser a m�dia da escola "e"
								notaReb1 = esc[e].mediaGeral;
								iReb1 = e;
							}
						}
					}
					//Ap�s definir a escola rebaixada com menor m�dia, ser� definida a escola rebaixada com a segunda menor m�dia
					fst=0;
					for(e=0;e<10;e++){
						if(e==iReb1){		//Se o �ndice da escola "e" for igual ao da escola rebaixada com a pior m�dia, o programa ir� pular a verifica��o dessa escola
							continue;
						}
						else{
							if((fst==0)&&(esc[e].mediaGeral>notaReb1)){
								notaReb2 = esc[e].mediaGeral;
								iReb2 = e;
								fst++;
							}
							else{
								if((esc[e].mediaGeral<notaReb2)&&(esc[e].mediaGeral>notaReb1)){			//Se a m�dia da escola "e" for menor que a segunda nota de rebaixamento e maior que a primeira nota de rebaixamento, a m�dia da escola "e" passar� a ser a segunda nota de rebaixamento
									notaReb2 = esc[e].mediaGeral;
									iReb2 = e;
								}
							}
						}
					}
					//Ser� impresso na tela as escolas rebaixadas com a menor nota e com a segunda menor nota, respectivamente
					printf("\n\nA escola rebaixada com a menor nota foi %s com %.1f pontos na m�dia geral", esc[iReb1].nomeEsc, esc[iReb1].mediaGeral);
					printf("\n\nA escola rebaixada com a segunda menor nota foi %s com %.1f pontos na m�dia geral", esc[iReb2].nomeEsc, esc[iReb2].mediaGeral);
				}
				//O usu�rio poder� ent�o escolher outra op��o do menu
				printf("\n\nDigite a opera��o que deseja executar: ");
				scanf("%d", &opcao);
				break;
			default:			//default = reinserir o valor da op��o, j� que a opera��o selecionada n�o existe
				printf("\n\nA opera��o desejada n�o existe ou n�o foi implementada ainda. Tente novamente.\n");
				printf("\n\n\tDigite a opera��o que deseja executar: ");
				scanf("%d", &opcao);
				break;
		}
	}
	printf("\n\n\tObrigado pela visita! Volte sempre.\n\n");
	return 0;
}
