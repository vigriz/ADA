#include <stdio.h>

int graph[40][40], n, visited[40]={0}, acyclic =1, f=0, r=-1, q[40];

void createGraph(){
	printf("No. of vertices>> ");
	scanf("%d", &n);
	printf("Enter adjacency matrix:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d",&graph[i][j]);
		}
	}
}

void bfs(int v){
	visited[v]=1;
	
	for(int i=0;i<n;i++){
		if (graph[v][i] && !visited[i]){
			printf("%d-->",v);
			q[++r] = i;
		}
		
		if (graph[v][i] && visited[i]){
			acyclic=0;
		}
		
		if(f<=r) {
			visited[q[f]]=1; 
			bfs(q[f++]); 
		}
	}
}

void main(){
	int i,count=0;
	
	createGraph();
	
	bfs(0);
	
	for(i=0;i<n;i++){
		if (visited[i])
			count++;
	}
	
	(count==n) ? printf("\nConnected Graph\n") : printf("\nGraph not connected!\n");
	(acyclic) ? printf("Acyclic Graph\n") : printf("Graph not acyclic!\n");
	
	//Printing connected components
	
	if (count!=n){
		for(i=0;i<n;i++) visited[i]=0;
	
		for(i=0;i<n;i++){
			bfs(i);
			printf("\n");
		}
	}
}
//only to write
void main(){
	int n,i,j;
	int *arr;
	
	FILE *b,*w,*a;
	system("rm a.txt b.txt w.txt");
	b = fopen("b.txt","a");
	w = fopen("w.txt","a");
	a = fopen("a.txt","a");
	
	for(n=10;n<1000;n+=10){
		arr = (int*)malloc(n*sizeof(int));
		
		//Best Case
		count=0;
		for(i=0;i<n;i++){
			arr[i] = (i==0) ? rand()%100 : arr[i-1]+rand()%10;
		}
		mergeSort(arr,0,n-1);
		fprintf(b,"%d\t%d\n",n,count);
		
		//Worst Case
		worstCaseGenerate(arr,0,n-1); //to generate worst case input
		mergeSort(arr,0,n-1);
		fprintf(w,"%d\t%d\n",n,count);
		
		//Average Case
		count=0;
		for(i=0;i<n;i++){
			arr[i] = rand()%100;
		}
		mergeSort(arr,0,n-1);
		fprintf(a,"%d\t%d\n",n,count);
	}
	
	fclose(b); fclose(a); fclose(w);
}
