import sys
import copy

EMPTYHEURISTIC = None
#---------------------------------
class Game:
    
    #Initialize graph as empty array that will be filled with other
    #arrays designating each node of the game board. [[0,1,2,3,4,5,6],...]
    def __init__(self):
        self.gameBoard = []
        self.heuristic = EMPTYHEURISTIC
    
    #Calculates heuristic value for the given game board
    def calculateHeuristicValue(self, gameBoard):

        #Heuristic values to create final value
        maxValue = 0
        minValue = 0
        
        #Start at the bottom row to be sure no erroneous checking
        rowIndex = len(gameBoard) - 1
        
        #While not at the end of the top of the board
        while (rowIndex >= 0):
            columnIndex = 0
            
            #step through each column looking for values
            while (columnIndex != len(gameBoard[rowIndex])):
                
                #Check for all x positions
                if(gameBoard[rowIndex][columnIndex] == 'x'):
                
                    #All the 3 in a row checks
                    #Check if UR UR Diag is there
                    if((rowIndex >= 2) and 
                        columnIndex <= len(gameBoard[rowIndex]) - 3):
                        if(gameBoard[rowIndex-1][columnIndex+1] == 'x' and gameBoard[rowIndex-2][columnIndex+2] == 'x'):
                            maxValue += 1
                
                    #Check if UL UL Diag is there
                    if(rowIndex >= 2 and columnIndex >= 2):
                        if(gameBoard[rowIndex-1][columnIndex-1] == 'x' and gameBoard[rowIndex-2][columnIndex-2] == 'x'):
                            maxValue += 1
                
                    #Check immediate up and up if you can
                    if(rowIndex >= 2):
                        if(gameBoard[rowIndex-1][columnIndex] == 'x' and gameBoard[rowIndex-2][columnIndex] == 'x'):
                            maxValue += 1
                    
                    #Check right right if possible
                    if(columnIndex <= len(gameBoard[rowIndex]) - 3):
                        if(gameBoard[rowIndex][columnIndex+1] == 'x' and gameBoard[rowIndex][columnIndex+2] == 'x'):
                            maxValue += 1 
                            
                    #All the four in a row checks
                    #Check UP UP UP
                    if(rowIndex >= 3):
                        if(gameBoard[rowIndex-1][columnIndex] == 'x' and gameBoard[rowIndex-2][columnIndex] == 'x' and
                            gameBoard[rowIndex-3][columnIndex] == 'x'):
                                hValue = float('inf')
                                return hValue
                    #check R R R
                    if(columnIndex <= len(gameBoard[rowIndex]) - 4):
                        if(gameBoard[rowIndex][columnIndex+1] == 'x' and gameBoard[rowIndex][columnIndex+2] == 'x' and
                            gameBoard[rowIndex][columnIndex+3] == 'x'):
                                hValue = float('inf')
                                return hValue
                    
                    #check UL UL UL
                    if(rowIndex >= 3 and columnIndex >= 3):
                        if(gameBoard[rowIndex-1][columnIndex-1] == 'x' and gameBoard[rowIndex-2][columnIndex-2] == 'x' and
                            gameBoard[rowIndex-3][columnIndex-3] == 'x'):
                                hValue = float('inf')
                                return hValue
                    
                    #check UR UR UR
                    if(rowIndex >= 3 and 
                        columnIndex <= len(gameBoard[rowIndex]) - 4):
                        if(gameBoard[rowIndex-1][columnIndex+1] == 'x' and gameBoard[rowIndex-2][columnIndex+2] == 'x' and
                            gameBoard[rowIndex-3][columnIndex+3] == 'x'):
                                hValue = float('inf')
                                return hValue
                    
                #Check for all o positions
                elif(gameBoard[rowIndex][columnIndex] == 'o'):
                
                    #Check if UR UR Diag is there
                    if((rowIndex >= 2) and 
                        columnIndex <= len(gameBoard[rowIndex]) - 3):
                        if(gameBoard[rowIndex-1][columnIndex+1] == 'o' and gameBoard[rowIndex-2][columnIndex+2] == 'o'):
                            minValue += 1
                
                    #Check if UL UL Diag is there
                    if(rowIndex >= 2 and columnIndex >= 2):
                        if(gameBoard[rowIndex-1][columnIndex-1] == 'o' and gameBoard[rowIndex-2][columnIndex-2] == 'o'):
                            minValue += 1
                
                    #Check immediate up and up if you can
                    if(rowIndex >= 2):
                        if(gameBoard[rowIndex-1][columnIndex] == 'o' and gameBoard[rowIndex-2][columnIndex] == 'o'):
                            minValue += 1
                
                    #Check right right if possible
                    if(columnIndex <= len(gameBoard[rowIndex]) - 3):
                        if(gameBoard[rowIndex][columnIndex+1] == 'o' and gameBoard[rowIndex][columnIndex+2] == 'o'):
                            minValue += 1
                            
                    #All the four in a row checks
                    #Check UP UP UP
                    if(rowIndex >= 3):
                        if(gameBoard[rowIndex-1][columnIndex] == 'o' and gameBoard[rowIndex-2][columnIndex] == 'o' and
                            gameBoard[rowIndex-3][columnIndex] == 'o'):
                                hValue = -(float('inf'))
                                return hValue
                                
                    #check R R R
                    if(columnIndex <= len(gameBoard[rowIndex]) - 4):
                        if(gameBoard[rowIndex][columnIndex+1] == 'o' and gameBoard[rowIndex][columnIndex+2] == 'o' and
                            gameBoard[rowIndex][columnIndex+3] == 'o'):
                                hValue = -(float('inf'))
                                return hValue
                    
                    #check UL UL UL
                    if(rowIndex >= 3 and columnIndex >= 3):
                        if(gameBoard[rowIndex-1][columnIndex-1] == 'o' and gameBoard[rowIndex-2][columnIndex-2] == 'o' and
                            gameBoard[rowIndex-3][columnIndex-3] == 'o'):
                                hValue = -(float('inf'))
                                return hValue
                    
                    #check UR UR UR
                    if(rowIndex >= 3 and 
                        columnIndex <= len(gameBoard[rowIndex]) - 4):
                        if(gameBoard[rowIndex-1][columnIndex+1] == 'o' and gameBoard[rowIndex-2][columnIndex+2] == 'o' and
                            gameBoard[rowIndex-3][columnIndex+3] == 'o'):
                                hValue = -(float('inf'))
                                return hValue
                                
                #Check next column            
                columnIndex += 1
            rowIndex -= 1
        
        hValue = maxValue - minValue
        return hValue
    
    #Check for win state after move is made
    def CheckWin(self, gameBoard):
        rowIndex = len(gameBoard) - 1
        
        while (rowIndex >= 0):
            columnIndex = 0
            
            #step through each column looking for values
            while (columnIndex != len(gameBoard[rowIndex])):
                
                #Check for all x positions
                if(gameBoard[rowIndex][columnIndex] == 'x'):
                    #All the four in a row checks
                    #Check UP UP UP
                    if(rowIndex >= 3):
                        if(gameBoard[rowIndex-1][columnIndex] == 'x' and gameBoard[rowIndex-2][columnIndex] == 'x' and
                            gameBoard[rowIndex-3][columnIndex] == 'x'):
                                print("X WINS!!!")
                                return False
                    #check R R R
                    if(columnIndex <= len(gameBoard[rowIndex]) - 4):
                        if(gameBoard[rowIndex][columnIndex+1] == 'x' and gameBoard[rowIndex][columnIndex+2] == 'x' and
                            gameBoard[rowIndex][columnIndex+3] == 'x'):
                                print("X WINS!!!")
                                return False
                    
                    #check UL UL UL
                    if(rowIndex >= 3 and columnIndex >= 3):
                        if(gameBoard[rowIndex-1][columnIndex-1] == 'x' and gameBoard[rowIndex-2][columnIndex-2] == 'x' and
                            gameBoard[rowIndex-3][columnIndex-3] == 'x'):
                                print("X WINS!!!")
                                return False
                    
                    #check UR UR UR
                    if(rowIndex >= 3 and 
                        columnIndex <= len(gameBoard[rowIndex]) - 4):
                        if(gameBoard[rowIndex-1][columnIndex+1] == 'x' and gameBoard[rowIndex-2][columnIndex+2] == 'x' and
                            gameBoard[rowIndex-3][columnIndex+3] == 'x'):
                                print("X WINS!!!")
                                return False
                    
                    
                #Check for all o positions
                elif(gameBoard[rowIndex][columnIndex] == 'o'):
                    #All the four in a row checks
                    #Check UP UP UP
                    if(rowIndex >= 3):
                        if(gameBoard[rowIndex-1][columnIndex] == 'o' and gameBoard[rowIndex-2][columnIndex] == 'o' and
                            gameBoard[rowIndex-3][columnIndex] == 'o'):
                                print("O WINS!!!")
                                return False
                                
                    #check R R R
                    if(columnIndex <= len(gameBoard[rowIndex]) - 4):
                        if(gameBoard[rowIndex][columnIndex+1] == 'o' and gameBoard[rowIndex][columnIndex+2] == 'o' and
                            gameBoard[rowIndex][columnIndex+3] == 'o'):
                                print("O WINS!!!")
                                return False
                    
                    #check UL UL UL
                    if(rowIndex >= 3 and columnIndex >= 3):
                        if(gameBoard[rowIndex-1][columnIndex-1] == 'o' and gameBoard[rowIndex-2][columnIndex-2] == 'o' and
                            gameBoard[rowIndex-3][columnIndex-3] == 'o'):
                                print("O WINS!!!")
                                return False
                    
                    #check UR UR UR
                    if(rowIndex >= 3 and 
                        columnIndex <= len(gameBoard[rowIndex]) - 4):
                        if(gameBoard[rowIndex-1][columnIndex+1] == 'o' and gameBoard[rowIndex-2][columnIndex+2] == 'o' and
                            gameBoard[rowIndex-3][columnIndex+3] == 'o'):
                                print("O WINS!!!")
                                return False
            #Check next column            
                columnIndex += 1
            rowIndex -= 1
        return True
        
    #Drops the current players token
    #into the correct column
    def MakeMove(self, column, maxTurn):
        rowIndex = len(self.gameBoard) - 1
        for row in reversed(self.gameBoard):
            if(row[column] == '_'):
                
                if(maxTurn):
                    row[column] = 'x'
                else:
                    row[column] = 'o'       
                return rowIndex
            rowIndex -= 1 
        return
       
    #Checks if a column can receive more tokens 
    #Returns True if not able
    def ColumnFull(self, column):
        if(self.gameBoard[0][column] == "_"):
            return False
        else:
            return True
        
    #Prints the board to the user interface
    def PrintBoard(self):
        index = 0
        for x in self.gameBoard:
            for y in self.gameBoard[index]:
                print(y, end=' ')
            index += 1
            print()
        print("0 1 2 3 4 5 6")
        print()
        
    #Sets the intitial game state
    def Setup(self, filename):
        file = open(filename, "r")
        rowIndex = 0
        #Step through the input file given
        #Insert each item into the correct column and row
        for line in file:
            line = line.split()
            if(len(line) == 0):
                continue
            else:
                self.gameBoard.append([])
                for character in line:
                    self.gameBoard[rowIndex].append(character)
                rowIndex += 1
    
    #Lookahead function minimax tree
    def Lookahead(self,MaxDepth, depth, maxTurn):
        
        #If this is as deep as the lookahead should go,
        #simply return the heuristic value of this board
        if(depth == 0):
            return self.calculateHeuristicValue(self.gameBoard)
            
        #X's turn
        if(maxTurn):
            bestValue = -float("inf")
            #Create a deep copy of the board to change and move through
            #available game states
            for column in range(0, len(self.gameBoard[0])):
                if(not self.ColumnFull(column)):
                    
                    oracleBoard = copy.deepcopy(self)
                    oracleBoard.MakeMove(column, maxTurn)
                    
                    newValue = oracleBoard.Lookahead(MaxDepth, depth - 1, not maxTurn)
                    if(newValue > bestValue):
                        bestValue = newValue
                        columnToPlay = column
            
            if(depth == MaxDepth):
                rowToPlay = self.MakeMove(columnToPlay, maxTurn)
                print('[',rowToPlay,', ', columnToPlay,'] ', bestValue, sep='')
                #self.PrintBoard()
                
            return bestValue
            
        #O's turn
        else:
            bestValue = float("inf")
            for column in range(0, len(self.gameBoard[0])):
                if(not self.ColumnFull(column)):
                    
                    oracleBoard = copy.deepcopy(self)
                    oracleBoard.MakeMove(column, maxTurn)
                    
                    newValue = oracleBoard.Lookahead(MaxDepth, depth - 1, not maxTurn)
                    if(newValue < bestValue):
                        bestValue = newValue
                        columnToPlay = column
           
            if(depth == MaxDepth):
                self.MakeMove(columnToPlay, maxTurn)
                #self.PrintBoard()
                
            return bestValue



    #Driver function that plays the game using
    #lookahead to perform moves for the players
    #with a minimax tree. Prints results of each move to the screen and 
    #finally a winner
    def Play(self, lookahead):
        
        #Always start on "X" or MAX turn
        #If false, it is "O" or MIN turn
        maxTurn = True
        playing = True
    
        while playing:
            
            #Depth of turns to check
            depth = (lookahead * 2) + 1
            MaxDepth = depth
            #On X's turn, Lookahead the number of steps needed and select the 
            #best move
            if maxTurn:
                
                self.heuristic = self.Lookahead(MaxDepth, depth, maxTurn) 
                
            #On O's turn. Simply play the best move available to them    
            else:
                
                self.heuristic = self.Lookahead(1, 1, maxTurn)
                
            self.heuristic = EMPTYHEURISTIC  
            
            #Check for win state to end game
            playing = self.CheckWin(self.gameBoard)
            
            #Switch to the next players turn.
            maxTurn = not maxTurn

        return
#---------------------------------
def main():
    
    #Initialize the game board
    connect4Board = Game()

    #Collect the command line args given
    filename = sys.argv[1]
    lookahead = int(sys.argv[2])

    #Setup the initial game board with input file
    connect4Board.Setup(filename)
    connect4Board.PrintBoard()
    connect4Board.Play(lookahead)
    return
    
main()
