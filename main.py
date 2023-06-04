import pygame, random
from button import Button

# Define grid dimensions
ROWS = 20
COLS = 20

GRID_WIDTH = 800
BUTTON_WIDTH = 200

HEIGHT = 800
CELL_SIZE = GRID_WIDTH // COLS

# Define colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (200, 0, 0)
GRAY = (200, 200, 200)

# Initialize Pygame
pygame.init()

window = pygame.display.set_mode((GRID_WIDTH + BUTTON_WIDTH, HEIGHT))
clock = pygame.time.Clock()

# Create grid
grid = [[0] * COLS for _ in range(ROWS)]

def clear_grid():
    global grid
    grid = [[0] * COLS for _ in range(ROWS)]

def start_pathfinding():
    print('starting pathfinding')

def randomize_grid():
    """
    Randomly fills the grid with 0s and 1s (0 = empty, 1 = wall), with a 20% chance of a cell being a wall
    """
    
    global grid
    for row in range(ROWS):
        for col in range(COLS):
            if random.random() < 0.10:
                grid[row][col] = 1
            else:
                grid[row][col] = 0

    grid[0][ROWS - 1] = 2
    grid[ROWS - 1][0] = 2

# Create buttons
but = Button(
    window,
    x = GRID_WIDTH + 35,
    y = 50,
    width = BUTTON_WIDTH - 70,
    height = 110,
    buttonText='Clear',
    onclickFunction= clear_grid,
    onePress=True
)
but2 = Button(
    window,
    x= GRID_WIDTH + 35,
    y= 655,
    width = BUTTON_WIDTH - 70,
    height = 110,
    buttonText='Start',
    onclickFunction= start_pathfinding,
    onePress=True
)
but3 = Button(
    window,
    x= GRID_WIDTH + 35,
    y= 350,
    width = BUTTON_WIDTH - 70,
    height = 110,
    buttonText='Random',
    onclickFunction= randomize_grid,
    onePress=True
)

# Main game loop
running = True
while running:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Clear the screen
    window.fill(WHITE)

    # why the button is not showing up?

    # Draw the grid
    for row in range(ROWS):
        for col in range(COLS):
            cell_color = WHITE if grid[row][col] == 0 else BLACK

            if grid[row][col] == 2:
                cell_color = RED

            pygame.draw.rect(window, cell_color, (col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE))
            pygame.draw.rect(window, GRAY, (col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE), 1)

        
    but.process()
    but2.process()
    but3.process()

    try:
        if pygame.mouse.get_pressed()[0]:
            pos = pygame.mouse.get_pos()
            col = pos[0] // CELL_SIZE
            row = pos[1] // CELL_SIZE
            grid[row][col] = 1

        elif pygame.mouse.get_pressed()[2]:
            pos = pygame.mouse.get_pos()
            col = pos[0] // CELL_SIZE
            row = pos[1] // CELL_SIZE
            grid[row][col] = 0

        if pygame.key.get_pressed()[pygame.K_SPACE]:
            # Start the game
            pos = pygame.mouse.get_pos()
            col = pos[0] // CELL_SIZE
            row = pos[1] // CELL_SIZE
            grid[row][col] = 2

    except:
        pass


    
    # Update the screen
    pygame.display.flip()
    clock.tick(60)

# Quit the game
pygame.quit()
