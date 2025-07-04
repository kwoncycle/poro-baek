#include<stdio.h>
int n;
char s[100100];
int zn;
int next[100100];
int chk[100100];
int zcnt, ocnt;
int main() {
	scanf("%d%s", &n, s);
	zn = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '0')zn++;
	}
	zcnt = 0;
	ocnt = zn;
	for (int i = 0; i < n; i++) {
		if (s[i] == '0') {
			next[zcnt] = i;
			zcnt++;
		}
		else {
			next[ocnt] = i;
			ocnt++;
		}
	}
	int p = 0;
	for (int i = 0; i < n; i++) {
		if (chk[p] == 1) {
			p = i;
			break;
		}
		chk[p] = 1;
		p = next[p];
	}
	if (p != 0) {
		if (n%p == 0) {
			for (int i = 0; i < n; i++) {
				if (s[i] != s[(i / (n / p))*(n / p)]) {
					printf("-1");
					return 0;
				}
			}
		}
		else {
			printf("-1");
			return 0;
		}
	}
	p = 0;
	for (int i = 0; i < n; i++) {
		if (p < zn)printf("0");
		else printf("1");
		p = next[p];
	}
	return 0;
}