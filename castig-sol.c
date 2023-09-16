#include <stdio.h>
#include <stdlib.h>

#define NMIN 3
#define NMAX 100000
#define VMAX 1000000000

int main()
{
	long long s;
	unsigned n, k, *v, i, st, stmax, drmax;
	unsigned long long smax;

	FILE *fin = fopen("castig.in", "r");
	
	if (!fin) { printf("Eroare castig.in\n"); return 1; }

	fscanf(fin, "%u %u", &n, &k);

	if (n < NMIN || n > NMAX) { printf("Eroare valoare n\n"); return 2; }

	if (k < 1 || k > NMAX/3) { printf("Eroare valoare k\n"); return 3; }

	v = (unsigned*)malloc(n*sizeof(unsigned));

	for (s = smax = st = i = 0; i < n; i++) {
		fscanf(fin, "%u", &v[i]);
			
		if (v[i] < 1 || v[i] > VMAX) { printf("Eroare valore v[%u]\n", i); return 4; }

		s += v[i];

		if (i-st+1 == k) {
			if (s > smax) smax = s, stmax = st, drmax = i;
			
			s -= v[st], st++;	
		}
	}

	fclose(fin);

	for (s = smax = st = i = 0; i < n; i++) {
		if (i == stmax)
			st = i = drmax+1, s = v[st];
		else {
			s += v[i];

			if (i-st+1 == k) {
				if (s > smax) smax = s;
				
				s -= v[st], st++;	
			}
		}
	}

	FILE *fout = fopen("castig.out", "w");

	fprintf(fout, "%llu", smax);

	fclose(fout);

	free(v);

	return 0;
}
// scor 59
