/* gfsm.c -- finite state machine implementation task
 *
 * Roger Dannenberg
 * Aug 2014, Proxor
 */

#include <stdio.h>
#include <string.h>

/* these are possible states */
#define START 0
#define INT 1
#define FRAC 2
#define END 3

/* This is the current state. Do not change this */
int state = START;

/* This is the value of the number parsed by the fsm.
 * Do not change this declaration.
 */
double sign = 1.0;
double output = 0.0;
double significance = 0.1;

/* fsm_accept is called with each input character. It
 * updates state (defined above) to the current state 
 * according to the state transition diagram in README.txt.
 *
 * In addition, sign, output, and significance are computed
 * according to the algorithm in README.txt. Note that 
 * while there are various ways to compute output, for this
 * task, output must always contain the absolute value of the
 * number parsed so far.
 * 
 * main() is designed so that you can complete and test the
 * parser first, then add code to compute output. This is
 * recommended.
 */
void fsm_accept(char input)
{
  switch (state)
  {
    case 0:
    
      if (((input-'0')>=0 && (input-'0')<=9) || input== '+' ||input== '-'  )
      {
        state=INT;
      }
      else if (input=='.')
      {
        state=FRAC;
      }
      if (input=='-')
      {
        sign=-1.0;
      }
      else if ((input-'0')>=0 && (input-'0')<=9)
      {
        output=input-'0';
	printf("%f\n",output);
      }
      break;

    case 1:
    
      if ((input-'0')>=0 && (input-'0')<=9)
      {}
      else if (input=='.')
      {
        state=FRAC;
      }
      else 
      {
        state=END;
      }
      if ((input-'0')>=0 && (input-'0')<=9)
      {
        output=output*10+(input-'0');
	printf("%f\n",output);
      }
      break;

    case 2:
    
      if ((input-'0')>=0 && (input-'0')<=9)
      {
        output=output+(input-'0')*significance;
        significance=significance*0.1;
	printf("%f\n",output);
      }
      else 
      {
        state=END;
      }
	
      break;
    default:
      break;
  }
}


/* main() provides a simple test of your code.
 * Recommended: (1) implement just the state transisions and test
                (2) add your own tests
 *              (3) add code to compute output and test
 *              (4) add your own tests
 */
int main()
{
    
     int pass = 1;
    double delta = 0.000001;
    fsm_accept('-');
    pass &= (state == INT);
    fsm_accept('0');
    pass &= (state == INT);
    fsm_accept('.');
    pass &= (state == FRAC);
    fsm_accept('5');
    pass &= (state == FRAC);
    fsm_accept('4');
    pass &= (state == FRAC);
    fsm_accept('1');
    pass &= (state == FRAC);
    fsm_accept('2');
    pass &= (state == FRAC);
    fsm_accept('4');
    pass &= (state == FRAC);
    fsm_accept('3');
    pass &= (state == FRAC);
    fsm_accept(' ');
    pass &= (state == END);
	printf("%f\n",output);
    
    if (pass) {
        printf("gfsm has passed some simple tests\n");
    } else {
        printf("gfsm appears to have errors\n");
    }
    if (output < -0.541243 - delta || output > -0.541243 + delta) {
        printf("output is not computed correctly\n");
    }
    
    return 0;
}
