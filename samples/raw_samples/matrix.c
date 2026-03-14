int main() {
  // ---- Create 2D array ----
  int mat[3][5];

  // ---- Declare r and c ----
  int r = 0;
  int c = 0;

  // ---- Fill matrix ----
  for (r = 0; r < 3; r++) {
    for (c = 0; c < 5; c++) {
      mat[r][c] = (r + 1) * (c + 1);
    }
  }

  return 0;
}
