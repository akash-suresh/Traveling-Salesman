#include<stdio.h>
#include<stdlib.h>


void display(int n, int *arr[]){
    int i,j;
    printf("\nadjacency mat is \n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%6d ",arr[i][j]);
        }
        printf("\n");
    }
}

int mat_reduce(int n, int *arr[]){
    int i,j,lowerbound=0,min=0,flag,count;
    for(i=0;i<n;i++){
        flag=0;
        count=0;
        for(j=0;j<n;j++){
            if(arr[i][j]==0){
                flag=1;
                break;
            }
        }
        if(flag==0){
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
    }
    for(j=0;j<n;j++){
        flag=0;
        count=0;
        for(i=0;i<n;i++){
            if(arr[i][j]==0){
                flag=1;
                break;
            }
        }
        if(flag==0){
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
	temp[i][u]=1000;
	//display(n,temp);
	nlb=mat_reduce(n,temp);
	printf("\nnlb is %d",nlb);
	//display(n,temp);
	cost = low_bound + arr[u][i] + nlb;
	return cost;
}
void BandB(int n, int *arr[]){
	int i,j,u,low_bound,p,nlb,visited[n],order_visit[n],k=0,*min_arr[100],*temp[100],cost,l,m,min_cost,min_cost_index;
	for(i=0;i<n;i++){
		visited[i]=0;
	}
	
	u=0; //previous node. initially it is source node
	//calculated lower bound at node 0
	low_bound = mat_reduce(n,arr);
	printf("original lower bound %d",low_bound);
	order_visit[k++]=0;
	visited[u]=1;
	display(n,arr);
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
				printf("\ncost of node %d to %d is %d" ,u,i,cost);
				if(cost<min_cost){
					min_cost=cost;
					min_cost_index=i;
					copy(n,temp,min_arr);
				}
			}
		}
		u=min_cost_index;
		printf("\n\ngoing to %d ",u);
		visited[u]=1;
		order_visit[k++]=u;
		low_bound=min_cost;
		copy(n,min_arr,arr);
		printf("\n\narray for next is ");
		display(n,arr);
	}
	//to display order of visit
    printf("\norder of visit is ");
    for(i=0;i<n;i++){
    	printf("%d ",order_visit[i]);
    }
    printf("\n total cost is %d\n",low_bound);


}
int main()
{
    int *arr[100], x, n, i ,j;
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
    }/*
    arr[0][0]=10,arr[0][1]=37,arr[0][2]=22,arr[0][3]=16;
    arr[1][0]=17,arr[1][1]=36,arr[1][2]=37,arr[1][3]=6;
    arr[2][0]=22,arr[2][1]=43,arr[2][2]=8,arr[2][3]=31;
    arr[3][0]=44,arr[3][1]=24,arr[3][2]=20,arr[3][3]=47;
    */
    display(n, arr);
    BandB(n,arr);
    return 0;
}
