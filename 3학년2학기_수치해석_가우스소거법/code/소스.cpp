#include <stdio.h>
#include <math.h>

void printResult(double aug[3][4]) {
	printf("a1\ta2\ta3\tb\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++)
			printf("%.1f\t", aug[i][j]);
		printf("\n");
	}
}

void changeRow(double (&row1)[4], double (&row2)[4]) {
	double temp[4] = { 0, };

	for (int i = 0; i < 4;i++) {
		temp[i] = row1[i];
		row1[i] = row2[i];
		row2[i] = temp[i];
	}
}

void Q1_standardGaussian(double aug[3][4]) {
	// Gaussian elimination about ar1
	for (int r = 0; r < 3; r++) {

		// if pivot point == 0
		if (aug[r][r] == 0) {
			// (Er) ¡ê (Er+1)
			// Re-operation r-th row
			changeRow(aug[r], aug[r + 1]);
			r--;
			continue;
		}

		// Calculate mkr
		for (int k = r + 1; k < 3; k++) {
			double mkr = aug[k][r] / aug[r][r];

			// (Ek - mkrEr) ¡æ (Ek)
			for (int c = r; c < 4; c++)
				aug[k][c] -= mkr * aug[r][c];
		}
	}

	printResult(aug);
}

void Q2_partialPivoting(double aug[3][4]) {
	for (int r = 0; r < 3; r++) {
		
		// Check what is largest in same column
		int row = r;
		for (int R = r+1; R < 3; R++)
			if (fabs(aug[row][r]) < fabs(aug[R][r])) row = R;

		// if aii is larger that aji
		if (row != r) {
			// (Er) ¡ê (ER)
			// Re-operation r-th row
			changeRow(aug[r], aug[row]);
			r--;
			continue;
		}

		// Elimination
		if (aug[r][r] == 0) {
			changeRow(aug[r], aug[r + 1]);
			r--;
			continue;
		}

		for (int k = r + 1; k < 3; k++) {
			double mkr = aug[k][r] / aug[r][r];
			for (int c = r; c < 4; c++)
				aug[k][c] -= mkr * aug[r][c];
		}
	}

	printResult(aug);
}

void Q3_scaledPartial(double aug[3][4]) {
	for (int r = 0; r < 3; r++) {
		// Set scale factor
		double sk[3] = { fabs(aug[r][r]), fabs(aug[r][r]), fabs(aug[r][r]) };
		for (int i = r; i < 3; i++)
			for (int j = r; j < 3; j++)
				if (sk[i] < fabs(aug[i][j])) sk[i] = fabs(aug[i][j]);

		// Find p-th row
		int p = r;
		for (int P = p + 1;P < 3;P++)
			if (fabs(aug[p][r]) / sk[p] < fabs(aug[P][r] / sk[P])) p = P;

		// (Er) ¡ê (EP)
		if (r != p)	changeRow(aug[r], aug[p]);

		// Elimination
		if (aug[r][r] == 0) {
			changeRow(aug[r], aug[r + 1]);
			r--;
			continue;
		}

		for (int k = r + 1; k < 3; k++) {
			double mkr = aug[k][r] / aug[r][r];
			for (int c = r; c < 4; c++)
				aug[k][c] -= mkr * aug[r][c];
		}
	}

	printResult(aug);
}

int main() {
	double a1_aug[3][4] = { {1, -5, 1, 7}, {10, 0, 20, 6}, {5, 0, -1, 4} };
	double b1_aug[3][4] = { {1, 1, -1, 1}, {1, 1, 4, 2}, {2, -1, 2, 3} };
	double c1_aug[3][4] = { {2, -3, 2, 5}, {-4, 2, -6, 14}, {2, 2, 4, 8} };
	double d1_aug[3][4] = { {0, 1, 1, 6}, {1, -2, -1, 4}, {1, -1, 1, 5} };

	printf("Q1. standard Gaussian elimination");
	printf("\na.\n");	Q1_standardGaussian(a1_aug);
	printf("\nb.\n");	Q1_standardGaussian(b1_aug);
	printf("\nc.\n");	Q1_standardGaussian(c1_aug);
	printf("\nd.\n");	Q1_standardGaussian(d1_aug);

	double a2_aug[3][4] = { {1, -5, 1, 7}, {10, 0, 20, 6}, {5, 0, -1, 4} };
	double b2_aug[3][4] = { {1, 1, -1, 1}, {1, 1, 4, 2}, {2, -1, 2, 3} };
	double c2_aug[3][4] = { {2, -3, 2, 5}, {-4, 2, -6, 14}, {2, 2, 4, 8} };
	double d2_aug[3][4] = { {0, 1, 1, 6}, {1, -2, -1, 4}, {1, -1, 1, 5} };

	printf("\nQ2. Gaussian elimination with partial pivoting");
	printf("\na.\n");	Q2_partialPivoting(a2_aug);
	printf("\nb.\n");	Q2_partialPivoting(b2_aug);
	printf("\nc.\n");	Q2_partialPivoting(c2_aug);
	printf("\nd.\n");	Q2_partialPivoting(d2_aug);

	double a3_aug[3][4] = { {1, -5, 1, 7}, {10, 0, 20, 6}, {5, 0, -1, 4} };
	double b3_aug[3][4] = { {1, 1, -1, 1}, {1, 1, 4, 2}, {2, -1, 2, 3} };
	double c3_aug[3][4] = { {2, -3, 2, 5}, {-4, 2, -6, 14}, {2, 2, 4, 8} };
	double d3_aug[3][4] = { {0, 1, 1, 6}, {1, -2, -1, 4}, {1, -1, 1, 5} };

	printf("\nQ3. Gaussian elimination with scaled partial pivoting");
	printf("\na.\n");	Q3_scaledPartial(a3_aug);
	printf("\nb.\n");	Q3_scaledPartial(b3_aug);
	printf("\nc.\n");	Q3_scaledPartial(c3_aug);
	printf("\nd.\n");	Q3_scaledPartial(d3_aug);
}