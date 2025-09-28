#include <iostream>
#include <cstring>

// Fills lps[] for given pattern pat[0..M-1]
void computeKMPTable(char* pat, int M, int* h)
{
	h[0]=-1;
	int i=1,j=0;
	while(i<M){
		if(pat[i]!=pat[j]){
		h[i]=j;
		while(j>=0 && pat[i]!=pat[j])j=h[j];
		i++;
		j++;
		}
		else{
		h[i]=h[j];
		i++;
		j++;
		}
	}
	h[M]=j;
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
	
  

	int n = strlen(pat);               
	int m = strlen(txt);              
	if (n == 0) return;       
	int h[n+1];
	computeKMPTable(pat,n,h);
	int i=0,j=0;
	while(i<m){
		if(txt[i]==pat[j]){
			i++;
			j++;
			if(j==n){
			printf("Found pattern at index %d \n",i-j);
			j=h[j];
			}
		}
		else{
		j=h[j];
		if(j<0){
			i++;
			j++;
		}
		}
	}
}