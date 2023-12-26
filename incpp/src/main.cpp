#include <iostream>
#include <vector>
#include "../include/A_Star.h"
#include <SFML/Graphics.hpp>
#include "constants.h"

const int GRID_SIZE = 200;
const int CELL_SIZE = 800 / GRID_SIZE;


int main() {
    Node start = {0, 0};
    Node goal = {GRID_SIZE - 1, GRID_SIZE - 1};

    std::vector<std::vector<int>> grid{ randomize_grid(GRID_SIZE, 20) };
    

    /*#############################################*/

    sf::RenderWindow window(sf::VideoMode(1000, 800), "A* Pathfinding");

    sf::RectangleShape s_Button;
    s_Button.setSize(sf::Vector2f(120, 50));
    s_Button.setPosition(CELL_SIZE * GRID_SIZE + 40, 20);
    s_Button.setFillColor(sf::Color::Red);
    
    sf::RectangleShape r_Button;
    r_Button.setSize(sf::Vector2f(120, 50));
    r_Button.setPosition(CELL_SIZE * GRID_SIZE + 40, 100);
    r_Button.setFillColor(sf::Color::Red);

    bool draw_grid = false;
    std::vector<Node> path;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && s_Button.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) 
                {
                    Timer T;
                    path = A_star(start, goal, grid);
                    std::cout << "Time elapsed in full program: " << T.elapsed() << " seconds" << std::endl;

                    if (path.empty()) {
                        std::cout << "No path found." << std::endl;
                    }
             
                    draw_grid = true;
                }

                if (event.mouseButton.button == sf::Mouse::Left && r_Button.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                {
                    grid = randomize_grid(GRID_SIZE, 20);
                    draw_grid = false;
                }
            }
        }

        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {

                sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                rect.setPosition(i * CELL_SIZE, j * CELL_SIZE);

                if (grid[i][j] == 1) {
                    rect.setFillColor(sf::Color::Black);
                }

                window.draw(rect);
            }
        }

        if (draw_grid)
        {
            for (Node node : path) {
                sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                rect.setPosition(node.x * CELL_SIZE, node.y * CELL_SIZE);
                rect.setFillColor(sf::Color::Red);
                window.draw(rect);
            }

        }

        window.draw(s_Button);
        window.draw(r_Button);

        window.display();
    }

    return 0;
}
