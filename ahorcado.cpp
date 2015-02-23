#include <iostream>
#include <cctype>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
char* convert(char*);
char** draw (char**);
void printm(char**);
int Categoria();
char* ocultarPalabra(int);
char* revealLetter(char*,char*,char*);
char** mistakes(char**,int);
bool LetterAppears(char*, char*);
int CompareWords(char*,char*);
bool verificar(char*);
void stickman();

int main(int argc,char* argv[]){
	srand(time(0));
	char resp [80];
	int won=0;
	int lost=0;
	do{
		char** words=new char*[90];
		char* palabra;
		int numPalabras;
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<"Bienvenido a Hangman!"<<endl;
		stickman();
		cout<<endl;
		int categoria=Categoria();
		switch(categoria){
			case 1:{
				numPalabras=43;
				char cadena[50];
				ifstream myfile ("carros.txt");
				if (myfile.is_open()){
					for (int i = 0; i < 44; ++i)
					{
						myfile.getline(cadena,sizeof(cadena));
						words[i]=new char[strlen(cadena)+1];
						strcpy(words[i],cadena);
					}
					myfile.close();
				}else{
					cout<<"Unable to open file"<<endl;
				}
				/////////////seleccionar palabra random/////////
				int random=rand()%numPalabras;
				palabra=new char[strlen(words[random])+1];
				strcpy(palabra,words[random]);
				break;
			}//fin case 1
			case 2:{
				numPalabras=82;
				char cadena[50];
				ifstream myfile ("paises.txt");
				if (myfile.is_open()){
					for (int i = 0; i < 82; ++i)
					{
						myfile.getline(cadena,sizeof(cadena));
						words[i]=new char[strlen(cadena)+1];
						strcpy(words[i],cadena);
					}
					myfile.close();
				}else{
					cout<<"Unable to open file"<<endl;
				}
				/////////////seleccionar palabra random/////////
				int random=rand()%numPalabras;
				palabra=new char[strlen(words[random])+1];
				strcpy(palabra,words[random]);
				break;
			}//fin case 2 
			case 3:{
				numPalabras=30;
				char cadena[50];
				ifstream myfile ("frutas.txt");
				if (myfile.is_open()){
					for (int i = 0; i < 30; ++i)
					{
						myfile.getline(cadena,sizeof(cadena));
						words[i]=new char[strlen(cadena)+1];
						strcpy(words[i],cadena);
					}
					myfile.close();
				}else{
					cout<<"Unable to open file"<<endl;
				}
				/////////////seleccionar palabra random/////////
				int random=rand()%numPalabras;
				palabra=new char[strlen(words[random])+1];
				strcpy(palabra,words[random]);
				break;
			}//fin case 3
			case 4:{
				numPalabras=56;
				char cadena[50];
				ifstream myfile ("programacion.txt");
				if (myfile.is_open()){
					for (int i = 0; i < 56; ++i)
					{
						myfile.getline(cadena,sizeof(cadena));
						words[i]=new char[strlen(cadena)+1];
						strcpy(words[i],cadena);
					}
					myfile.close();
				}else{
					cout<<"Unable to open file"<<endl;
				}
				/////////////seleccionar palabra random/////////
				int random=rand()%numPalabras;
				palabra=new char[strlen(words[random])+1];
				strcpy(palabra,words[random]);
				break;
			}//fin case 4 
		}//fin switch categoria
		char** hangman= new char*[6];
		for (int i = 0; i < 6; i++){
			hangman[i]= new char[6];
		}//fin for 
		hangman=draw(hangman);
		int mistake=0;
		char aciertos [20]=" ";
		char** errores = new char*[6];
		bool win=false;
		char* hiddenWord=new char[strlen(palabra)+1];
		hiddenWord=ocultarPalabra(strlen(palabra));
		bool completed=false;
		do{
			bool right;
			bool wrong;
			bool appears=false;
			char* guess= new char[80];
			cout<<"//////////////////////////////////////////////////////////////////////"<<endl;
			cout<<"Aciertos: "<<aciertos<<endl;
			cout<<"Errores: ";
			for (int numErrores = 0; numErrores < mistake; numErrores++)
			{
				cout<<errores[numErrores];
				cout<<" ";
			}			
			cout<<endl;
			printm(hangman);
			cout<<hiddenWord<<endl;
			cout<<endl;
			do{
				right=false;
				wrong=false;
				cout<<"Ingrese una letra o la palabra que desea adivinar: "<<endl;
				cin>>guess;
				guess=convert(guess);
				if (strlen(guess)==1){
					for (int rights = 0; rights < strlen(aciertos); rights++)
					{
						if(aciertos[rights]==guess[0]){
							cout<<"Ya ingreso esa letra o palabra."<<endl;
							cout<<endl;
							right=true;
							break;
						}else{
							right=false;
						}
					}//fin for rights
					for (int numErrores = 0; numErrores < mistake; numErrores++)
					{
						int IGUAL=CompareWords(errores[numErrores],guess);
						if (IGUAL==0){
							cout<<"Ya ingreso esa letra o palabra."<<endl;
							cout<<endl;
							wrong=true;
							break;
						}else{
							wrong=false;
						}
					}//fin for wrongs
				}else{
					for (int numErrores = 0; numErrores < mistake; numErrores++)
					{
						int IGUAL=CompareWords(errores[numErrores],guess);
						if (IGUAL==0){
							cout<<"Ya ingreso esa letra o palabra."<<endl;
							cout<<endl;
							wrong=true;
							break;
						}else{
							wrong=false;
						}
					}//fin for wrongs
				}	
			}while(right==true||wrong==true);
			if (strlen(guess)==1){
				appears=LetterAppears(palabra,guess);
				if (appears==true){
					hiddenWord=revealLetter(hiddenWord,palabra,guess);
					strcat(aciertos,guess);
					strcat(aciertos," ");
					completed=verificar(hiddenWord);
					if (completed==true){
						printm(hangman);
						cout<<hiddenWord<<endl;
						win=true;
						break;
					}
					cout<<endl;
				}else{
					errores[mistake]=new char[strlen(guess)+1];
					strcpy(errores[mistake],guess);
					mistake++;
					hangman=mistakes(hangman,mistake);
					cout<<endl;
					}
			}else{
				int igual=CompareWords(palabra,guess);
				if(igual==0){
					win=true;
					break;
				}else{
					errores[mistake]=new char[strlen(guess)+1];
					strcpy(errores[mistake],guess);
					mistake++;
					hangman=mistakes(hangman,mistake);
					cout<<endl;
				}
			}//fin if
			if (mistake==6){
				break;
			}
		}while(win==false||mistake<=6);
		if (win==true){
			cout<<"//////////////////////////////////////////////////////////////////////"<<endl;
			cout<<"Aciertos: "<<aciertos<<endl;
			cout<<"Errores: ";
			for (int numErrores = 0; numErrores < mistake; numErrores++)
			{
				cout<<errores[numErrores];
				cout<<" ";
			}			
			cout<<endl;
			won++;
			cout<<endl;
			stickman();
			cout<<"Usted ha ganado!"<<endl;
			cout<<"La palabra era: "<<palabra<<endl;
		}else{
			cout<<"//////////////////////////////////////////////////////////////////////"<<endl;
			cout<<"Aciertos: "<<aciertos<<endl;
			cout<<"Errores: ";
			for (int numErrores = 0; numErrores < mistake; numErrores++)
			{
				cout<<errores[numErrores];
				cout<<" ";
			}			
			cout<<endl;
			lost++;
			printm(hangman);
			cout<<hiddenWord<<endl;
			cout<<"Usted ha Perdido"<<endl;
			cout<<"La palabra era: "<<palabra<<endl;
		}
		bool salida;
		do{
			salida=false;
			cout<<"Desea volver a jugar? (S/N):"<<endl;
			cin>>resp;
			if (strlen(resp)>1){
				cout<<"Opcion no valida"<<endl;
				salida=true;
			}else if(!(resp[0]=='s'||resp[0]=='S'||resp[0]=='n'||resp[0]=='N')){
				cout<<"Opcion no valida"<<endl;
				salida=true;
			} 
		}while(salida==true);

	}while (resp[0]=='s'||resp[0]=='S');
	cout<<"Usted gano "<< won<<" veces y perdio "<< lost<<" veces."<<endl;
	cout<<endl;
	return 0;
}//fin main

char* convert(char* word){
	for (int letra = 0; letra < strlen(word); letra++)
	{
		word[letra]=tolower(word[letra]);
	}
	return word;
}

char** draw(char** hangman){
	char** drawing= new char*[6];
	for (int filas = 0; filas < 6; filas++)
	{
		drawing[filas]= new char[6];
	}
	drawing=hangman;
	for (int filas = 0; filas < 6; filas++)
	{
		for (int columnas = 0; columnas < 6; columnas++)
		{
			drawing[filas][columnas]=' ';
		}
	}
	for (int filas = 1; filas < 6; filas++){
		drawing[filas][0]='|';
		if (filas==1){
			drawing[filas][3]='|';
		}
	}

	for (int columnas = 0; columnas < 4; columnas++)
	{
		drawing[0][columnas]='-';
	}
	return drawing;
}
void printm(char** hangman){
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout<<hangman[i][j];
		}
		cout<<endl;
	}
}
char** mistakes(char** hangman, int errores){
	char** drawing= new char*[6];
	for (int i = 0; i < 6; i++)
	{
		drawing[i]= new char[6];
	}
	drawing=hangman;

	if (errores==1){
		drawing[2][3]='O';
	}else if (errores==2){
		drawing[3][3]='|';
	}else if (errores==3){
		drawing[2][2]=92;
	}else if (errores==4){
		drawing[2][4]='/';
	}else if (errores==5){
		drawing[4][2]='/';
	}else if (errores==6){
		drawing[4][4]=92;
	}
	return drawing;
}
int Categoria(){
	cout<<"CATEGORIAS:"<<endl;
	cout<<"1.Marcas de automoviles."<<endl;
	cout<<"2.Nombres de paises."<<endl;
	cout<<"3.Nombres de Frutas."<<endl;
	cout<<"4.Palabras de programacion."<<endl;
	char categoria[100];
	cout<<endl;
	bool mayor;
	do{
		mayor=false;
		cout<<"Seleccione la categoria:";
		cin>>categoria;
		if (strlen(categoria)>1){
			cout<<"Opcion no valida!"<<endl;
			mayor=true;
		}else if (!(categoria[0]=='1'||categoria[0]=='2'||categoria[0]=='3'||categoria[0]=='4')){
			cout<<"Opcion no valida!"<<endl;
			mayor=true;
		}
	}while(mayor==true);
	int category;
	if (strlen(categoria)==1){
		switch (categoria[0]){
			case '1':{
				category=1;
				break;
			}
			case '2':{
				category=2;
				break;
			}
			case '3':{
				category=3;
				break;
			}
			case '4':{
				category=4;
				break;
			}
		}
	}
	return category;
}
char* ocultarPalabra(int size){
	char* hidden= new char[size+1];
	for (int i= 0; i < 6; i++)
	{	
		hidden[i]=' ';

	}
	for (int letra = 0; letra < size; letra++)
	{	
		hidden[letra]='_';

	}
	return hidden;
}

char* revealLetter(char* hidden, char* palabra, char* letter){
	char* reveal= new char[strlen(palabra)];
	reveal=hidden;
	for (int i = 0; i < strlen(palabra); i++)
	{
		if(palabra[i]==letter[0]){
			reveal[i]=letter[0];
		}
	}
	return reveal;
}

bool LetterAppears(char* palabra, char*letra){
	bool aparece=false;
	for (int i = 0; i < strlen(palabra); i++)
	{
		if (palabra[i]==letra[0]){
			aparece=true;
			break;
		}
	}
	return aparece;
}

int CompareWords(char*palabra,char*word){
	int igual;
	igual=strcmp(palabra,word);
	return igual;
}

bool verificar(char* hidden){
	bool appear=true;
	for (int i = 0; i < strlen(hidden); i++)
	{
		if (hidden[i]=='_'){
			appear=false;
			break;
		}
	}
	return appear;
}

void stickman(){
	char** stickman= new char*[3];
	for (int filas = 0; filas < 3; filas++)
	{
		stickman[filas]= new char[3];
	}
	for (int filas = 0; filas < 3; filas++)
	{
		for (int columnas = 0; columnas < 3; columnas++)
		{
			stickman[filas][columnas]=' ';
		}
	}
	stickman[0][1]='O';
	stickman[1][1]='|';
	stickman[2][2]=92;
	stickman[0][0]=92;
	stickman[0][2]='/';
	stickman[2][0]='/';

	for (int filas = 0; filas < 3; filas++)
	{
		for (int columnas = 0; columnas < 3; columnas++)
		{
			cout<<stickman[filas][columnas];
		}
		cout<<endl;
	}
}

