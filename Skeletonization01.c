#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct point{
		double x;
		double y;
	}point;
	
typedef struct abc{
	double A;
	double B;
	double C;
}abc;
	
double vektorhossz(point vektor){
	return sqrt( vektor.x * vektor.x + vektor.y * vektor.y );
}
double hossz(point e, point m){
	return sqrt( ( (e.x - m.x) * (e.x - m.x) ) + ( (e.y - m.y) * (e.y - m.y) ) );
}

abc egyenes_egyenlete(point egyik, point masik){
	abc egyenes;
	egyenes.A = masik.y - egyik.y;
	egyenes.B = egyik.x - masik.x;
	egyenes.C = egyenes.A * egyik.x + egyenes.B * egyik.y;
	return egyenes;
}
	
point eltolo_vektor(point origo, point visz){
	point kul, vektor;
	if( (origo.x == visz.x) && (origo.y == visz.y)){
		vektor.x = 0;
		vektor.y = 0;
	}else{
		kul.x = origo.x - visz.x;
		kul.y = origo.y - visz.y;
		vektor.x = kul.x / ( vektorhossz(kul) * vektorhossz(kul) * vektorhossz(kul) );
		vektor.y = kul.y / ( vektorhossz(kul) * vektorhossz(kul) * vektorhossz(kul) );
	}
	return vektor;
}

point pszv(point origo, point egyik, point masik){ /* Egy origo(x,y) ponthoz a egyik(x1,y1) és a masik(x2,y2) szakaszon lévõ legközelebbi pont koordinátáit adja vissza. */
	double ae, be, ce;    /* ae, be, ce: a P1(x1,y1) P2(x2,y2) szakaszra illeszkedeõ egyenes egyenletének (Ax+Bx=C) A, B és C eleme*/
	double am, bm, cm;    /* am, bm, cm: a P1(x1,y1) P2(x2,y2) szakaszra merõleges egyenes egyenletének (Ax+Bx=C) A, B és C eleme*/
	point kozel;
	point veg;
	ae = masik.y - egyik.y;
	be = egyik.x - masik.x;
	ce = ae * egyik.x + be * egyik.y;
	am = egyik.x - masik.x;
	bm = egyik.y - masik.y;
	cm = am * origo.x + bm * origo.y;
	kozel.x = (cm-(bm*(ce/be)))/(am-(bm*(ae/be)));
	kozel.y = (cm-(am*(ce/ae)))/(bm-(am*(be/ae)));
	if(egyik.x < masik.x){
		if(masik.x > kozel.x && egyik.x<kozel.x){
			veg.x = kozel.x;
		} else if(masik.x <= kozel.x){
			veg.x = masik.x;
		} else if(egyik.x >= kozel.x){
			veg.x = egyik.x;
		}
	} else if(egyik.x > masik.x){
		if(egyik.x > kozel.x && masik.x < kozel.x){
			veg.x = kozel.x;
		} else if(egyik.x <= kozel.x){
			veg.x = egyik.x;
		} else if(masik.x >= kozel.x){
			veg.x = masik.x;
		}
	} else if(egyik.x == masik.x){
		veg.x = egyik.x;
	}
	if(egyik.y < masik.y){
		if(masik.y > kozel.y && egyik.y < kozel.y){
			veg.y = kozel.y;
		} else if(masik.y <= kozel.y){
			veg.y = masik.y;
		} else if(egyik.y >= kozel.y){
			veg.y = egyik.y;
		}
	} else if(egyik.y > masik.y){
		if(egyik.y > kozel.y && masik.y < kozel.y){
			veg.y = kozel.y;
		} else if(egyik.y <= kozel.y){
			veg.y = egyik.y;
		} else if(masik.y >= kozel.y){
			veg.y = masik.y;
		}
	} else if(egyik.y == masik.y){
		veg.y = egyik.y;
	}
	return veg;
}

int main(){
	FILE * outputfile;
	outputfile = fopen("./Output2.txt", "w");
	
	point pontok[6];
	point hatar[6];
	point eltolas[6];
	
	memset(eltolas,0,sizeof(eltolas));
	
	pontok[0].x = 4.96497;
	pontok[1].x = 1.91939;
	pontok[2].x = 7.96883;
	pontok[3].x = 2.37831;
	pontok[4].x = 8.17743;
	pontok[5].x = 5.25701;
	pontok[0].y = 7.09276;
	pontok[1].y = 5.54911;
	pontok[2].y = 5.50739;
	pontok[3].y = 1.79428;
	pontok[4].y = 2.00288;
	pontok[5].y = 4.04717;
	
	hatar[0].x = 0;
	hatar[1].x = 0;
	hatar[2].x = 5;
	hatar[3].x = 10;
	hatar[4].x = 10;
	hatar[5].x = 0;
	hatar[0].y = 0;
	hatar[1].y = 10;
	hatar[2].y = 8;
	hatar[3].y = 10;
	hatar[4].y = 0;
	hatar[5].y = 0;
	
	double max = 1000;
	int darab = 0;
	int i;
	int k;
	int j;
	
	while(max > 0.4){
		
		max = 0;
		for(i = 0 ; i < 6 ; i++){
			
			double mintav = 1000;
			int kozelipont = 0;
			point kpp;
			
			for(k = 0 ; k < 5 ; k++){
				
				double tavolsag = hossz(pontok[i], pszv(pontok[i], hatar[k], hatar[k+1]));
				//printf("%lf %lf %lf %lf %lf\n", pontok[i].x, pontok[i].y, hatar[k].x, hatar[k].y, tavolsag);
				if(tavolsag <= mintav){
					mintav = tavolsag;
					kozelipont = k;
				}
				
			}
			
			kpp = pszv(pontok[i], hatar[kozelipont], hatar[kozelipont+1]);
			
			eltolas[i].x += eltolo_vektor(pontok[i], kpp).x;
			eltolas[i].y += eltolo_vektor(pontok[i], kpp).y;
			
			for(j = 0 ; j < 6 ; j++){
				
				eltolas[i].x += eltolo_vektor(pontok[i], pontok[j]).x;
				eltolas[i].y += eltolo_vektor(pontok[i], pontok[j]).y;
			}
			
			while(mintav <= vektorhossz(eltolas[i])){
				eltolas[i].x = eltolas[i].x / 2;
				eltolas[i].y = eltolas[i].y / 2;
			}
			
		}
		
		for(i = 0 ; i < 6 ; i++){
			
			pontok[i].x = pontok[i].x + eltolas[i].x;
			pontok[i].y = pontok[i].y + eltolas[i].y;
			if(vektorhossz(eltolas[i]) >= max){
				max = vektorhossz(eltolas[i]);
			}
			fprintf(outputfile,"%lf %lf %d\n", pontok[i].x, pontok[i].y, darab);
			
		}
		
		darab++;
		
		printf("%lf\n", max);
		//fprintf(outputfile,"%lf\n", osszeg);
	}
	
	fclose(outputfile);
	
	return 0;
}
