#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// genEncMatrix generate encoding matrix. upper: Identity_Matrix; lower: Cauchy_Matrix
uint8_t* genEncMatrix(int d, int p){
	int r, off, a, d, i, j;
	uint8_t *m;
	r = d + p;
	m = malloc(r*d);
	// create identity matrix upper
	for (i = 0; i < d; i++){
		m[i*d+i] = 1;
	}
	// create cauchy matrix below
	off = d * d; // offset of encMatrix
	for (i = d; i < r; i++ ){
		for (j = 0; j < d; j++ ){
			d = i ^ j;
			a = inverseTbl[d];
			//TODO may end up with integer promotion
			m[off] = a;
			off++;
		}
	}
	return m;
}

// [A|B] -> [B]
uint8_t* subMatrix(uint8_t* m, int n){
	int off, i;
	uint8_t *b = malloc(n*n);
	for (i = 0; i < n; i++){
		off = i * n;
		//TODO make sure to take care of this slice
		copy(b[off:off+n], m[2*off+n:2*(off+n)])
	}
	return b;
}

uint8_t* invert(uint8_t *m, int n) (im matrix) { // im: inverse_matrix of m
	uint8_t mI = malloc(2*n*n);
	int off, i;
	//TODO make sure this length is calculated correctly
	if (n != len(m)/n) {
		return NULL;
	}
	// step1: (m) -> (m|I)
	off = 0;
	for (i = 0; i < n; i++){
		//TODO again handle this copy
		copy(mI[2*off:2*off+n], m[off:off+n])
		mI[2*off+n+i] = 1;
		off += n;
	}
	// step2: Gaussian Elimination
	// TODO have I handled the guassian shit yet?
	err = mI.gauss(n);
	im = subMatrix(mI, n);
	return im;
}

// swap row[i] & row[j], col = n
void swap(uint8_t* m, int i, int j, int n) {
	int k;
	//TODO this probably doesn't really work right
	for (k = 0; k < n; k++){
		m[i*n+k], m[j*n+k] = m[j*n+k], m[i*n+k];
	}
}

// (A|I) -> (I|A')
int gauss(uint8_t *m, int n){
	int c, i, j, k, e;
	c = 2 * n; // c: cols_num of m
	// main_diagonal(left_part) -> 1 & left_part -> upper_triangular
	for (i = 0; i < n; i++){
		// m[i*c+i]: element of main_diagonal(left_part)
		if (m[i*c+i] == 0){ // swap until get a non-zero element
			for (j = i + 1; j < n; j++){
				if(m[j*c+i] != 0){
					swap(m, i, j, c);
					break;
				}
			}
		}
		if (m[i*c+i] == 0){ // all element in one col are zero
			return -1;
		}
		// main_diagonal(left_part) -> 1
		if (m[i*c+i] != 1){
			e = m[i*c+i];
			s = inverseTbl[e]; // s * e = 1
			for (j = 0; j < c; j++){
				m[i*c+j] = mulTbl[m[i*c+j]][s]; // all element * s (in i row)
			}
		}
		// left_part -> upper_triangular
		for (j = i + 1; j < n; j++){
			if (m[j*c+i] != 0){
				s = m[j*c+i]; // s ^ (s * m[i*c+i]) = 0, m[i*c+i] = 1
				for (k = 0; k < c; k++){
					m[j*c+k] ^= mulTbl[s][m[i*c+k]]; // all element ^ (s * row_i[k]) (in j row)
				}
			}
		}
	}
	// element upper main_diagonal(left_part) -> 0
	for (i = 0; i < n; i++){
		for (j = 0; j < i; j++){
			if (m[j*c+i] != 0){
				s = m[j*c+i]; // s ^ (s * m[i*c+i]) = 0, m[i*c+i] = 1
				for (k = 0; k < c; k++){
					m[j*c+k] ^= mulTbl[s][m[i*c+k]]; // all element ^ (s * row_i[k]) (in j row)
				}
			}
		}
	}
	return 0;
}
