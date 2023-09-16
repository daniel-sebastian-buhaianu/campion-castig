#include <stdio.h>
#include <stdlib.h>

#define NMIN 3
#define NMAX 100000
#define VMAX 1000000000

int main()
{
	unsigned n, k, *v, smax, i, st, stmax, drmax, s;

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

	for (s = smax = st = i = 0; i < stmax && stmax >= k; i++) {
		s += v[i];

		if (i-st+1 == k) {
			if (s > smax) smax = s;

			s -= v[st], st++;
		}
	}

	for (s = 0, st = i = drmax+1; i < n && n-drmax-1 >= k; i++) {
		s += v[i];

		if (i-st+1 == k) {
			if (s > smax) smax = s;

			s -= v[st], st++;
		}
	}

	FILE *fout = fopen("castig.out", "w");

	fprintf(fout, "%u", smax);

	fclose(fin);
	fclose(fout);

	free(v);

	return 0;
}
// scor 42
