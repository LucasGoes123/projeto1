
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int i;
    int j;
    int dado;
    int num;
}_coordenadas;

void trocar(_coordenadas dados2[], int a, int b){
    _coordenadas aux;
    aux = dados2[a];
    dados2[a] = dados2[b];
    dados2[b] = aux;
}

int partition(_coordenadas dados[], int min, int max){
    int i = min, j = max+1;
    while (1){
        while(dados[++i].num < dados[min].num){
            if(i == max) break;
        }
        while(dados[min].num < dados[--j].num){
            if(j == min) break;
        }
        if(i >= j) break;
        trocar(dados, i, j);
    }
    trocar(dados, min, j);
    return j;
}
void quicksort(_coordenadas dados[], int min, int max){
    if(max <= min) return;
    int i = partition(dados, min, max);
    quicksort(dados, min, i-1);
    quicksort(dados, i+1, max);
}
int concatenar(int num1, int num2){
    int aux = num1;
    int mult = 1;
    while(1){
        mult = mult*10;
        aux = aux/10;
        if(aux == 0) break;
    }
    return num1*mult+num2;
}
int recuperar(int vetor_A[], int vetor_C[], int vetor_R[], int i, int j){
    int aux = 0;
    if(vetor_R[i] == vetor_R[i+1]){
        return 0;
    }
    else{
        for(int k = vetor_R[i]; k <= vetor_R[i+1]; k++){
            if(j == vetor_C[k]) return vetor_A[k];
        }
        return 0;
    } 	
}
int main(void) {

  int k, maior = -1, num_i, num_j;
  scanf("%d", &k);
  _coordenadas *coordenadas = (_coordenadas*)malloc(k*sizeof(_coordenadas));
  int *A = (int*)malloc(k*sizeof(int));
  int *C = (int*)malloc(k*sizeof(int));
  
  for(int i = 0; i < k; i++){
      scanf("%d %d %d", &coordenadas[i].i, &coordenadas[i].j, &coordenadas[i].dado);
      coordenadas[i].num = concatenar(coordenadas[i].i, coordenadas[i].j);
      if(coordenadas[i].i > maior) maior = coordenadas[i].i;
  }

  int cont = 1, m = maior+1;
  int *R = (int*)malloc((m+200)*sizeof(int));
  R[0] = 0;
  quicksort(coordenadas, 0, k-1);
  for(int i = 0; i < k; i++){
    A[i] = coordenadas[i].dado;
    C[i]= coordenadas[i].j;
    if(coordenadas[i+1].i == cont){
        R[cont] = i+1;
        cont++;
    }
    else if (coordenadas[i+1].i > cont){
        while(1){
            if(coordenadas[i+1].i == cont){
                R[cont] = i+1;
                cont++;
                break;
            } 
            R[cont] = i+1;
            cont++;
        }
    }
  }
  R[m] = k;
  while (1){
    scanf("%d %d", &num_i, &num_j);
    if(num_i == -1 && num_j == -1) break;
    printf("(%d,%d) = %d\n", num_i, num_j, recuperar(A, C, R, num_i, num_j));
  };
  free(A);
  free(C);
  free(R);
  return 0;
}
