#include<time.h>
#include<stdio.h>
#include<stdlib.h>


void display(int n, int *arr[]){
    int i,j;
    printf("\nCOST matrix is \n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
        	if(arr[i][j]==1000){
      		    printf("   inf ");
        		
        	}
        	else{
            printf("%3d ",arr[i][j]);
        	}
        }
        printf("\n");
    }
}

int mat_reduce(int n, int *arr[]){
    int i,j,lowerbound=0,min=0;
    for(i=0;i<n;i++){
        min=arr[i][0];
        for(j=1;j<n;j++){
           	if(arr[i][j]<min){
           		min=arr[i][j];
           	}
        }
        for(j=0;j<n;j++){
            if(arr[i][j]!=1000){
              	arr[i][j]-=min;
           	}
        }
        if(min!=1000)
          	lowerbound+=min;
    }

    for(j=0;j<n;j++){
        min=arr[0][j];
        for(i=1;i<n;i++){
          	if(arr[i][j]<min){
           		min=arr[i][j];
           	}
        }
        for(i=0;i<n;i++){
            if(arr[i][j]!=1000){
              	arr[i][j]-=min;
           	}
        }
        if(min!=1000)
          	lowerbound+=min;
    }
    return lowerbound;
}

void copy(int n, int *arr[], int *temp[]){
	int i=0,j=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			temp[i][j]=arr[i][j];
		}
	}
}
int choose(int n, int *temp[], int *arr[], int u, int i, int low_bound){
	int j, nlb, cost;
	for(j=0;j<n;j++){
		temp[u][j]=1000;
		temp[j][i]=1000;
	}
	temp[i][0]=1000;
	nlb=mat_reduce(n,temp);
	cost = low_bound + arr[u][i] + nlb;
	return cost;
}
/*
int BandB1(int n, int *arr[]){
	int i,j,u,low_bound,p,nlb,visited[n],order_visit[n],k=0,*min_arr[100],*temp[100],cost,l,m,min_cost,min_cost_index;
	for(i=0;i<n;i++){
		visited[i]=0;
	}
	
	u=0; //previous node. initially it is source node
	//calculated lower bound at node 0
	low_bound = mat_reduce(n,arr);
	//order_visit[k++]=0;
	visited[u]=1;
    for(i=0; i<n; i++){
        temp[i] = (int*)calloc(n,sizeof(int));
        min_arr[i]= (int*)calloc(n,sizeof(int));
	}
	for(p=1;p<n;p++)
	{
		min_cost=10000;
		for(i=0;i<n;i++)
		{
			if(visited[i]!=1){
				copy(n,arr,temp);
				cost = choose(n,temp,arr,u ,i, low_bound);
				if(cost<min_cost){
					min_cost=cost;
					min_cost_index=i;
					copy(n,temp,min_arr);
				}
			}
		}
		u=min_cost_index;
		visited[u]=1;
		order_visit[k++]=u;
		low_bound=min_cost;
		copy(n,min_arr,arr);
	}
	return low_bound;
}
*/
int BandB(int n, int *arr[], int visited[], int u){
	int i,k,x,y,count=0,*temp[n],low_bound,next[n], min_cost, min_cost_index,cost;
	
	low_bound=mat_reduce(n,arr);
	visited[u]=1;
	//printf("\nlow bound is %d",low_bound);
	//display(n,arr);
	for(i=0;i<n;i++){
		if(visited[i]==1){
			count++;
		}
	}
	if(count==n){
		return 0;
	}
    
    for(i=0; i<n; i++){
    	next[i]=0;
        temp[i] = (int*)calloc(n,sizeof(int));
    }

	min_cost=1000;
	for(i=1;i<n;i++){
		if(visited[i]!=1){
			copy(n,arr,temp);
			cost = choose(n,temp,arr,u,i,low_bound);
	//		printf("\ncost for %d is %d",i,cost);
			if(cost<min_cost){
	//			printf("\ncost %d is replaced by %d",min_cost,cost);
				min_cost=cost;
				min_cost_index=i;
				for(k=0;k<n;k++){
					next[k]=0;
				}
				next[i]=1;
			}
			else if(cost==min_cost){
				next[i]=1;
			}
		}
	}
	for(i=0;i<n;i++){
		if(next[i]==1){
			copy(n,arr,temp);
			cost = choose(n,temp,arr,u,i,low_bound);
	//		printf("\ngoing to %d",i);

			x = BandB(n,temp,visited,i);		
			x = x + cost;
			break;
		}
	}
	i++;
	for(;i<n;i++){
		if(next[i]==1){
			copy(n,arr,temp);
			cost = choose (n,temp,arr,u,i,low_bound);
			y= BandB(n,temp,visited,i);
			y = y + cost;
			if(y<x){
				x=y;
			}
		}
	}
	return x;

}
int greedy(int n, int *arr[]){
	int i,j,visited[n],u,cost=0,min_dist,min_ind;

	for(i=0;i<n;i++){
		visited[i]=0;
	}
	u=0; //initially source node is 0
	visited[0]=1;
	for(i=1;i<n;i++){
		min_dist=1000;
		for(j=1;j<n;j++){
			if(visited[j]==0){
				if(arr[u][j]<min_dist){
					min_dist=arr[u][j];
					min_ind=j;
				}
			}
		}
		u=min_ind;
		if(min_dist!=1000){
			cost+=min_dist;
		}
		visited[u]=1;
	}
	cost+=arr[u][0];
    return cost;
}
int main()
{
	clock_t start_t,end_t,total_t;
    int *arr[100], *temp[100], x, n, m, i ,j, k, result[46][6],visited[100];
    time_t t;
    srand((unsigned) time(&t));

    printf("\nEnter the number of nodes : ");
    scanf("%d",&n);
    for(i=0; i<n; i++){
    	visited[i]=0;
        arr[i] = (int*)calloc(n,sizeof(int));
        temp[i] = (int*)calloc(m,sizeof(int));
        for(j=0;j<n;j++){
        	if(i==j){
        		arr[i][j]=1000;
        	}
        	else{
            	x=rand()%49+1;
        		arr[i][j]=x;
        	}
        }
    }/*
    arr[0][0]=1000,arr[0][1]=20,arr[0][2]=30,arr[0][3]=10,arr[0][4]=11,arr[0][5]=40;
    arr[1][0]=15,arr[1][1]=1000,arr[1][2]=16,arr[1][3]=4,arr[1][4]=2,arr[1][5]=42;
    arr[2][0]=3,arr[2][1]=5,arr[2][2]=1000,arr[2][3]=2,arr[2][4]=4,arr[2][5]=11;
    arr[3][0]=17,arr[3][1]=6,arr[3][2]=18,arr[3][3]=1000,arr[3][4]=3,arr[3][5]=20;
    arr[4][0]=16,arr[4][1]=4,arr[4][2]=7,arr[4][3]=16,arr[4][4]=1000,arr[4][5]=4;
    arr[5][0]=23,arr[5][1]=23,arr[5][2]=13,arr[5][3]=40,arr[5][4]=27,arr[5][5]=1000;
*/
  /*  
    arr[0][0]=1000,arr[0][1]=48,arr[0][2]=4,arr[0][3]=47,arr[0][4]=23;
    arr[1][0]=32,arr[1][1]=1000,arr[1][2]=7,arr[1][3]=33,arr[1][4]=42;
    arr[2][0]=18,arr[2][1]=10,arr[2][2]=1000,arr[2][3]=15,arr[2][4]=7;
    arr[3][0]=25,arr[3][1]=12,arr[3][2]=6,arr[3][3]=1000,arr[3][4]=20;
    arr[4][0]=19,arr[4][1]=9,arr[4][2]=40,arr[4][3]=27,arr[4][4]=1000;
*/
    display(n, arr);
    
    for(i=0;i<=n-5;i++){
    	m=i+5;
    	for(j=0;j<m;j++){
    		visited[j]=0;
    	}
    	copy(m,arr,temp);	
    	start_t = clock();
    	result[i][0] = greedy(m,temp);
    	end_t = clock();
   		total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC *1000000;
 		result[i][1]=total_t;


    	start_t = clock();
 		result[i][2] = BandB(m, temp, visited, 0);
    	end_t = clock();    	
   		total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC * 1000000;
 		result[i][3]=total_t;
 	}
 	printf("\n\n NOTE time is in microseconds");
 	printf("\n\n %25s  %20s ","GREEDY","BRANCH and BOUND");
 	printf("\n %15s  %10s  %10s  %10s\n","cost","time","cost","time");
 	for(i=0;i<=n-5;i++){
 		m=i+5;
 		printf("%5d",i+5);
 		for(j=0;j<4;j++){
 			printf(" %10d ",result[i][j]);
 		}/*
 		if(result[i][0]<result[i][2]){
 			printf(" boo");
 		}*/
 		printf("\n");
 	}
/*
    for(j=0;j<n;j++){
    		visited[j]=0;
    }
 	display(n,arr);
 	printf("Band B is %d ",BandB(n,arr,visited,0));
*/
    return 0;
}
