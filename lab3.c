// represent a board in reversi, try as a matrix.
//rules of reversi:
/*
1)place your coin somewhere
2)if the position is open then move there
3)if you can connect the dot with other dots then convert all the dots there

things you have to do
1)2D array print

*/
#include <stdio.h>
#include <stdlib.h>
#define rows 8
#define columns 8
int directions;//if direction is 1 for up 10 for r-t-d 100 for right 1000 for r-l-d 10000 for down 100000 for l-l-d 1000000 for left and 10000000 for l-t-d
int array[columns][rows];

int iterator;
int neg(int whose_turn){
	if(whose_turn==1){
		return 2;
	}
	else return 1;
}
typedef struct {
	int valid_counter;
	int direction;
}answer;
answer is_valid_claim(int x_coordinate , int y_coordinate ,int whose_turn){
	answer to_be_returned;
	to_be_returned.valid_counter=0;
	//check if the place asked for is a valid claim 
	//ways to check this would be to first check if it's zero-done
	/*and then check if any same color pattern is made along the lines of other color pattern:
	ways to do this:----
	1) go up check if you are on contrary color if so then start counter and keep going up until you encounter the same color, if you encounter 0 then place count as zero
	2)similarly go digonals and directions now if the place counter
	chanege direction counter as such int direction is a global variable*/
	//this goes up
	int checker = 0;
	to_be_returned.direction = 0;
	for(iterator = y_coordinate;iterator>=0;iterator--){
		//go up then y is --
		if(array[x_coordinate][iterator]==neg(whose_turn)){
			to_be_returned.valid_counter++;
		}
		else if(array[x_coordinate][iterator]==whose_turn){
			break;
		}
		else if(array[x_coordinate][iterator]==0){
			to_be_returned.valid_counter = 0;
			break;
		}
	}
	if(to_be_returned.valid_counter!=checker){
		checker =to_be_returned.valid_counter;
		to_be_returned.direction = to_be_returned.direction+1;
	}
	//goes down
	for(iterator = y_coordinate;iterator<8;iterator++){
		//go up then y is --
		if(array[x_coordinate][iterator]==neg(whose_turn)){
			to_be_returned.valid_counter++;
		}
		else if(array[x_coordinate][iterator]==whose_turn){
			break;
		}
		else if(array[x_coordinate][iterator]==0){
			to_be_returned.valid_counter = 0;
			break;
		}
	}
	if(to_be_returned.valid_counter!=checker){
		checker =to_be_returned.valid_counter;
		to_be_returned.direction = to_be_returned.direction+10;
	}
	//this goes left
	for(iterator = x_coordinate;iterator>=0;iterator--){
		//go up then y is --
		if(array[iterator][y_coordinate]==neg(whose_turn)){
			to_be_returned.valid_counter++;
		}
		else if(array[iterator][y_coordinate]==whose_turn){
			break;
		}
		else if(array[iterator][y_coordinate]==0){
			to_be_returned.valid_counter = 0;
			break;
		}
	}
	if(to_be_returned.valid_counter!=checker){
		checker =to_be_returned.valid_counter;
		to_be_returned.direction = to_be_returned.direction+100;
	}
	//goes right
	for(iterator = x_coordinate;iterator<8;iterator++){
		
		if(array[iterator][y_coordinate]==neg(whose_turn)){
			to_be_returned.valid_counter++;
		}
		else if(array[iterator][y_coordinate]==whose_turn){
			break;
		}
		else if(array[iterator][y_coordinate]==0){
			to_be_returned.valid_counter = 0;
			break;
		}
	}
	if(to_be_returned.valid_counter!=checker){
		checker =to_be_returned.valid_counter;
		to_be_returned.direction = to_be_returned.direction+1000;
	}
	//this goes diagonol right down
	for(iterator=0;(x_coordinate+iterator<8)&&(y_coordinate+iterator<8);iterator++){
		if(array[x_coordinate+iterator][y_coordinate+iterator]==neg(whose_turn)){
			to_be_returned.valid_counter;
		}
		else if(array[x_coordinate+iterator][y_coordinate+iterator]==whose_turn){
			break;
		}
		else if(array[x_coordinate+iterator][y_coordinate+iterator]==0){
			to_be_returned.valid_counter = 0;
			break;
		}

	}
	if(to_be_returned.valid_counter!=checker){
		checker =to_be_returned.valid_counter;
		to_be_returned.direction = to_be_returned.direction+10000;
	}
	//this goes diagonal left up
	for(iterator=0;(x_coordinate-iterator>=0)&&(y_coordinate-iterator>=0);iterator++){
		if(array[x_coordinate-iterator][y_coordinate-iterator]==neg(whose_turn)){
			to_be_returned.valid_counter;
		}
		else if(array[x_coordinate-iterator][y_coordinate-iterator]==whose_turn){
			break;
		}
		else if(array[x_coordinate-iterator][y_coordinate-iterator]==0){
			to_be_returned.valid_counter = 0;
			break;
		}

	}
	if(to_be_returned.valid_counter!=checker){
		checker =to_be_returned.valid_counter;
		to_be_returned.direction = to_be_returned.direction+100000;
	}
	//this goes left down diagonal
	for(iterator=0;(x_coordinate-iterator>=0)&&(y_coordinate+iterator<8);iterator++){
		if(array[x_coordinate-iterator][y_coordinate+iterator]==neg(whose_turn)){
			to_be_returned.valid_counter;
		}
		else if(array[x_coordinate-iterator][y_coordinate+iterator]==whose_turn){
			break;
		}
		else if(array[x_coordinate-iterator][y_coordinate+iterator]==0){
			to_be_returned.valid_counter = 0;
			break;
		}

	}
	if(to_be_returned.valid_counter!=checker){
		checker =to_be_returned.valid_counter;
		to_be_returned.direction = to_be_returned.direction+1000000;
	}
	//this goes right up diagonol
	for(iterator=0;(x_coordinate+iterator>=0)&&(y_coordinate-iterator<8);iterator++){
		if(array[x_coordinate+iterator][y_coordinate-iterator]==neg(whose_turn)){
			to_be_returned.valid_counter;
		}
		else if(array[x_coordinate+iterator][y_coordinate-iterator]==whose_turn){
			break;
		}
		else if(array[x_coordinate+iterator][y_coordinate-iterator]==0){
			to_be_returned.valid_counter = 0;
			break;
		}

	}
	if(to_be_returned.valid_counter!=checker){
		checker =to_be_returned.valid_counter;
		to_be_returned.direction = to_be_returned.direction+10000000;
	}
	return to_be_returned;
}



void claim_valid(int x_coordinate , int y_coordinate ,int whose_turn, answer x){
	//now you know that you can claim the places then how do you go about it?
	//go to the direction
	if(x.direction/10000000!=0){
		for(iterator=0;(x_coordinate+iterator>=0)&&(y_coordinate-iterator<8);iterator++){
			if(array[x_coordinate+iterator][y_coordinate-iterator]==neg(whose_turn)){
				array[x_coordinate+iterator][y_coordinate-iterator]=whose_turn;
			}
			else if(array[x_coordinate+iterator][y_coordinate-iterator]==whose_turn){
				break;
			}

		}
		x.direction = x.direction-10000000;
	}
	if (x.direction/1000000!=0)
	{	
		for(iterator=0;(x_coordinate-iterator>=0)&&(y_coordinate+iterator<8);iterator++){
			if(array[x_coordinate-iterator][y_coordinate+iterator]==neg(whose_turn)){
				array[x_coordinate-iterator][y_coordinate+iterator] = whose_turn;
			}
			else if(array[x_coordinate-iterator][y_coordinate+iterator]==whose_turn){
				break;
			}

		}
		
		x.direction = x.direction-1000000;
	}
	if(x.direction/100000!=0){
		for(iterator=0;(x_coordinate-iterator>=0)&&(y_coordinate-iterator>=0);iterator++){
			if(array[x_coordinate-iterator][y_coordinate-iterator]==neg(whose_turn)){
				array[x_coordinate-iterator][y_coordinate-iterator]=whose_turn;
			}
			else if(array[x_coordinate-iterator][y_coordinate-iterator]==whose_turn){
				break;
			}


		}
		x.direction =x.direction-100000;
	}
	if(x.direction/10000!=0){
		for(iterator=0;(x_coordinate+iterator<8)&&(y_coordinate+iterator<8);iterator++){
			if(array[x_coordinate+iterator][y_coordinate+iterator]==neg(whose_turn)){
				array[x_coordinate+iterator][y_coordinate+iterator]=whose_turn;
			}
			else if(array[x_coordinate+iterator][y_coordinate+iterator]==whose_turn){
				break;
			}

		}
		x.direction =x.direction-10000;
	}
	if(x.direction/1000!=0){
		for(iterator = x_coordinate;iterator<8;iterator++){

			if(array[iterator][y_coordinate]==neg(whose_turn)){
				array[iterator][y_coordinate]=whose_turn;
			}
			else if(array[iterator][y_coordinate]==whose_turn){
				break;
			}
		}
		x.direction =	x.direction-1000;
	}
	if(x.direction/100!=0){
		for(iterator = x_coordinate;iterator>=0;iterator--){
		//go up then y is --
			if(array[iterator][y_coordinate]==neg(whose_turn)){
				array[iterator][y_coordinate]=whose_turn;
			}
			else if(array[iterator][y_coordinate]==whose_turn){
				break;
			}
		}
		x.direction =	x.direction-100;
	}
	if(x.direction/10!=0){
		for(iterator = y_coordinate;iterator<8;iterator++){
		//go up then y is --
			if(array[x_coordinate][iterator]==neg(whose_turn)){
				array[x_coordinate][iterator]=whose_turn;
			}
			else if(array[x_coordinate][iterator]==whose_turn){
				break;
			}

		}
		x.direction =x.direction-10;
	}
	if(x.direction/1!=0){
		for(iterator = y_coordinate;iterator>=0;iterator--){
		//go up then y is --
			if(array[x_coordinate][iterator]==neg(whose_turn)){
				array[x_coordinate][iterator]=whose_turn;
			}
			else if(array[x_coordinate][iterator]==whose_turn){
				break;
			}
		}
		x.direction = x.direction-1;
	}

}





int chance_time(int x){
	printf("Which place do you want to claim?\nEnter -1,-1 when done\n");
	int aye,jay;
	scanf("%d,%d",&aye,&jay);
	if(aye!=-1){		
		if(array[aye][jay]==0){
			array[aye][jay]=x;
			answer this_answer = is_valid_claim(aye,jay,x);
			while(this_answer.valid_counter!=0){
				claim_valid(aye,jay,x,this_answer);
			}
		}
		else {
			printf("Not valid choose again\n");
			chance_time(x);
		}
	}
}
int main(){
	
	//int 0 is nothing 1 is white 2 is black

	int i_out , i_in;
	for(i_out=0;i_out<rows;i_out++){
		for(i_in=0;i_in<columns;i_in++){
			array[i_in][i_out]=0;
		}
	}

int count = 0;//number of chances
//start game
array[3][3]=array[4][4]=1;
array[3][4]=array[4][3]=2;

int game_count = 0;
while(game_count<60){
	printf("   0 1 2 3 4 5 6 7 \n");

	//print array;
	for(i_out=0;i_out<rows;i_out++){
		printf("\n%d  ",i_out%10);
		for(i_in=0;i_in<columns;i_in++){
			printf("%d ",array[i_in][i_out]);;
		}
		
	}
	//Time for play
	printf("\n");
	printf("White turn:\n");
	chance_time(count);
	count++;
	printf("   0 1 2 3 4 5 6 7 \n");

	//print array;
	for(i_out=0;i_out<rows;i_out++){
		printf("\n%d  ",i_out%10);
		for(i_in=0;i_in<columns;i_in++){
			printf("%d ",array[i_in][i_out]);;
		}
		
	}
	printf("\n");
	printf("Black turn\n");
	chance_time(count);
	count--;
	game_count++;
}

return 1;

}
