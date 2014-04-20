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
int set[50001];
int ranks[50001];
node * adjacency[100000] ;
node_edge * arr1[100000] ;
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
int getParent( int x )
{
    if( set[ x ] == x )
    {
        return x;
    }
    else
    {
        set[ x ] = getParent( set[ x ] );
        return set[ x ];
    }
}
int isSameSet( int a , int b )
{
    set[ a ] = getParent( a );
    set[ b ] = getParent( b );
    if(set[ a ] == set[ b ])
    {
        return 1 ;
    }
    return 0 ;
}
void make_union( int a , int b )
{
    if( isSameSet( a , b ) == 1 )
    return ;

    if( ranks[ set[ a ] ] >= ranks[ set[ b ] ] )
    {
        set[ set[ b ] ] = set[ a ];
        set[ b ] = set[ a ];
        if( ranks[ set[ a ] ] == ranks[ set[ b ] ])
        {
            ranks[ set[ a ] ] ++;
        }
    }
    else
    {
        set[ set[ a ] ] = set[ b ];
        set[ a ] = set[ b ];
    }
}
int main()
{
    int test_cases ;
    scanf("%d",&test_cases);
    while( test_cases -- )
    {
        int i , e , n , j , flag = 0 ;
        scanf("%d %d",&n,&e );
        for( i = 1 ; i <= n ; i++ )
        {
            adjacency[i] = (node *)malloc(sizeof(node));
            adjacency[ i ]->vertex = i ;
            adjacency[i]->next = NULL ;
            adjacency[i]->end = adjacency[i];
        }
        for( i = 0 ; i < e ; i++ )
        {
            node_edge * p = (node_edge *)malloc( sizeof(node_edge));
            scanf("%d %d %d",&(p-> starting_point),&(p -> ending_point),&(p -> weight1)) ;
            arr1[i] = p ;
        }
        quick_sort( arr1 , e ) ;

        for( i = 1 ; i <= n ; i++)
        {
            set[i] = i ;
            ranks[i] = 0 ;
        }
        for( i = 0 ; i < e ; i ++ )
        {
            if( isSameSet((arr1[i]->starting_point) ,( arr1[i]->ending_point )) != 1 )
            {
                make_union( arr1[i]->starting_point , arr1[i]->ending_point );
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
