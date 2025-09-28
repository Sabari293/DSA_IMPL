#include "common.h"

// Add two matrices
Matrix add(const Matrix &A, const Matrix &B) {
  int n = A.size();
  Matrix C(n, vector<int>(n));
  // TODO
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)C[i][j]=A[i][j]+B[i][j];
  }
  return C;
}

// Subtract two matrices
Matrix subtract(const Matrix &A, const Matrix &B) {
  int n = A.size();
  Matrix C(n, vector<int>(n));
  // TODO
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)C[i][j]=A[i][j]-B[i][j];
  }
  return C;
}

// Naive O(N^3) matrix multiplication
Matrix naiveMultiply(const Matrix &A, const Matrix &B) {
  int n = A.size();
  Matrix C(n, vector<int>(n));
  // TODO
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      for(int k=0;k<n;k++){
        C[i][j]+=A[i][k]*B[k][j];
      }
    }
  }
  return C;
}

// Strassen's matrix multiplication, use the reference for the algorithm
Matrix strassenMultiply(const Matrix &A, const Matrix &B, int threshold) {
  int n = A.size();
  Matrix C(n, vector<int>(n));
  // TODO
  if(n==1){
    C[0][0]=A[0][0]*B[0][0];
    return C;
  }
  Matrix A11(n/2,vector<int> (n/2,0)),A12(n/2,vector<int> (n/2,0)),A21(n/2,vector<int> (n/2,0)),A22(n/2,vector<int> (n/2,0)),B11(n/2,vector<int> (n/2,0)),B12(n/2,vector<int> (n/2,0)),B22(n/2,vector<int> (n/2,0)),B21(n/2,vector<int> (n/2,0));
  for(int i=0;i<n/2;i++){
    for(int j=0;j<n/2;j++){
        A11[i][j]=A[i][j];
        A12[i][j]=A[i][j+n/2];
        A21[i][j]=A[i+n/2][j];
        A22[i][j]=A[i+n/2][j+n/2];
        B11[i][j]=B[i][j];
        B12[i][j]=B[i][j+n/2];
        B21[i][j]=B[i+n/2][j];
        B22[i][j]=B[i+n/2][j+n/2];
    }
  }
  Matrix A1=add(A11,A22);
  Matrix A2=add(A21,A22);
  Matrix A3=add(A11,A12);
  Matrix S1=subtract(A21,A11);
  Matrix S2=subtract(A12,A22);
  Matrix B1=add(B11,B22);
  Matrix B2=add(B11,B12);
  Matrix B3=add(B21,B22);
  Matrix BS1=subtract(B12,B22);
  Matrix BS2=subtract(B21,B11);
  Matrix M1=strassenMultiply(A1,B1,threshold);
  Matrix M2=strassenMultiply(A2,B11,threshold);
  Matrix M3=strassenMultiply(A11,BS1,threshold);
  Matrix M4=strassenMultiply(A22,BS2,threshold);
  Matrix M5=strassenMultiply(A3,B22,threshold);
  Matrix M6=strassenMultiply(S1,B2,threshold);
  Matrix M7=strassenMultiply(S2,B3,threshold);
  Matrix C11(n/2,vector<int> (n/2)),C12(n/2,vector<int> (n/2,0)),C21(n/2,vector<int> (n/2,0)),C22(n/2,vector<int> (n/2,0));
  C11=subtract(add(add(M1,M4),M7),M5);
  C12=add(M3,M5);
  C21=add(M2,M4);
  C22=subtract(add(add(M1,M3),M6),M2);
  for(int i=0;i<n/2;i++){
    for(int j=0;j<n/2;j++){
        C[i][j]=C11[i][j];
        C[i][j+n/2]=C12[i][j];
        C[i+n/2][j]=C21[i][j];
        C[i+n/2][j+n/2]=C22[i][j];
    }
  }
  return C;
}


bool equal(const Matrix &A, const Matrix &B) {
    /*
        Returns True if the input matrices are equal and false otherwise
    */
    // TODO
  int n=A.size();
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)if(A[i][j]!=B[i][j])return 0;
  }
  return true; // Dummy return
}

