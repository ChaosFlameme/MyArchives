#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 9

int input_line, input_colone, input_corrige, input_menu, knockout, check, chancess;

clock_t ZIO, GEIZ;
double RiderTime;



void Print_sudoku(int a[N][N])
{
	printf("Votre sudoku est:\n");
	for (int i = 0; i < 9; i++)
	{
		printf("|");
		for (int n = 0; n < 9; n++)
		{
			printf("%d ", a[i][n]);
			if ((n + 3) % 3 == 2)printf("\b|");
		}
		printf("\n");
		if ((i + 3) % 3 == 2)printf("-------------------\n");
	}
	return;
}

int Creation(int a[N][N])
{
	for (int i = 0; i < 9; i++)
	{
		for (int n = 0; n < 9; n++)
		{
		Input_valeur:
			printf("Ligne:%d Colone:%d :(Saisir 999 pour quitter la creation.)\n", i + 1, n + 1);
			scanf("%d", &a[i][n]);
			if (a[i][n] > 9 || a[i][n] < 0)
			{
				if (a[i][n] == 999)
				{
					a[i][n] = 0;
					return 0;
				}
				printf("C'est nul.\n\n");
				getchar();
				goto Input_valeur;
			}
		}
	}
	return a[N][N];
}

int Corrige(int a[N][N])
{
CORRIGE_LINE://Get the line which user want change
	printf("Saisir le ligne:(0 pour quitter)\n");
	scanf("%d", &input_line);
	if (input_line > 9 || input_line < 0)
	{
		printf("C'est nul.\n\n");
		getchar();
		goto CORRIGE_LINE;
	}
	if (input_line == 0) return 0;

CORRIGE_COLONE://Get the row which user want change
	printf("Saisir le colonne:(0 pour quitter)\n");
	scanf("%d", &input_colone);
	if (input_colone > 9 || input_colone < 0)
	{
		printf("C'est nul.\n\n");
		getchar();
		goto CORRIGE_COLONE;
	}
	if (input_colone == 0) return 0;

	printf("Le nombre de ligne:%d colonne:%d est %d. ", input_line, input_colone, a[input_line - 1][input_colone - 1]);
	do
	{
		printf("Saisir le nombre que vous voullez changer.\n");
		scanf("%d", &input_corrige);
	} while (input_corrige > 9 || input_corrige < 0);
	a[input_line - 1][input_colone - 1] = input_corrige;
	printf("Now the number of line:%d row:%d is %d.\n", input_line, input_colone, a[input_line - 1][input_colone - 1]);
	return a[N][N];
}

int JUDD(int a[N][N])
{
	int knockout = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int n = 0; n < 9; n++)
		{
			//Judge for 9*9
			if (a[i][n] != 0)
			{
				for (int nline = 0; nline <= 2; nline++)
				{
					for (int ncolone = 0; ncolone <= 2; ncolone++)
					{
						//Remove the same!
						int ssss = i + nline - (i + 3) % 3;
						int zzzz = n + ncolone - (n + 3) % 3;
						if (i == ssss && n == zzzz)continue;
						if (a[ssss][zzzz] == 0)continue;
						if (a[i][n] - a[ssss][zzzz] == 0)
						{
							knockout = 1;
							goto JUDGE_JUDGE_JUGEMENT;
						}
					}
				}
				for (int c = 0; c < 9; c++)
				{
					//Judge line
					if (a[i][n] - a[i][c] == 0 && n != c)
					{
						knockout = 1;
						goto JUDGE_JUDGE_JUGEMENT;
					}
					for (int d = 0; d < 9; d++)
					{
						//Judge row
						if (a[i][n] - a[d][n] == 0 && i != d)
						{
							knockout = 1;
							goto JUDGE_JUDGE_JUGEMENT;
						}
					}
				}
			}
		}
	}
JUDGE_JUDGE_JUGEMENT:
	if (knockout == 1)printf("I don't think it's a sudoku.\n");
	return knockout;
}

int *GetSet(int a[N][N][10], int number, int i, int j) //For regristering the numbers into tbody, prepare for checking the number
{
	for (int k = 0; k < 9; k++)//When tbody[][][] = 1, it means the number is not available in the line and the row.
	{
		a[i][k][number]++;
		a[k][j][number]++;
	}
	for (int n = 0; n < 3; n++)//and the 9*9.
	{
		for (int m = 0; m < 3; m++)
		{
			a[i / 3 * 3 + n][j / 3 * 3 + m][number]++;
		}
	}
	return a;
}
int *Resetnum(int a[N][N][10], int number, int i, int j)
{
	for (int k = 0; k < 9; k++) //Return the check
	{
		a[i][k][number]--;
		a[k][j][number]--;
	}
	for (int n = 0; n < 3; n++)
	{
		for (int m = 0; m < 3; m++)
		{
			a[i / 3 * 3 + n][j / 3 * 3 + m][number]--;
		}
	}
	return a;
}


void Excution(int step, int a[N][N], int g[N][N][10]) //Voila, it's time to solve the sudoku
{

	if (step == 0)//Finish
	{
		if (chancess == 1)
		{
			int vides = -1;
			int yy, qq;
			while (vides < 0 || vides>81) {
				printf("Combien de carees vous voullez les faire vides?\n");
				scanf("%d*c", &vides);
				if (vides < 0 || vides>81) {
					printf("C'est nul.\n");
					getchar();
				}
			}
			for (vides; vides > 0; vides--)
			{
				chancess = 1;
				while (chancess == 1)
				{
					yy = rand() % 9;
					qq = rand() % 9;
					if (a[yy][qq] != 0) {
						a[yy][qq] = 0;
						chancess = 0;
					}
				}
			}
			Print_sudoku(a);
			FILE * Question;		//Here for creat the text
			Question = fopen("Question.txt", "w+");
			fprintf(Question, "A vous jouer:\n");
			for (int i = 0; i < 9; i++)
			{
				fprintf(Question, "|");
				for (int n = 0; n < 9; n++)
				{
					fprintf(Question, "%d ", a[i][n]);
					if ((n + 3) % 3 == 2)fprintf(Question, "|");
				}
				fprintf(Question, "\n");
				if ((i + 3) % 3 == 2)fprintf(Question, "-------------------\n");
			}
			fclose(Question);
			printf("Un fichier de votre sudoku a ¨¦t¨¦ cr¨¦e dans votre dossier.\n");
			exit(0);
		}
		else {
			Print_sudoku(a);
			GEIZ = clock();
			RiderTime = GEIZ - ZIO;
			printf("Time cost:%.0lfms\n", RiderTime);
			FILE * Result;		//Here for creat the text
			Result = fopen("Result.txt", "w+");
			fprintf(Result, "Votre sudoku est:\n");
			for (int i = 0; i < 9; i++)
			{
				fprintf(Result, "|");
				for (int n = 0; n < 9; n++)
				{
					fprintf(Result, "%d ", a[i][n]);
					if ((n + 3) % 3 == 2)fprintf(Result, "|");
				}
				fprintf(Result, "\n");
				if ((i + 3) % 3 == 2)fprintf(Result, "-------------------\n");
			}
			fprintf(Result, "Time cost:%.0lfms\n", RiderTime);
			printf("Un fichier de votre sudoku a ¨¦t¨¦ cr¨¦e dans votre dossier.\n");
			fclose(Result);
			exit(0);
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (a[i][j] == 0) //Check if it's blank and need to be solved
			{
				for (int number = 1; number < 10; number++)
				{
					if (g[i][j][number] == 0) //When the value is available, make a registration.
					{
						GetSet(g, number, i, j);//It can check following numbers in blanks whether is available or not
						a[i][j] = number;
						Excution(step - 1, a, g);//Here's the loop of the solution, until the times is 0
						a[i][j] = 0;
						Resetnum(g, number, i, j);
					}
				}
				return;
			}
		}
	}
}

int main(int argc, const char * argv[])
{
	do
	{
		int step;
		int a[N][N];
		int judge[N][N][10];
	MEOO_MEOW_MENU:
		step = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				a[i][j] = 0;
				for (int k = 1; k < 10; k++) {
					judge[i][j][k] = 0;//Prepare zero for all
				}
			}
		}
		printf("Choisir ce que vous voullez.\n1.Solve a sudoku.\n2.La guide\n3.Generate a sudoku_BETA\n4.Quit\n");
		scanf("%d", &input_menu);
		switch (input_menu)
		{
		case 1://Solution
		{
			do {
			MADE_IN_HEAVEN:
				printf("Vous voullez saisir un sodku: \n1.un par un\n2.remplir les trous\n3.THX, but I'm out.\n");
				scanf("%d", &input_menu);
				switch (input_menu)
				{
				case 1:
					printf("Veuillez saisir un sudoku.\n");
					Creation(a);
					break;
				case 2:
					break;
				case 3:
					goto MEOO_MEOW_MENU;
				default:
					printf("C'est nul.\n\n");
					getchar();
					goto MADE_IN_HEAVEN;
				}
			MAKESURE:
				Print_sudoku(a);
				printf("Vous voullez le refaire ou modifier?\n1.Refaire\n2.Modifier\n3.C'est bon.\n4.Je quitte.\n");
				scanf("%d", &input_menu);
				switch (input_menu)
				{
				case 1:
					break;
				case 2:
					Corrige(a);
					goto MAKESURE;
				case 3:
					break;
				case 4:
					goto MEOO_MEOW_MENU;
				default:
					getchar();
					goto MAKESURE;
				}
			} while (input_menu != 3);//END of giving the sudoku			
			knockout = JUDD(a);
			if (knockout == 1)goto MADE_IN_HEAVEN;
			else printf("Veuillez patienter.\n");
			ZIO = clock();
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (a[i][j] == 0)step++;//For prepare the times of solution					
					else GetSet(judge, a[i][j], i, j);//Prepare for the juddgement.				
				}
			}
			Excution(step, a, judge);
		}
		case 2://RULES
		{
			printf("Pour resoudre un sudoku:\n  JUSTEMENT SUIVRE LES INFO DANS LE PROGRAM.\n\n");
			printf("For the objective of sudoku:\n  The objective is to fill a 9¡Á9 grid with digits so that each column, each row, and each of the nine 3¡Á3 subgrids that compose the grid conjudgein all of the digits from 1 to 9.  Via.Wikipedia \n\n");
			break;
		}
		case 3://Generation
		{
			srand((unsigned)time(NULL));
			a[0][0] = rand() % 9 + 1;//Randomize one value
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (a[i][j] == 0)step++;//For prepare the times of solution					
					else GetSet(judge, a[i][j], i, j);//Prepare for the juddgement.				
				}
			}
			chancess = 1;
			Excution(step, a, judge);
		}
		case 4://EXIT
		{
			printf("See you next time~\n");
			exit(0);
		}
		default:
			printf("C'est nul.\n\n");
			getchar();
		}
	} while (input_menu != 4);
}
