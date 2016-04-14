from knight import Knight
from board import Board

# Define the board size and use it to determine the maximum moves.
BOARD_SIZE = 8
MAX_MOVES = BOARD_SIZE**2

# Define the possible combinations of Knight moves.
MOVE_X = [-2, -1, 1, 2, 2, 1, -1, -2]
MOVE_Y = [1, 2, 2, 1, -1, -2, -2, -1]

# Instantiate the x & y position variables.
x = 9
y = 9

# Take x & y initial inputs. Loop while invalid.
while (((x < 0) or (x > BOARD_SIZE - 1)) or ((y < 0) or (y > BOARD_SIZE - 1))):
    x, y = input("Enter x & y separated by a space (e.g. 4 4): ").split()
    x, y = [int(x), int(y)]

    if ((x < 0) or (x > BOARD_SIZE - 1)):
        print("ERROR:: x must be between 0 and " + str(BOARD_SIZE - 1))

    if ((y < 0) or (y > BOARD_SIZE - 1)):
        print("ERROR:: y must be between 0 and " + str(BOARD_SIZE - 1))

# Create a Knight object to move around the board.
knight = Knight(x, y)

# Instantiate a board and set the initial Knight position with move 1.
board = Board(BOARD_SIZE)
board.place_knight(1, knight.x, knight.y)

for i in range(2, MAX_MOVES + 1):
    num_possibilities = get_num_possibilities(knight, board)

# Print out the board.
board.print_board()

def get_num_possibilities(knight, board):
    """Test each of the eight squares one knight's move away from (I,J) and
    form a list of the possibilities for the next square (next_i(l), next_j(l)).

    Keyword arguments:
    <None>
    """
    num_possibilities = 0
    
    for i in range(0, BOARD_SIZE):
        # Check the next move without storing it.
        temp_x = knight.x + MOVE_X[i]
        temp_y = knight.y + MOVE_Y[i]

        if ((temp_x >= 0) and (temp_x < BOARD_SIZE)
            and (temp_y >= 0) and (temp_y < BOARD_SIZE)
            and board.is_empty(temp_x, temp_y)):
