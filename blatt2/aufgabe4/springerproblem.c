#include <stdlib.h>
#include <stdio.h>
#include "brett.h"
#include "output.h"

int n = 8	;
int start_x = 3;
int start_y = 4;
int lsgnr = 1;
int moves[8][2] = {{2,1}, {1,2}, {-2,1}, {-1,2}, {2,-1}, {1,-2}, {-2,-1}, {-1,-2}};
struct t_brett b;	

void setze_springer(struct t_brett *b);

int main()
{
  if (init_brett(&b,n,start_x,start_y)>0) return EXIT_FAILURE;
  setze_springer(&b);
  loesche_brett(&b);
  
  return EXIT_SUCCESS;
}

void setze_springer(struct t_brett *b)
{
  if (besuchte_felder(b)>= n*n) {
	printf("Loesung %i\n", lsgnr);
    lsgnr++;
    print_brett(b);
    printf("\n");
  }
  else {
    int i;
    for (i=0;i<8;i++) {      
      if (frei(b, moves[i][0], moves[i][1])) {
        neuer_sprung(b, moves[i][0], moves[i][1]);
        setze_springer(b);
        entferne_sprung(b, moves[i][0], moves[i][1]);
      }
    }
  }
}

