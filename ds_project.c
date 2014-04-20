//assuming graph has not directed an no repeated edges
#include<stdio.h>
#include<stdlib.h>

typedef struct node_edge
{
    int starting_point ;
    int ending_point ;
    int weight1 ;
}node_edge ;

typedef struct node
{
    int vertex;
    int weight2 ;
    struct node * end ;
    struct node * next ;
}node ;
void dfs( int start , node ** arr , int start_temp , int end_temp ) ;
node * adjacency[100000] ;
node_edge * arr1[100000] ;
int state[1000000] = {} ;
int count = 0 ;

void quick_sort(node_edge ** array , int no_of_edges )
{
    if(no_of_edges == 0)
        return;
    int i = 0 , j = no_of_edges-2 , k ;
    while( i <= j )
    {
        if( array[i]->weight1 < array[no_of_edges-1]->weight1 && array[j]->weight1 > array[no_of_edges-1]->weight1 )
        {
            i++;
            j--;
        }
        else
        if( array[i]->weight1 >= array[no_of_edges-1]->weight1 && array[j]->weight1 >= array[no_of_edges-1]->weight1 )
            j--;
        else
        if( array[i]->weight1 <= array[no_of_edges-1]->weight1 && array[j]->weight1 <= array[no_of_edges-1]->weight1 )
            i++;
        else
        if( array[i]->weight1 > array[no_of_edges-1]->weight1 && array[j]->weight1 < array[no_of_edges-1]->weight1 )
        {
            node_edge * temp = array[i] ;
            array[i] = array[j] ;
            array[j] = temp;
            i++;
            j--;
        }
    }
    node_edge * temp = array[i] ;
    array[i] = array[no_of_edges-1];
    array[no_of_edges-1] = temp;
    quick_sort( &array[0] , j+1 );
    quick_sort( &array[i+1] , no_of_edges-i-1 );
}
int main()
{
    int test_cases ;
    scanf("%d",&test_cases);
    while(test_cases --)
    {
        int i , e , n , j , flag = 0 ;
        count = 0 ;
        scanf("%d %d",&n,&e );
        for( i = 1 ; i <= n ; i++ )
        {
            state[i] = 0;
            adjacency[i] = (node *)malloc(sizeof(node));
            adjacency[ i ]->vertex = i ;
            adjacency[i]->next = NULL ;
            adjacency[i]->end = adjacency[i];
        }
        for( i = 0 ; i < e ; i++ )
        {
            node_edge * r = (node_edge *)malloc( sizeof(node_edge));
            scanf("%d %d %d",&(r-> starting_point),&(r -> ending_point),&(r -> weight1)) ;
            arr1[i] = r ;

            node * p = ( node *)malloc(sizeof(node));
            p->vertex = arr1[i]->ending_point;
            p->weight2 = arr1[i]->weight1;
            p->next = NULL;
            adjacency[ arr1[i]->starting_point ]->end->next = p ;
            adjacency[ arr1[i]->starting_point ] ->end = p ;

            node * q = ( node *)malloc(sizeof(node));
            q->vertex = arr1[i]->starting_point;
            q->weight2 = arr1[i]->weight1;
            q->next = NULL;
            adjacency[ arr1[i]->ending_point ]->end->next = q ;
            adjacency[ arr1[i]->ending_point ] ->end = q ;
        }

        quick_sort( arr1 , e );

        for( i = ( e - 1 ) ; i >= 0  ; i -- )
        {
            count = 0 ;
            for( j = 1 ; j < 100000 ; j ++)
                state[j] = 0 ;
            flag = 0 ;
            state[ arr1[i]->starting_point ] = 1 ;
            count ++;
            dfs( arr1[i]->starting_point ,  adjacency , arr1[i]->starting_point , arr1[i]->ending_point );
            if( count != n )
                flag = 1;
            if( flag == 0 )
            {
                node * p = adjacency[ arr1[i]->starting_point ];
                node * q ;
                while( p != NULL && p->vertex != arr1[i]->ending_point )
                {
                    q = p ;
                    p = p -> next;
                }
                if( p != NULL )
                    q -> next = p -> next;

                p = adjacency[ arr1[i]->ending_point ];
                while( p != NULL && p->vertex != arr1[i]->starting_point )
                {
                    q = p ;
                    p = p -> next;
                }
                if( p != NULL )
                    q -> next = p -> next;
            }
        }
        for( i = 1 ; i <= n ; i++ )
        {
            node * p = adjacency[i];
            while( p != NULL )
            {
                printf("%d ",p->vertex );
                p = p -> next;
            }
            printf("\n");
        }
    }
    return 0;
}
void dfs( int start , node ** arr , int start_temp , int end_temp )
{
    int i ;
    node * p = arr[ start ];
    p = p ->next ;
    while( p != NULL )
    {
        if( ( start == start_temp && p ->vertex == end_temp ) || ( start == end_temp && p->vertex == start_temp ) )
        {
            p = p -> next;
            continue;
        }
        else if( state[ (p ->vertex) ] == 0 )
        {
            state[ (p ->vertex) ] = 1 ;
            count++ ;
            dfs( p ->vertex , arr , start_temp , end_temp ) ;
        }
        p = p -> next ;
    }
    state[start] = 2 ;
    return ;
}
