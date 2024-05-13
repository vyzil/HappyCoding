#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static inline int convert(int x){
   assert(x != 0);
   return (x > 0) ? ((x-1)<<1|1) : ((-x-1)<<1|0);
}

int chase(int *parent, int x)
{
   if(x != parent[x])
      parent[x] = chase(parent, parent[x]);
   return parent[x];
}

void sort(int *arr, int len)
{
   int n = 1;
   while(n < len)
   {
      const int w = arr[n++];
      int tx = n, px = n >> 1;
      while(px > 0)
      {
         if(arr[px-1] >= w)
            break;
         arr[tx-1] = arr[px-1];
         tx = px;
         px >>= 1;
      }
      arr[tx-1] = w;
   }
   while(n > 1)
   {
      const int w = arr[--n];
      int tx = 1, cx = 2;
      arr[n] = arr[0];
      while(cx <= n)
      {
         if(cx != n && arr[cx-1] < arr[cx])
            ++cx;
         if(w >= arr[cx-1])
            break;
         arr[tx-1] = arr[cx-1];
         tx = cx;
         cx <<= 1;
      }
      arr[tx-1] = w;
   }
}

/*Graph Function*/
#define NONE (-1)
typedef struct{int v, n;} node_t;

int main(void)
{
   int N, M;
   scanf("%d %d", &N, &M);
   
   //Graph properties
   node_t *edges = calloc(M<<1, sizeof(*edges));
   int *graph = calloc(N<<1, sizeof(int));
   
   //DFS properties
   int *Q = calloc(N << 1, sizeof(int));
   int *iter = calloc(N << 1, sizeof(int));
   int *check = calloc(N << 1, sizeof(int));
   
   //SCC properties
   int *parent = calloc(N << 1, sizeof(int));
   int *stack_depth = calloc(N << 1, sizeof(int));
   
   //Init Loop
   for(int i = 0; i < (N << 1); i++)
   {
      graph[i] = NONE;
      iter[i] = NONE;
      check[i] = NONE;
      parent[i] = i;
   }
   
   //read a statement & make a inverse graph
   for(int i = 0; i < M; i++)
   {
      int a, b;
      scanf("%d %d", &a, &b);
      if(a + b == 0) continue; //meaningless: a --> a and -a --> -a
      
      //a or b <==> (-a --> b) and (-b --> a)
      #define INSERT(A,B,I) \
      {\
         const int x = convert(B), y = convert(A), z = (I);\
         edges[z] = (node_t){y, graph[x]};\
         graph[x] = z;\
      }
      INSERT(-a, b, i << 1 | 0)
      if(a != b) INSERT(-b, a, i << 1 | 1)
      #undef INSERT
   }
   
   //SCC analysis
   for(int i = 0; i < (N << 1); i++)
   {
      if(check[i] != NONE) continue;
      int pc = 0;
      #define PUSH(X) \
      {\
         check[(X)] = i;\
         stack_depth[(X)] = pc;\
         Q[pc++] = (X);\
      }
      PUSH(i)
      while(pc)
      {
         const int x = Q[pc-1];
         if(iter[x] == NONE)
            iter[x] = graph[x];
         else
            iter[x] = edges[iter[x]].n;
         if(iter[x] == NONE)
         {
            --pc;
            continue;
         }
         
         const int y = edges[iter[x]].v;
         if(check[y] == NONE)
            PUSH(y)
         else if(check[y] == i)
         {
            const int yy = chase(parent, y);
            const int py = stack_depth[yy];
            if(py < pc && Q[py] == yy)
            {
               int it = pc-1;
               while(1)
               {
                  it = stack_depth[chase(parent, Q[it])];
                  if(py >= it) break;
                  parent[Q[it--]] = yy;
               }
            }
         }
      }
      #undef PUSH
   }
   
   //Verifying
   for(int i = 0; i < N; i++)
      if(chase(parent, i << 1 | 0) == chase(parent, i << 1 | 1))
        {
          putchar('0');
            goto finale;
        }
     putchar('1');

   
finale:
   //exit
   free(edges); free(graph);
   free(Q);
   free(parent);
   free(stack_depth); free(iter); free(check);
   return 0;
}