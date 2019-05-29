#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


//Programa realizado para a disciplina de ICC por Armindo Lopes, nº70054, CTESP Desenvolvimento de Produtos Multimédia
//O objetivo do programa é permitir ao utilizador introduzir e armazenar dados e notas dos alunos
//Programa escrito e compilado em Visual Studio 2017, linguagem C


//Estrutura das variáveis que atribuem dados aos alunos
typedef struct dados{
	char Nome[30];
	char nAluno[10];
	char Curso[15];
	float Nota;
}aluno;


//Protótipos de funções
int procurar(aluno al[], char id[], int nItens);
void limpar(aluno al[], int nItensApagar);
void mostracabecalho();

//Menu de opções disponíveis
void mostramenu() {
	printf("Programa realizado para a disciplina de ICC por Armindo Lopes, nº70054\n\n\n");
	printf(" Menu \n");
	printf(" ================================================\n");
	printf(" 1.Adicionar aluno e respetivos dados\n");
	printf(" 2.Eliminar aluno e respetivos dados\n");
	printf(" 3.Atualizar dados do aluno (nome, curso e nota)\n");
	printf(" 4.Tabela de alunos\n");
	printf(" 5.Procurar aluno através do número\n");
	printf(" ================================================\n\n");
}

//Novo registo (tecla 1)
void adiciona_aluno(aluno al[], int *nItens) {

	do {

		printf("Introduza o número do aluno:\n");
		scanf_s("%s%*[^\n]%*1[\n]", &al[*nItens].nAluno, 9);

		//Verifica se o número já existe
		if (procurar(al, al[*nItens].nAluno, *nItens) != -1)
			printf("Este número já existe.\n");
		else {
			printf("Introduza o nome do aluno:\n");
			scanf_s("%s%*[^\n]%*1[\n]", &al[*nItens].Nome, 29);

			printf("Introduza o curso:\n");
			scanf_s("%s%*[^\n]%*1[\n]", &al[*nItens].Curso, 14);

			printf("Introduza a nota do aluno:\n");
			scanf_s("%f%*[^\n]%*1[\n]", &al[*nItens].Nota);

			++(*nItens);

			break;
		}
	} while (1);


}

//Encontrar aluno no registo de dados através do número de aluno (tecla 5)
int procurar(aluno al[], char id[], int nItens) {
	int encontrado = -1, i;

	for (i = 0; i < nItens && encontrado == -1; i++){

		if (strcmp(al[i].nAluno, id) == 0) encontrado = i;

		else encontrado = -1;
	}

	return encontrado;
}



//Ver todos os dados e mostrar tabela (tecla 4)
void vertudo(aluno al[], int nItens) {
	int i = 0;
	mostracabecalho();

	while (i<nItens) {
		if (al[i].nAluno != "") {
			printf("%-10s", al[i].nAluno);
			printf("%-30s", al[i].Nome);
			printf("%-15s", al[i].Curso);
			printf("%-4f", al[i].Nota);
			printf("\n");
		}
		i = i + 1;
	}
}

void mostracabecalho() {
	
	printf("Nº        Nome                          Curso          Nota\n");
	printf("===========================================================\n");
	
}


//Apagar dados através da introdução do número de aluno (tecla 2)
void apagar_aluno(aluno al[], int *nItens) {
	char id[10];
	int index, i;
	if (*nItens > 0)
	{
		printf("Introduza o número do aluno.\n");
		scanf("%s", id);
		index = procurar(al, id, *nItens);

		if ((index != -1) && (*nItens != 0))
		{
			if (index == (*nItens - 1)) //Apagar o último registo
			{

				limpar(al, index);
				--(*nItens);

				printf("Os dados foram eliminados.\n");
			}
			else //Apagar o primeiro registo ou do meio
			{
				for (i = index; i < *nItens - 1; i++)
				{
					al[i] = al[i + 1];
					limpar(al, *nItens);
					--(*nItens);
				}
			}
		}
		else printf("O registo não existe. Tente outra vez.\n");
	}
	else printf("Não há dados para eliminar.\n");
}

//Limpar dados eliminados
void limpar(aluno al[], int index)
{
	strcpy(al[index].Nome, "");
	strcpy(al[index].nAluno, "");
	strcpy(al[index].Curso, "");
	al[index].Nota = 0;
}


//Atualizar dados; permite modificar o nome, curso e nota (tecla 3) através do número do aluno
void actualizar_aluno(aluno al[], int nItens) {
	char id[10];
	int id_coluna;
	printf("Introduza o número do aluno:\n");
	scanf("%s", &id);
	printf("Qual é o campo que pretende alterar(1 = Nome, 2 = Curso, 3 = Nota)?\n");
	scanf("%d", &id_coluna);

	int index = procurar(al, id, nItens);

	if (index != -1)
	{
		if (id_coluna == 1)
		{
			printf("Introduza o nome do aluno:\n");
			scanf_s("%s%*[^\n]%*1[\n]", &al[index].Nome, 29);
		}

		else if (id_coluna == 2)
		{
			printf("Introduza o curso:\n");
			scanf_s("%s%*[^\n]%*1[\n]", &al[index].Curso, 14);
		}
		else if (id_coluna == 3)
		{
			printf("Introduza a nota do aluno:\n");
			scanf_s("%f%*[^\n]%*1[\n]", &al[index].Nota);
		}
		else printf("Coluna inválida.");

	}
	else printf("Os dados não existem, tente outra vez.\n");

}

//Encontrar registo de aluno (tecla 5) através do número
void encontra_aluno(aluno al[], int nItens)
{
	char id[10];
	printf("Introduza o número de aluno.\n");
	scanf("%s", &id);

	int index = procurar(al, id, nItens);
	if (index != -1)
	{ //Tabela com registo de dados do aluno procurado
		mostracabecalho();
		printf("%-10s", al[index].nAluno);
		printf("%-30s", al[index].Nome);
		printf("%-15s", al[index].Curso);
		printf("%-4f", al[index].Nota);

		printf("\n");

	}
	else printf("Dados não existem.\n"); // Na eventualidade do utilizador não ter introduzido dados
}


//Função principal

int main(int argc, char *argv[])
{
	//Comando para permitir executar o programa em Visual Studio com os carateres de português
	setlocale(LC_ALL, "Portuguese");

	
	//Alocação de memória para a estrutura, através de apontador
	typedef aluno *al2;

	//Limite de 50 alunos
	al2 al[50];

	for (int j = 0; j < 49; j++)
		al[j] = (al2)malloc(sizeof(aluno));


	//Número de alunos no vector
	int nItens = 0;


	char escolha;
	char ch;


	do
	{
		system("cls");

		//Mostrar menu de opções disponíveis
		mostramenu();

		printf("Introduza a sua escolha de 1 a 5 ou prima 's' para sair.\n");
		escolha = tolower(getch());


		//Switch para operar as opções do menu e permitir a interação com o utilizador
		switch (escolha) {
		case '1':adiciona_aluno(al, &nItens); break; //Utiliza a opção que permite adicionar o aluno e respetivos dados
		case '2':apagar_aluno(al, &nItens); break; //Utiliza a opção de eliminar o aluno através da introdução do seu número
		case '3':actualizar_aluno(al, nItens); break; //Utiliza a opção de atualizar dados do aluno (nome, curso e nota)
		case '4':vertudo(al, nItens); break; //Utiliza a opção de ver todos os alunos num cabeçalho/tabela
		case '5':encontra_aluno(al, nItens); break; //Utiliza a opção de encontrar o aluno pelo número
		case 's':
			for (int j = 0; j < 49; j++)
				free(al[j]);
			return EXIT_SUCCESS; //Saí do programa caso o utilizador prima a tecla 's'
		default:
			printf("Opção inválida.\n"); //Caso o utilizador prima outra tecla esta mensagem aparecerá
		}

		//Após o utilizador introduzir dados terá de premir qualquer tecla para proceder para o próximo passo
		printf("Prima qualquer tecla para continuar.\n");
		ch = getch();

		//Define a tecla 's' para permitir sair do programa 
	} while (escolha != 's'); 

	for (int j = 0; j < 49; j++)
		free(al[j]);

	
	return EXIT_SUCCESS;
}