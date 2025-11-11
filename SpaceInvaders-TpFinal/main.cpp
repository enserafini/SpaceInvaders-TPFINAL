#include <iostream>
#include <conio2.h>
using namespace std;

const int LIM_IZQ = 5;
const int LIM_DER = 115;
const int LIM_SUP = 2;
const int LIM_INF = 28;

void dibujarBordes() {
	
	for (int x = LIM_IZQ; x <= LIM_DER; x++) {
		putchxy(x, LIM_SUP, '-');  
		putchxy(x, LIM_INF, '-');  
	}
	
	for (int y = LIM_SUP; y <= LIM_INF; y++) {
		putchxy(LIM_IZQ, y, '|');  
		putchxy(LIM_DER, y, '|');  
	}
}

class Nave {
private:
	int x;
	int y;
public:
	Nave() {
		x = (LIM_IZQ + LIM_DER) / 2; 
		y = LIM_INF - 1;            
	}
	
	void dibujar() {
		textcolor(RED);
		putchxy(x, y, '^'); 
	}
	
	void borrar() {
		putchxy(x, y, ' ');
	}
	
	void mover() {
		if (kbhit()) {
			int tecla = getch();
			switch (tecla) {
			case 75:
				if (x > LIM_IZQ + 1) {
					borrar();
					x--;
					dibujar();
				}
				break;
			case 77: 
				if (x < LIM_DER - 1) {
					borrar();
					x++;
					dibujar();
				}
				break;
			}
		}
	}
};

int main() {
	dibujarBordes();
	Nave n1;
	n1.dibujar();
	
	while (true) {
		n1.mover();
	}
	return 0;
}
