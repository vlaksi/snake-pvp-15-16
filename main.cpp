
//UPUSTVO-igra se sa komandama(w-gore,s-dole,a-levo,d-desno)


#include <iostream>
#include <windows.h> //za brzinu igre u ovom kodu
#include <conio.h>//zbog inputa,biblioteka da bi mogli da koristimo tastaturu za igru npr.
using namespace std;
bool gameOver, smrtPrveZmije, smrtDrugeZmije; // globalna promenljiva
const int width = 40;//dimenzije mape-sirina
const int height = 20;//dimenzije mape-visina
int x, y, u, c, fruitX, fruitY, score,score2;//promenljive,(x,y za zmiju,fruitX i fruitY za ono sto pokupi zmija) i imamo score ,brojac za postignut skor
int teloX[400], teloY[400], teloX2[400], teloY2[400];//maksimalna velicina za telo x,y
int nTelo, nTelo2;//duzina tela n
enum eDirection1 { STOP = 0, LEFT, RIGHT, UP, DOWN };//da ne bi morali da stiskamo stalno jednu te istu komandu,ovim omogucujemo da kad se npr nesto pokrenulo prema dole,ide prema dole dok se ne zaustavi nekom komandom ili pravilom
eDirection1 dir;//promenljiva dir
enum eDirection2 { STOP2 = 10, LEFT2, RIGHT2, UP2, DOWN2 };
eDirection2 dir2;
int zivot = 13;
int zivot2 = 13;
void Setup()
{
	gameOver = false;//krecemo od toga da nije gameover na pocetku
	smrtPrveZmije = false;
	smrtDrugeZmije = false;
	dir = STOP;// zmija se ne krece dok je mi ne pokrenemo na pocetku
	dir2 = STOP2;
	x = width / 2;//postavljamo zmiji pocetni polozaj,centar
	y = height / 2;
	u = width / 2;
	c = width / 3;
	fruitX = rand() % width;//postavljamo vockici pocetni polozaj,random
	fruitY = rand() % height;
	score = 0;//na pocetku je skor 0
}
void Draw()
{
	system("cls");//cisti ekran na pocetku
	for (int i = 0; i < width + 2; i++)//gornji deo okvira,+2 da bi lepo ispalo
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)//0 jer stampa levo
				cout << "#";
			if (i == c && j == u)
				cout << "0";
			else if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "*";
			else
			{
				bool stampa = false;
				for (int k = 0; k < nTelo; k++)
				{
					if (teloX[k] == j && teloY[k] == i)
					{
						cout << "o";
						stampa = true;
					}
				}
				/*if (!stampa)//ako nema stampe,prazan prostor pisi
				cout << " "; //prazan prostor izmedju levog i desnog okvira
				*/
				bool stampa2 = false;
				for (int z = 0; z < nTelo2; z++)
				{
					if (teloX2[z] == j && teloY2[z] == i)
					{
						cout << "o";
						stampa2 = true;
					}
				}
				if (!stampa && !stampa2)
					cout << " ";
				//ako su iste kordinate tela i jedne i druge da mogu da se poklope i da se promeni njihovo mesto i da pojede jedna drugu
				
				/*
				if (teloX == teloX2 && teloY == teloY2)
				{
					stampa = false;
					stampa2 = false;
				}
				*/
				/*bool stampa2 = false;
				for (int k = 0; k < nTelo2; k++)
				{
				if (teloX2[k] == j && teloY2[k] == i)
				}
				*/
			}
			if (j == width - 1)//kad dodje do kraja,oduzme jedan i to stampa desnu stranu okvira,da bi desni okvir pomerio na odgovarajuce mesto ide -1*u ovom slucaju samo*
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++)//donji deo okvira,+2,da bi se poklopilo
		cout << "#";
	cout << endl;
}
void Input()
{
	if (_kbhit())//ako se pritisne nesto na tastaturi
	{
		switch (_getch())//uvodimo da mozemo koristiti,a,b,w,s,za kretnju u igri
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case '4':
			dir2 = LEFT2;
			break;
		case '6':
			dir2 = RIGHT2;
			break;
		case '8':
			dir2 = UP2;
			break;
		case '5':
			dir2 = DOWN2;
			break;
		case'x'://ako pritisnemo x,igra se odma prekida,tj odma je gameOver
			gameOver = true;
			break;
		}
	}
}
void Logic0()
{
	int preX = teloX[0];//prethodna kordinata jednog dela tela zmije(x),znaci ono 'o' posle 'O'
	int preY = teloY[0];//isto za y
	int pre2X, pre2Y;
	teloX[0] = x;
	teloY[0] = y;
	for (int i = 1; i < nTelo; i++)//,princip dodavanja tela i=1 jer vec glava zmije zauzima nesto,tako da je ovo bas telo
	{
		pre2X = teloX[i];
		pre2Y = teloY[i];
		teloX[i] = preX;
		teloY[i] = preY;
		preX = pre2X;
		preY = pre2Y;
		//prev2X,prev2Y su kordinate novog tela zmijice,ono prvo ne postoji,zmijina glava je nulti deo u telu zmije,odnosno prvi,svi ostali delovi su 1,2,3,4...
		//u zavisnosti od duzine tela zmije
		//pre2X = teloX[i]; kordinate tela zmije i koliko ce se puta dodavati,
		//pre2Y = teloY[i];
		//teloX[i] = preX; odnosno ono mesto gde je zmijina glava bila sada ce se stvoriti jedan komadic zmijinog tela odnosno 'o',ovo je logika,a crtanje gore
		//teloY[i] = preY;
		//preX = pre2X; a telo zmije moze biti ko zna koliko,preX je onaj deo zmijice koji stalno ide uz glavu zmije, i uvek njenu prethodnu
		// poziciju zauzima,dok pre2X su svi ostali ustvari delovi zmije i oni prate i zauzimaju kordinate ovog preX
		//preY = pre2Y;
	}
	int preU = teloX2[0];
	int preC = teloY2[0];
	int pre2X2, pre2Y2;
	teloX2[0] = u;
	teloY2[0] = c;
	for (int p = 1; p < nTelo2; p++)
	{
		pre2X2 = teloX2[p];
		pre2Y2 = teloY2[p];
		teloX2[p] = preU;
		teloY2[p] = preC;
		preU = pre2X2;
		preC = pre2Y2;
	}
	switch (dir) //cista logika kretanja zmije
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;//-- jer je 0 gore skroz i ako idemo prema gore,a npr je zmija bila na kordinati y=7,da bi ona isla gore po kordinati y,y se mora smanjiti
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	switch (dir2) //cista logika kretanja zmije
	{
	case LEFT2:
		u--;
		break;
	case RIGHT2:
		u++;
		break;
	case UP2:
		c--;//-- jer je 0 gore skroz i ako idemo prema gore,a npr je zmija bila na kordinati y=7,da bi ona isla gore po kordinati y,y se mora smanjiti
		break;
	case DOWN2:
		c++;
		break;
	default:
		break;
	}
	switch (score)
	{
	case 100:
		score = score + 40;
		
		break;
	case 400:
		score = score + 60;
	
		break;
	case 1000:
		score = score + 80;
		
		break;
	case 2000:
		score = score + 120;
		
		break;
	}
	switch (score2)
	{
	case 100:
		score2 = score2 + 40;
		
		break;
	case 400:
		score2 = score2 + 60;
	
		break;
	case 1000:
		score2 = score2 + 80;
		
		break;
	case 2000:
		score2 = score2 + 120;
	
		break;
	}
	//if (x > width|| x < 0|| y > height || y < 0)
	//	gameOver = true;
	for (int i = 0; i < nTelo; i++)
		if (teloX[i] == x && teloY[i] == y)//ako se podudare kordinate glave i tela,gubi zivot zmija
		{
			zivot = zivot - 1;
		}
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;
	if (u >= width) u = 0; else if (u < 0) u = width - 1;
	if (c >= height) c = 0; else if (c < 0) c = height - 1;
	if (x == fruitX && y == fruitY)//ako je zmijina tacka jednaka tacki vockice,dodaje se skor +10 i stvara se nova radnom pozicija vockice
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTelo++;//ako su kordinate iste,povecava se telo zmije
	}
	if (u == fruitX && c == fruitY)
	{
		score2+= 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTelo2++;
	}
	
	if (x == u && y == c || x == (u - 1) && y == c ||x == u && y == (c - 1) || (x - 1) == u && (y - 1) == c  /*x == preU && y == preC || u == preX && c == preY || x == preU && y == preC || u == teloX[1] && c == teloY[1]|| x == teloX2[1] && y == teloY2[1]*/ )
		//omogucava da ako se poklope jedna i druga zmija da ih premesta na random poziciju na mapi
	{
		score=score-50;
		score2=score2-50;
		x = rand() % width;
		y = rand() % height;

		u = rand() % width;
		c = rand() % height;		
	}
	
	
	cout << "\n SKOR PRVE ZMIJE: " << score << endl;
	cout << " \n SKOR DRUGE ZMIJE: " << score2 << endl;
	
	
	
	
	
}




void Logic1()
{
	int preX = teloX[0];//prethodna kordinata jednog dela tela zmije(x),znaci ono 'o' posle 'O'
	int preY = teloY[0];//isto za y
	int pre2X, pre2Y;
	teloX[0] = x;
	teloY[0] = y;
	for (int i = 1; i < nTelo; i++)//,princip dodavanja tela i=1 jer vec glava zmije zauzima nesto,tako da je ovo bas telo
	{
		pre2X = teloX[i];
		pre2Y = teloY[i];
		teloX[i] = preX;
		teloY[i] = preY;
		preX = pre2X;
		preY = pre2Y;
		//prev2X,prev2Y su kordinate novog tela zmijice,ono prvo ne postoji,zmijina glava je nulti deo u telu zmije,odnosno prvi,svi ostali delovi su 1,2,3,4...
		//u zavisnosti od duzine tela zmije
		//pre2X = teloX[i]; kordinate tela zmije i koliko ce se puta dodavati,
		//pre2Y = teloY[i];
		//teloX[i] = preX; odnosno ono mesto gde je zmijina glava bila sada ce se stvoriti jedan komadic zmijinog tela odnosno 'o',ovo je logika,a crtanje gore
		//teloY[i] = preY;
		//preX = pre2X; a telo zmije moze biti ko zna koliko,preX je onaj deo zmijice koji stalno ide uz glavu zmije, i uvek njenu prethodnu
		// poziciju zauzima,dok pre2X su svi ostali ustvari delovi zmije i oni prate i zauzimaju kordinate ovog preX
		//preY = pre2Y;
	}
	int preU = teloX2[0];
	int preC = teloY2[0];
	int pre2X2, pre2Y2;
	teloX2[0] = u;
	teloY2[0] = c;
	for (int p = 1; p < nTelo2; p++)
	{
		pre2X2 = teloX2[p];
		pre2Y2 = teloY2[p];
		teloX2[p] = preU;
		teloY2[p] = preC;
		preU = pre2X2;
		preC = pre2Y2;
	}
	switch (dir) //cista logika kretanja zmije
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;//-- jer je 0 gore skroz i ako idemo prema gore,a npr je zmija bila na kordinati y=7,da bi ona isla gore po kordinati y,y se mora smanjiti
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	switch (dir2) //cista logika kretanja zmije
	{
	case LEFT2:
		u--;
		break;
	case RIGHT2:
		u++;
		break;
	case UP2:
		c--;//-- jer je 0 gore skroz i ako idemo prema gore,a npr je zmija bila na kordinati y=7,da bi ona isla gore po kordinati y,y se mora smanjiti
		break;
	case DOWN2:
		c++;
		break;
	default:
		break;
	}
	switch (score)
	{
	case 100:
		score = score + 40;
		
		break;
	case 400:
		score = score + 60;
	
		break;
	case 1000:
		score = score + 80;
		
		break;
	case 2000:
		score = score + 120;
		
		break;
	}
	switch (score2)
	{
	case 100:
		score2 = score2 + 40;
		
		break;
	case 400:
		score2 = score2 + 60;
	
		break;
	case 1000:
		score2 = score2 + 80;
		
		break;
	case 2000:
		score2 = score2 + 120;
	
		break;
	}
	//if (x > width|| x < 0|| y > height || y < 0)
	//	gameOver = true;
	for (int i = 0; i < nTelo; i++)
		if (teloX[i] == x && teloY[i] == y)//ako se podudare kordinate glave i tela,gubi zivot zmija
		{
			zivot = zivot - 1;
		}
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;
	if (u >= width) u = 0; else if (u < 0) u = width - 1;
	if (c >= height) c = 0; else if (c < 0) c = height - 1;
	if (x == fruitX && y == fruitY)//ako je zmijina tacka jednaka tacki vockice,dodaje se skor +10 i stvara se nova radnom pozicija vockice
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTelo++;//ako su kordinate iste,povecava se telo zmije
	}
	if (u == fruitX && c == fruitY)
	{
		score2 += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTelo2++;
	}
	
	if (x == u && y == c || x == (u - 1) && y == c ||x == u && y == (c - 1) || (x - 1) == u && (y - 1) == c  /*x == preU && y == preC || u == preX && c == preY || x == preU && y == preC || u == teloX[1] && c == teloY[1]|| x == teloX2[1] && y == teloY2[1]*/ )
		//omogucava da ako se poklope jedna i druga zmija da ih premesta na random poziciju na mapi
	{
		score=score-50;
		score2=score2-50;
		zivot=zivot-1;
		zivot2=zivot2-1;
		x = rand() % width;
		y = rand() % height;

		u = rand() % width;
		c = rand() % height;		
	}
	
	
	cout << "\n SKOR PRVE ZMIJE: " << score << endl;
	cout << " \n SKOR DRUGE ZMIJE: " << score2 << endl;
	cout << "\t\t\t\t Zivota prve zmije : " << zivot << endl;
	cout << "\t\t\t\t Zivota druge zmije: " << zivot2 << endl;
	
	 if (zivot <= 0 && zivot2 <= 0)
		gameOver = true;
	
	
}

  
	





void Logic2()
{
	int preX = teloX[0];//prethodna kordinata jednog dela tela zmije(x),znaci ono 'o' posle 'O'
	int preY = teloY[0];//isto za y
	int pre2X, pre2Y;
	teloX[0] = x;
	teloY[0] = y;
	for (int i = 1; i < nTelo; i++)//,princip dodavanja tela i=1 jer vec glava zmije zauzima nesto,tako da je ovo bas telo
	{
		pre2X = teloX[i];
		pre2Y = teloY[i];
		teloX[i] = preX;
		teloY[i] = preY;
		preX = pre2X;
		preY = pre2Y;
		//prev2X,prev2Y su kordinate novog tela zmijice,ono prvo ne postoji,zmijina glava je nulti deo u telu zmije,odnosno prvi,svi ostali delovi su 1,2,3,4...
		//u zavisnosti od duzine tela zmije
		//pre2X = teloX[i]; kordinate tela zmije i koliko ce se puta dodavati,
		//pre2Y = teloY[i];
		//teloX[i] = preX; odnosno ono mesto gde je zmijina glava bila sada ce se stvoriti jedan komadic zmijinog tela odnosno 'o',ovo je logika,a crtanje gore
		//teloY[i] = preY;
		//preX = pre2X; a telo zmije moze biti ko zna koliko,preX je onaj deo zmijice koji stalno ide uz glavu zmije, i uvek njenu prethodnu
		// poziciju zauzima,dok pre2X su svi ostali ustvari delovi zmije i oni prate i zauzimaju kordinate ovog preX
		//preY = pre2Y;
	}
	int preU = teloX2[0];
	int preC = teloY2[0];
	int pre2X2, pre2Y2;
	teloX2[0] = u;
	teloY2[0] = c;
	for (int p = 1; p < nTelo2; p++)
	{
		pre2X2 = teloX2[p];
		pre2Y2 = teloY2[p];
		teloX2[p] = preU;
		teloY2[p] = preC;
		preU = pre2X2;
		preC = pre2Y2;
	}
	switch (dir) //cista logika kretanja zmije
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;//-- jer je 0 gore skroz i ako idemo prema gore,a npr je zmija bila na kordinati y=7,da bi ona isla gore po kordinati y,y se mora smanjiti
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	switch (dir2) //cista logika kretanja zmije
	{
	case LEFT2:
		u--;
		break;
	case RIGHT2:
		u++;
		break;
	case UP2:
		c--;//-- jer je 0 gore skroz i ako idemo prema gore,a npr je zmija bila na kordinati y=7,da bi ona isla gore po kordinati y,y se mora smanjiti
		break;
	case DOWN2:
		c++;
		break;
	default:
		break;
	}
	switch (score)
	{
	case 100:
		score = score + 40;
		zivot = zivot + 1;
		break;
	case 200:
		score = score + 60;
		zivot = zivot + 3;
		break;
	case 500:
		score = score + 100;
		zivot = zivot + 6;
		break;
	case 2000:
		score = score + 200;
		zivot = zivot + 10;
		break;
	}
	switch (score2)
	{
	case 100:
		score2 = score2 + 40;
		zivot2 = zivot2 + 1;
		break;
	case 200:
		score2 = score2 + 60;
		zivot2 = zivot2 + 3;
		break;
	case 500:
		score2 = score2 + 100;
		zivot2 = zivot2 + 6;
		break;
	case 2000:
		score2 = score2 + 200;
		zivot2 = zivot2 + 10;
		break;
	}
	//if (x > width || x < 0) || y > height || y < 0)//ako zmijina glava izadje iz okvira igre
	//{
	//	zivot = zivot - 1;
	//	}
	if (x >= width)
	{
		zivot = zivot - 1;
		score= score-100;
		dir = LEFT;
	}
	if (x <= -1)
	{
		zivot = zivot - 1;
		score=score-100;
		dir = RIGHT;
	}
	if (y >= height)
	{
		zivot = zivot - 1;
		score=score-100;
		dir = UP;
	}
	if (y <= -1)
	{
		zivot = zivot - 1;
		score=score-100;
		dir = DOWN;
	}
	if (u >= width)
	{
		zivot2 = zivot2 - 1;
		score2 = score2 -100;
		dir2 = LEFT2;
	}
	if (u <= -1)
	{
		zivot2 = zivot2 - 1;
		score2 = score2 -100;
		dir2 = RIGHT2;
	}
	if (c >= height)
	{
		zivot2 = zivot2 - 1;
		score2 = score2 -100;
		dir2 = UP2;
	}
	if (c <= -1)
	{
		zivot2 = zivot2 - 1;
		score2 = score2 -100;
		dir2 = DOWN2;
	}
	for (int i = 0; i < nTelo; i++)
		if (teloX[i] == x && teloY[i] == y)//ako se podudare kordinate glave i tela,igra je gotova
		{
			zivot = zivot - 1;
			score2 = score2 -100;
			score= score - 100;
		}
	//if (x >= width) x = 0; else if (x < 0) x = width - 1;
	//if (y >= height) y = 0; else if (y < 0) y = height - 1;
	if (x == fruitX && y == fruitY)//ako je zmijina tacka jednaka tacki vockice,dodaje se skor +10 i stvara se nova radnom pozicija vockice
	{
		score += 20;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTelo++;//ako su kordinate iste,povecava se telo zmije
	}
	if (u == fruitX && c == fruitY)
	{
		score2 += 20;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTelo2++;
	}
	cout << "\n SKOR PRVE ZMIJE: " << score << endl;
	cout << " \n SKOR DRUGE ZMIJE: " << score2 << endl;
	cout << "\t\t\t\t Zivota prve zmije : " << zivot << endl;
	cout << "\t\t\t\t Zivota druge zmije: " << zivot2 << endl;





	/*
	
	int preU = teloX2[0];
	int preC = teloY2[0];
	int pre2X2, pre2Y2;
	teloX2[0] = u;
	teloY2[0] = c;
	for (int p = 1; p < nTelo2; p++)
	{
		pre2X2 = teloX2[p];
		pre2Y2 = teloY2[p];
		teloX2[p] = preU;
		teloY2[p] = preC;
		preU = pre2X2;
		preC = pre2Y2;
	}
	
	
	*/
	
	if (x == u && y == c || x == (u - 1) && y == c ||x == u && y == (c - 1) || (x - 1) == u && (y - 1) == c  /*x == preU && y == preC || u == preX && c == preY || x == preU && y == preC || u == teloX[1] && c == teloY[1]|| x == teloX2[1] && y == teloY2[1]*/ )
		//omogucava da ako se poklope jedna i druga zmija da ih premesta na random poziciju na mapi
	{
		zivot = zivot - 1;
		zivot2 = zivot2 - 1;
		x = rand() % width;
		y = rand() % height;

		u = rand() % width;
		c = rand() % height;		
	}

	


	/*if (zivot <= -1 && zivot2 <= -1)
		gameOver = true;
	*/
	
	if(zivot <= 0 || zivot2 <= 0)
	{
             score= score+((zivot+1)*10);
             score2=score2+((zivot2+1)*10);
             gameOver=true;
    }
}
int main()
{
	char level;
	//Setup();//pozivamo Setup
	/*while (!gameOver)//i sve dok nije gameOver,neka radi sledece
	{
	Draw();
	Input();
	Logic();
	Sleep(50);//brzina kretanja nase zmijice
	}
	*/
	cout << "\t \t *****************" << endl;
	cout << "\t \t *******MENI******" << endl;
	cout << "\t \t *Izaberi level: *\n\t \t * \t \t *" << endl;
	cout << "\t \t *1. Lako        *\n \t \t * \t \t *" << endl;
	cout << "\t \t *2. Normalno    *\n\t \t * \t \t *" << endl;
	cout << "\t \t *3. Tesko       *"  << endl;
	cout << "\t \t ******EXIT*******" << endl;
	cout << "\t \t *****************" << endl;
	cin >> level;
	Setup();
	while (!gameOver)
	{
		switch (level)
		{
		case '1':
		{
			Draw();
			Input();
			Logic0();
			Input();
			//brzina kretanja nase zmijice
			break;
			return 0;
		}
		case '2':
		{
			Draw();
			Input();
			Logic1();
			break;
			return 0;
		}
		case '3':
		{
			Draw();
			Input();
			Logic2();
			Sleep(0);
			break;
			return 0;
		}
		default:
			break;
		}
	}
	if (gameOver)
	{
	}
	system("pause");
	return 0;
}
