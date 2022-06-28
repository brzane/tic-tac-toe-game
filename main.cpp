#include<bits/stdc++.h>
using namespace std;

struct Move
{
	int row, col;
};

char player = 'x', opponent = 'o';
bool isMovesLeft(char board[3][3])
{
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (board[i][j]=='_')
				return true;
	return false;
}

int evaluate(char b[3][3])
{
	for (int row = 0; row<3; row++)
	{
		if (b[row][0]==b[row][1] &&
			b[row][1]==b[row][2])
		{
			if (b[row][0]==player)
				return +10;
			else if (b[row][0]==opponent)
				return -10;
		}
	}
	for (int col = 0; col<3; col++)
	{
		if (b[0][col]==b[1][col] &&
			b[1][col]==b[2][col])
		{
			if (b[0][col]==player)
				return +10;

			else if (b[0][col]==opponent)
				return -10;
		}
	}
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
	{
		if (b[0][0]==player)
			return +10;
		else if (b[0][0]==opponent)
			return -10;
	}

	if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
	{
		if (b[0][2]==player)
			return +10;
		else if (b[0][2]==opponent)
			return -10;
	}

	return 0;
}
int MAX=1000,MIN=-1000;
int minimax(char board[3][3], int depth, bool isMax)
{
	int score = evaluate(board);

	if (score == 10)
		return score;

	if (score == -10)
		return score;

	if (isMovesLeft(board)==false)
		return 0;

	// If this maximizer's move
	if (isMax)
	{           cout<<"max"<<endl;

		int best = MIN;

		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				// Check if cell is empty
				if (board[i][j]=='_')
				{
					// Make the move
					board[i][j] = player;

					// Call minimax recursively and choose
					// the maximum value
					best = max( best,
						minimax(board, depth+1, !isMax) );

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
	//	cout<<"max:"<<best<<endl;
		return best;
	}


	else
	{           cout<<"min"<<endl;

		int best = MAX;

		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				if (board[i][j]=='_')
				{
					board[i][j] = opponent;

					best = min(best,
						minimax(board, depth+1, !isMax));

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		//cout<<"min:"<<best<<endl;
		return best;
	}
}

int alphaBeta(char board[3][3], int depth, bool isMax,int alpha,int beta)
{
	int score = evaluate(board);
	if (score == 10)
		return score;

	if (score == -10)
		return score;

	if (isMovesLeft(board)==false)
		return 0;

	// If this maximizer's move
	if (isMax)
	{           cout<<"max"<<endl;

		int best = MIN;

		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				// Check if cell is empty
				if (board[i][j]=='_')
				{
					// Make the move
					board[i][j] = player;

					// Call minimax recursively and choose
					// the maximum value
					best = max( best,alphaBeta(board, depth+1, !isMax,alpha,beta) );
                    alpha = max(alpha, best);

                    // Alpha Beta Pruning
                    if (beta <= alpha){
                        board[i][j]='_';
                        break;
                    }

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}


	else
	{           cout<<"min"<<endl;

		int best = MAX;

		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				if (board[i][j]=='_')
				{
					board[i][j] = opponent;

					best = min(best,alphaBeta(board, depth+1, !isMax,alpha,beta));
                    beta = min(beta, best);

                    // Alpha Beta Pruning
                    if (beta <= alpha){
                        board[i][j]='_';
                        break;
                    }

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}
}

Move findBestMove(char board[3][3])
{
	int bestVal = MIN;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			// Check if cell is empty
			if (board[i][j]=='_')
			{
				board[i][j] = player;
			//	int moveVal = alphaBeta(board, 0, false,MIN,MAX);
				int moveVal= minimax(board, 0, false);

				// Undo the move
				board[i][j] = '_';

				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	return bestMove;
}
void printBoard(char board[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<board[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void playGame(){
    char board[3][3] =
	{
		{ '_', '_', '_' },
		{ '_', '_', '_' },
		{ '_', '_', '_' }
	};
    bool flag=true;
	while(isMovesLeft(board)){
        Move bestMove= findBestMove(board);
        printf("The Optimal Move is :\n");
	    printf("ROW: %d COL: %d\n\n", bestMove.row, bestMove.col );
	    if(flag==true)
        board[bestMove.row][bestMove.col]=player;
        printBoard(board);
        //check game ended
        int gameStatue= evaluate(board);
        if(gameStatue==10){
            cout<<"X has Won "<<endl;
            break;
        }
        else if(gameStatue==-10){
            cout<<"O has Won"<<endl;
            break;
        }
        else{
        int x,y;
        cout<<"enter where u want to add"<<endl;
        cin>>x>>y;
        if(board[x-1][y-1]=='_'){
            flag= true;
            board[x-1][y-1]=opponent;
        }
        else{
            cout<<endl<<"already Taken"<<endl;
            flag=false;
        }
        }


	}
}


int main()
{
    playGame();
    /*
	char board[3][3] =
	{
		{ 'x', 'o', 'x' },
		{ 'o', 'o', 'x' },
		{ '_', '_', '_' }
	};

	Move bestMove = findBestMove(board);


    */
	return 0;
}
