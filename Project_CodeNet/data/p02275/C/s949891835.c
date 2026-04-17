    C[A[i]]++;

  for(i = 1; i <= MAXV; i++)
    C[i] += C[i-1];

  for(i = 1; i <= n; i++){
    B[C[A[i]]] = A[i];
    C[A[i]]--;
  }

  for(i = 1; i <= n; i++){
    if(i > 1)
      printf(" ");
    printf("%d", B[i]);
  }

  printf("\n");

  return 0;
}