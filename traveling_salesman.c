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
	//display(n,temp);
	nlb=mat_reduce(n,temp);
	//printf("\nnlb is %d",nlb);
	//display(n,temp);
	cost = low_bound + arr[u][i] + nlb;
	return cost;
}
int BandB(int n, int *arr[]){
	int i,j,u,low_bound,p,nlb,visited[n],order_visit[n],k=0,*min_arr[100],*temp[100],cost,l,m,min_cost,min_cost_index;
	for(i=0;i<n;i++){
		visited[i]=0;
	}
	
	u=0; //previous node. initially it is source node
	//calculated lower bound at node 0
	low_bound = mat_reduce(n,arr);
	//printf("original lower bound %d",low_bound);
	order_visit[k++]=0;
	visited[u]=1;
	//display(n,arr);
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
				//printf("\ncost of node %d to %d is %d" ,u,i,cost);
				if(cost<min_cost){
					min_cost=cost;
					min_cost_index=i;
					copy(n,temp,min_arr);
				}
			}
		}
		u=min_cost_index;
		//printf("\n\ngoing to %d ",u);
		visited[u]=1;
		order_visit[k++]=u;
		low_bound=min_cost;
		copy(n,min_arr,arr);
		//printf("\n\narray for next is ");
		//display(n,arr);
	}
	//to display order of visit
    /*printf("\norder of visit is ");
    for(i=0;i<n;i++){
    	printf("%d ",order_visit[i]);
    }
    printf("\n total cost is %d\n",low_bound);
*/	return low_bound;
}

int greedy(int n, int *arr[]){
	int i,j,visited[n],u,cost=0,min_dist,min_ind,k=0,order_visit[n];

	for(i=0;i<n;i++){
		visited[i]=0;
	}
	u=0; //initially source node is 0
	visited[0]=1;
	order_visit[k++]=0;

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
		cost+=min_dist;
		visited[u]=1;
		order_visit[k++]=u;
	}
	cost+=arr[u][0];
	//to display order of visit
    /*printf("\norder of visit is ");
    for(i=0;i<n;i++){
    	printf("%d ",order_visit[i]);
    }*/
    return cost;
}
int main()
{
	clock_t start_t,end_t,total_t;
    int *arr[100], *temp[100], x, n, m, i ,j, k, result[46][6];
    time_t t;
    srand((unsigned) time(&t));

    printf("\nEnter the number of nodes : ");
    scanf("%d",&n);
    for(i=0; i<n; i++){
        arr[i] = (int*)calloc(n,sizeof(int));
        for(j=0;j<n;j++){
        	if(i==j){
        		arr[i][j]=1000;
        	}
        	else{
            	x=rand()%49+1;
        		arr[i][j]=x;
        	}
        }
    }

    display(n, arr);
    
    for(i=0;i<46;i++){
    	m=i+5;
    	for(j=0;j<m;j++){
    		temp[j] = (int*)calloc(m,sizeof(int));
    		for(k=0;k<m;k++){
    			temp[j][k]=arr[j][k];
    		}
    	}
    	start_t = clock();
    	result[i][0] = greedy(m,temp);
    	end_t = clock();
   		total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC *1000000;
 		result[i][1]=total_t;


    	start_t = clock();
 		result[i][2] = BandB(m,temp);
    	end_t = clock();    	
   		total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC * 1000000;
 		result[i][3]=total_t;
 	}
 	printf("\n\n NOTE time is in microseconds");
 	printf("\n\n %25s  %20s ","GREEDY","BRANCH and BOUND");
 	printf("\n %15s  %10s  %10s  %10s\n","cost","time","cost","time");
 	for(i=0;i<46;i++){
 		m=i+5;
 		printf("%5d",i+5);
 		for(j=0;j<4;j++){
 			printf(" %10d ",result[i][j]);
 		}
 		printf("\n");
 	}

    return 0;
}
