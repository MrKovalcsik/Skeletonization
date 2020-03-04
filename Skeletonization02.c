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

abc egyenes_egyenlete(point egyik, point masik){ //két pont által meghatározott egyenes egyenletét dobja vissza az Ax+By=C alakban (az ABC értékeket)
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

point metszespont(abc egyik, abc masik){ //a bemeneti paraméterek: két egyenes egyenletének Ax+By=C alakban felírt ABC értéke és a visszatérési érték a két egyenes metszéspontjának koordinátái
	point pont;
	pont.x = (masik.C-(masik.B*(egyik.C/egyik.B)))/(masik.A-(masik.B*(egyik.A/egyik.B)));
	pont.y = (masik.C-(masik.A*(egyik.C/egyik.A)))/(masik.B-(masik.A*(egyik.B/egyik.A)));
	return pont;
}

int rajtavan(point kerdes, point elso, point masik){
	int igaz;
	if (elso.x >= masik.x && elso.y > masik.y){
		if(elso.x >= kerdes.x && kerdes.x >= masik.x&& elso.y >= kerdes.y && kerdes.y >= masik.y){
			igaz = 1;
		} else {
			igaz = 0;
		}
	} else if(elso.x <= masik.x && elso.y > masik.y){
		if(elso.x <= kerdes.x && kerdes.x <= masik.x && elso.y >= kerdes.y && kerdes.y >= masik.y){
			igaz = 1;
		} else {
			igaz = 0;
		}
	} else if(elso.x < masik.x && elso.y <= masik.y){
		if(elso.x <= kerdes.x && kerdes.x <= masik.x && elso.y <= kerdes.y && kerdes.y <= masik.y){
			igaz = 1;
		} else {
			igaz = 0;
		}
	} else if(elso.x > masik.x && elso.y <= masik.y){
		if(elso.x >= kerdes.x && kerdes.x >= masik.x && elso.y <= kerdes.y && kerdes.y <= masik.y){
			igaz = 1;
		} else {
			igaz = 0;
		}
	}
	return igaz;
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
	
	double maximum = 1000;
	int darab = 0;
	int i;
	int k;
	int j;
	int l;
	
	while(maximum > 0.02){
		
		maximum = 0;
		for(i = 0 ; i < 6 ; i++){
			
			double mintav = 1000;
			int kozelipont = 0;
			point kpp;
			point metszes;
			
			for(j = 0 ; j < 6 ; j++){
				
				eltolas[i].x += eltolo_vektor(pontok[i], pontok[j]).x;
				eltolas[i].y += eltolo_vektor(pontok[i], pontok[j]).y;
			}
			
			for(k = 0 ; k < 5 ; k++){
				
				kpp = pszv(pontok[i], hatar[k], hatar[k+1]);
				
				for(l = 0; l < 5; l++){
					if(k != l){
						metszes = metszespont(egyenes_egyenlete(pontok[i], kpp),egyenes_egyenlete(hatar[l], hatar[l+1]));
						int igaz = rajtavan(metszes, hatar[l], hatar[l+1]);
						if(!igaz){
							eltolas[i].x += eltolo_vektor(pontok[i], kpp).x;
							eltolas[i].y += eltolo_vektor(pontok[i], kpp).y;
						}
					}
				}
				double tavolsag = hossz(pontok[i], pszv(pontok[i], hatar[k], hatar[k+1]));
				//printf("%lf %lf %lf %lf %lf\n", pontok[i].x, pontok[i].y, hatar[k].x, hatar[k].y, tavolsag);
				if(tavolsag <= mintav){
					mintav = tavolsag;
				}
			}
			/*
			point eltolt;
			eltolt.x = pontok[i].x + eltolas[i].x;
			eltolt.y = pontok[i].y + eltolas[i].y;
			point vegso;
			for(k = 0 ; k < 6 ; k++){
				point mpont = metszespont(egyenes_egyenlete(pontok[i], eltolt) , egyenes_egyenlete(hatar[k], hatar[k+1]));
				int rajta = rajtavan(mpont, hatar[k], hatar[k+1]);
				double tavolsag = hossz(pontok[i], mpont);
				if(rajta){
					if(pontok[i].x < eltolt.x && pontok[i].x < mpont.x){
						if(tavolsag <= mintav){
							mintav = tavolsag;
							vegso = mpont;
						}
					} else if(pontok[i].x > eltolt.x && pontok[i].x > mpont.x){
						if(tavolsag <= mintav){
							mintav = tavolsag;
							vegso = mpont;
						}
					} else {
						if(pontok[i].y > eltolt.y && pontok[i].y > mpont.y){
							if(tavolsag <= mintav){
								mintav = tavolsag;
								vegso = mpont;
							}
						} else if (pontok[i].y < eltolt.y && pontok[i].y < mpont.y){
							if(tavolsag <= mintav){
								mintav = tavolsag;
								vegso = mpont;
							}
						}
					}
				}
				
			}
			
			eltolas[i].x += eltolo_vektor(pontok[i], vegso).x;
			eltolas[i].y += eltolo_vektor(pontok[i], vegso).y;
			*/
			while(mintav <= vektorhossz(eltolas[i])){
				eltolas[i].x = eltolas[i].x / 2;
				eltolas[i].y = eltolas[i].y / 2;
			}
			
		}
		
		for(i = 0 ; i < 6 ; i++){
			
			pontok[i].x = pontok[i].x + eltolas[i].x;
			pontok[i].y = pontok[i].y + eltolas[i].y;
			if(vektorhossz(eltolas[i]) >= maximum){
				maximum = vektorhossz(eltolas[i]);
			}
			fprintf(outputfile,"%lf %lf %d\n", pontok[i].x, pontok[i].y, darab);
			
		}
		
		darab++;
		
		printf("%lf\n", maximum);
		//fprintf(outputfile,"%lf\n", osszeg);
	}
	
	fclose(outputfile);
	
	return 0;
}
