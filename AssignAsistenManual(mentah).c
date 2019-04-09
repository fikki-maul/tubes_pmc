#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char* nama;
	char* prak[4];
	char* hari[5];
} asisten;

//cek search lagi
int search(char* array, char* item, int length)
{
    int i=0, val=0;
    while((array[i]!='0')&&(i<length))
    {
		if (array[i]==item)
		{
			val = 1;
			break;
		} else
		{
			i=i+1;
		}
	}
	return(val);
}

asisten namaAsisten (char initial)
{
	asisten Assist;
	char* nama;
	if (initial=='A')
	{
		Assist.nama = "Amir";
		Assist.prak = {"EL2205", '0'};
		Assist.hari = {"Rabu", '0'};
	} else if (initial=='B')
	{
		Assist.nama = "Budi";
		Assist.prak = {"EL2205", '0'};
		Assist.hari = {"Senin", '0'};
	} else if (initial=='C')
	{
		Assist.nama = "Cici";
		Assist.prak = {"EL2205", '0'};
		Assist.hari = {"Selasa", "Rabu", '0'};
	} else if (initial=='D')
	{
		Assist.nama = "Doni";
		Assist.prak = {"EL2205", '0'};
		Assist.hari = {"Senin", "Rabu", '0'};
	} else if (initial=='E')
	{
		Assist.nama = "Endang";
		Assist.prak = {"EL2205", "EL2208", '0'};
		Assist.hari = {'0'};
	} else if (initial=='F')
	{
		Assist.nama = "Fadel";
		Assist.prak = {"EL2205", '0'};
		Assist.hari = {"Selasa", '0'};
	} else if (initial=='G')
	{
		Assist.nama = "Gilang";
		Assist.prak = {"EL2205", "EB2200", '0'};
		Assist.hari = {"Kamis", '0'};
	} else if (initial=='H')
	{
		Assist.nama = "Hero";
		Assist.prak = {"EL2208", '0'};
		Assist.hari = {"Kamis", '0'};
	} else if (initial=='I')
	{
		Assist.nama = "Intan";
		Assist.prak = {"EL2205", "EL2208", "EB2200", '0'};
		Assist.hari = {"Rabu", '0'};
	} else if (initial=='J')
	{
		Assist.nama = "Joko";
		Assist.prak = {"EL2208", '0'};
		Assist.hari = {"Jumat", '0'};
	} else if (initial=='K')
	{
		Assist.nama = "Kiki";
		Assist.prak = {"EL2208", "EB2200", '0'};
		Assist.hari = {"Jumat", '0'};
	} else if (initial=='L')
	{
		Assist.nama = "Luis";
		Assist.prak = {"EL2208", '0'};
		Assist.hari = {'0'};
	} else if (initial=='M')
	{
		Assist.nama = "Mini";
		Assist.prak = {"EL2208", '0'};
		Assist.hari = {"Rabu", "Kamis", '0'};
	} else if (initial=='N')
	{
		Assist.nama = "Nina";
		Assist.prak = {"EL2208", "EB2200", '0'};
		Assist.hari = {'0'};
	}
	return(Assist);
}

void assignAsisten(jadwal_t* jadwal)
{
	char init;
	char* day, lab;
	int week;
	asisten Assist_func;
	do
	{
		printf("Pilih Asisten (A-N): ");
		bool test==0;
		do
		{
			scanf("%c", &init);
			if((init!='A')&&(init!='B')&&(init!='C')&&(init!='D')&&(init!='E')&&(init!='F')&&(init!='G')&&(init!='H')&&(init!='I')&&(init!='J')&&(init!='K')&&(init!='L')&&(init!='M')&&(init!='N')&&(init!='Q')&&(init!='q'))
			{
				printf("Tidak ada asisten\n");
			}
			else{
                test==1;
			}
		} while (!test);

		if((init!='Q')&&(init!='q')) //pasti asisten ada
		{
			Assist_func = namaAsisten(init);
			scanMinggu(&week);
			scanHari(&day);
			scanRuang(&lab);
			if (*jadwal[week-3][str2enum_hari(day)].lab[str2enum_lab(lab)].assist_count<2) //jumlah asisten kurang dari dua
			{
				if (cekAda(Assist_func, week, day, lab, *jadwal))
				{
					//ada praktikum bersangkutan, cek bisa asisten bisa atau engga
					if (cekBisa(Assist_func, day))
					{
						//cek apakah asisten bisa, jika bisa masukkan ke schedule
						int count = *jadwal[week-3][str2enum_hari(day)].lab[str2enum_lab(lab)].assist_count;
						*jadwal[week-3][str2enum_hari(day)].lab[str2enum_lab(lab)].assist[count] = Assist_func.nama;
						*jadwal[week-3][str2enum_hari(day)].lab[str2enum_lab(lab)].assist_count++; //jumlah assist_count naik
					} else
					{
						//cetak error asisten tidak bisa
						printf("Asisten berhalangan pada hari %s\n", day);
					}
				} else
				{
					printf("Jadwal Asisten Praktikum %s tidak sesuai (tidak ada praktikum bersangkutan)\n");
				}
			} else
			{
				printf("Asisten sudah penuh\n");
			}
		} else
	} while ((init!='Q')&&(init!='q'));
	return();
}

int cekBisa(asisten asis, char* item)
{
	int val;
	if(search(asis.hari, &item, 5)==0)
	{
		val = 1;
	} else
	{
		val = 0;
	}
	return(val);
}

int cekAda(asisten asis, int week, char* day, char* lab, jadwal_t jadwal)
{
	int val;
	int hari = str2enum_hari(&day);
	int room = str2enum_lab(&lab);

	char* prak = jadwal[week-3][hari].lab[room].prak;
	if(search(asis.prak, prak, 4)==1)
	{
		val = 1;
	} else
	{
		val = 0;
	}
	return(val);
}

void scanMinggu(int* week)
{
	do
	{
		printf("Minggu: "); scanf("%d", week);
		if ((&week-3)<0)||((&week-3)>12))
		{
			printf("Minggu salah\n");
		}
	} while ((&week-3)<0)||((&week-3)>12));
}

void scanHari(char* day)
{
	do
	{
		printf("Hari: "); scanf("%s", day);
		if ((str2enum_hari(&day)<0)||(str2enum_hari(&day)>4))
		{
			printf("Hari salah\n");
		}
	} while ((str2enum_hari(&day)<0)||(str2enum_hari(&day)>4));
}


void scanRuang(char* ruang)
{
	do
	{
		printf("Ruang: "); scanf("%s", &ruang);
		if ((str2enum_lab(&ruang)<0)||(str2enum_lab(&ruang)>3))
		{
			printf("Ruang salah\n");
		}
	} while ((str2enum_lab(&ruang)<0)||(str2enum_lab(&ruang)>3));
}

void AssignAssistenManual()
{
	printf("[Mode Assign Asisten]\n");
	printf("Isi `q` atau `Q` untuk kembali ke menu\n");
	assignAsisten(&jadwal);
}
