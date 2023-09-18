#include <stdio.h>
#include <stdlib.h>

#define NMIN 3
#define NMAX 100000
#define VMAX 1000000000

int main()
{
	int i;
	unsigned n, k, st, *v;
	unsigned long long sum, *s, *stmax, *drmax, valmin, maxim;

	FILE *fin = fopen("castig.in", "r");
	
	if (!fin) { printf("Eroare castig.in\n"); return 1; }

	fscanf(fin, "%u %u", &n, &k);

	if (n < NMIN || n > NMAX) { printf("Eroare valoare n\n"); return 2; }

	if (k < 1 || k > NMAX/3) { printf("Eroare valoare k\n"); return 3; }

	v = (unsigned*)malloc(n*sizeof(unsigned));
	
	s = (unsigned long long*)calloc(n, sizeof(unsigned long long));

	if (!v || !s) { printf("Eroare alocare memorie\n"); return 4; }

	for (sum = st = i = 0; i < n; i++) {
		fscanf(fin, "%u", &v[i]);

		if (v[i] < 1 || v[i] > VMAX) { printf("Eroare valoare v[%u]\n", i); return 5; }

		sum += v[i];

		if (i-st+1 == k) {
			s[st] = sum;

			sum -= v[st];

			st++;
		}
	}

	stmax = (unsigned long long*)calloc(n, sizeof(unsigned long long));

	if (!stmax) { printf("Eroare alocare memorie\n"); return 4; }
	
	stmax[k-1] = s[0];

	for (i = k; i < n; i++) {
		stmax[i] = stmax[i-1];

		if (stmax[i] < s[i-k+1]) stmax[i] = s[i-k+1];
	}

	drmax = (unsigned long long*)calloc(n, sizeof(unsigned long long));

	if (!drmax) { printf("Eroare alocare memorie\n"); return 4; }

	drmax[n-k] = s[n-k];

	for (i = n-k-1; i >= 0; i--) {
		drmax[i] = drmax[i+1];

		if (drmax[i] < s[i]) drmax[i] = s[i];
	}

	for (i = 0; i <= n-k; i++) {
		maxim = i-1 >= 0 ? stmax[i-1] : drmax[i+k];
		
		if (i+k < n)
			if (maxim < drmax[i+k]) maxim = drmax[i+k];

		if (i == 0) valmin = maxim;
		else if (valmin > maxim) valmin = maxim;
	}

	FILE *fout = fopen("castig.out", "w");

	fprintf(fout, "%llu", valmin);

	free(v);
	free(s);
	free(stmax);
	free(drmax);

	return 0;
}
// scor 100
