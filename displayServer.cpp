//
//  displayServer.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Copyright © 2019 Tarek Abdelrahman. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <valarray>
using namespace std;
using namespace sf;

#include "tictactoe.h"
#include "gameState.h"

// Function prototype for playMove
void playMove(gameState&);

// The display server function
int displayServer() {

    /************************************************************************************************************/
    /* Insert code that loads the various images used by the game and creates the sprites                       */
    /* ECE244 Student: The loading of the X image is shown. Repreat for the rest of the images                  */
    /************************************************************************************************************/

    // Get the X image
    sf::Texture X_texture;
    if (!X_texture.loadFromFile("/share/copy/ece244f/lab2/data/X.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite X_sprite(X_texture);
    
    // Get the O image
    sf::Texture O_texture;
    if (!X_texture.loadFromFile("/share/copy/ece244f/lab2/data/O.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite O_sprite(O_texture);
    
    // Get the blank image
    sf::Texture B_texture;
    if (!X_texture.loadFromFile("/share/copy/ece244f/lab2/data/B.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite B_sprite(B_texture);
    
    
    // First, we find the sizes of the images so we can determine the size of the window we must create
    // The images (X, O and Black) are assumed to be square are are all of the same size
    // Thus, we just find the size of one of them
    
    // The tile size is the size of the images
    const int tileSize = X_texture.getSize().x;
    
    // The cell borders (thick lines) are rectangles
    // The size of these rectangles is 1/20th of the size of the tile by 3 
    const int barWidth = tileSize/20;
    const int barHeight = boardSize*tileSize + (boardSize-1)*barWidth;
    
    // The size of the window in pixels can now be calculated
    const int windowSize = boardSize*tileSize + (boardSize-1)*barWidth;
    std::cout << windowSize << std::endl;
    // Create the main window: it has a title bar and a close button, but is not resizable
    // ECE244 Student: you should replace ECE244 in the title of the window by your login ID
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Tic-Tac_Toe (sunlingw Display Server)", sf::Style::Titlebar | sf::Style::Close);

    // Set the Icon that appears in the task bar when the window is minimized
    // ECE244 Student: add your code here
    
    sf::Image myFirstWindowIcon;
    if (!myFirstWindowIcon.loadFromFile("/share/copy/ece244f/lab2/data/icon.jpg")){
        return EXIT_FAILURE;
    }
    window.setIcon(myFirstWindowIcon.getSize().x, myFirstWindowIcon.getSize().y, myFirstWindowIcon.getPixelsPtr());
    

    // Create the horizonal (vertical) borders as rectangles of sizes barWidth and barHeight (berHeight and barWidth)
    // ECE244 Student: insert your code here
    
    //load the blank turn on to specific position
    sf::Texture bTexture;
    if (!bTexture.loadFromFile("/share/copy/ece244f/lab2/data/B.jpg")){
        return EXIT_FAILURE;
    }
    sf::Sprite bSprite1(bTexture);
    sf::Sprite bSprite2(bTexture);
    sf::Sprite bSprite3(bTexture);
    sf::Sprite bSprite4(bTexture);
    sf::Sprite bSprite5(bTexture);
    sf::Sprite bSprite6(bTexture);
    sf::Sprite bSprite7(bTexture);
    sf::Sprite bSprite8(bTexture);
    sf::Sprite bSprite9(bTexture);
    //set the position
    bSprite1.setPosition(0,0);
    bSprite2.setPosition(tileSize+barWidth,tileSize+barWidth);
    bSprite3.setPosition(0,tileSize+barWidth);
    bSprite4.setPosition(0,barHeight-tileSize);
    bSprite5.setPosition(barHeight-tileSize,0);
    bSprite6.setPosition(tileSize+barWidth,0);
    bSprite7.setPosition(tileSize+barWidth,barHeight-tileSize);
    bSprite8.setPosition(barHeight-tileSize,tileSize+barWidth);
    bSprite9.setPosition(barHeight-tileSize,barHeight-tileSize);
    //Draw the image    
    window.draw(bSprite1);
    window.draw(bSprite2);
    window.draw(bSprite3);
    window.draw(bSprite4);
    window.draw(bSprite5);
    window.draw(bSprite6);
    window.draw(bSprite7);
    window.draw(bSprite8);
    window.draw(bSprite9);
    
    //Now actually update the display window
    //window.display();
    
    //the borders
    //create the rectangle shape for the x border
    sf::RectangleShape myX1Border(sf::Vector2f(barHeight,barWidth));
    sf::RectangleShape myX2Border(sf::Vector2f(barHeight,barWidth));  
    //create the rectangle shape for the y border
    sf::RectangleShape myY1Border(sf::Vector2f(barWidth,barHeight));
    sf::RectangleShape myY2Border(sf::Vector2f(barWidth,barHeight));    
    //set the position for x and y borders
    myX1Border.setPosition(0,tileSize);
    myX2Border.setPosition(0,barHeight-tileSize-barWidth);
    myY1Border.setPosition(tileSize,0);
    myY2Border.setPosition(barHeight-tileSize-barWidth,0);   
    //set the color for the four border
    myX1Border.setFillColor(sf::Color(255,165,0));
    myX2Border.setFillColor(sf::Color(255,165,0));
    myY1Border.setFillColor(sf::Color(255,165,0));
    myY2Border.setFillColor(sf::Color(255,165,0));   
    // draw the four border
    window.draw(myX1Border);
    window.draw(myX2Border);
    window.draw(myY1Border);
    window.draw(myY2Border);
    
    window.display();
    
    /************************************************************************************************************/
    /* Create and initialize the game state object                                                              */
    /************************************************************************************************************/
    gameState game_state;

    game_state.set_clickedRow(0);
    game_state.set_clickedColumn(0);
    game_state.set_moveValid(true); // This must start out as true
    game_state.set_gameOver(false);
    game_state.set_winCode(0);
    game_state.set_turn(true);  // X always plays first
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            game_state.set_gameBoard(i,j,Empty);
        }
    }
    
    /************************************************************************************************************/
    /* This is the main event loop of the code                                                                  */
    /************************************************************************************************************/
    
    // Start the game loop that runs as long as the window is open
    while (window.isOpen()) {
        
        int xp, yp;
        // The event
        sf::Event event;
        bool has_event = false;
        // Process the events
        while (window.pollEvent(event)) {
                        
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            // Left mouse button pressed: get the click position and update the game
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !game_state.get_gameOver()) {
                // left mouse button is pressed: get the coordinates in pixels
                // ECE244 Student: Insert your code to get the coordinates here             
            
                // left mouse button is pressed
                // get the coordinates in pixels
                sf::Vector2i localPosition=Mouse::getPosition(window);
                //get the x,y ordinates
                int xPosition = localPosition.x;
                int yPosition = localPosition.y;
               
                // Convert the pixel coordinates into game board rows and columns
                // Just divide by tileSize
                // Observe that the x axis is the rows and the y axis is the columns
                // Also make sure that row and column values are valid
                // ECE244 Student: Insert your code below
                int  xs, ys;
                //the position is (0,0)
                if ((0<=xPosition && xPosition<=tileSize) && (0<=yPosition && yPosition<=tileSize)){
                    xp=0;
                    yp=0;
                    xs=0;
                    ys=0;
                }
                //position is (tileSize+barWidth,0)
                if ((tileSize+barWidth<=xPosition && xPosition<=tileSize+barWidth+tileSize) && (0<=yPosition && yPosition<=tileSize)){
                    xp=tileSize+barWidth;
                    yp=0;
                    xs=1;
                    ys=0;
                }
                //position is (barHeight-tileSize,0)
                if ((barHeight-tileSize<=xPosition && xPosition<=barHeight) && (0<=yPosition && yPosition<=tileSize)){
                    xp=barHeight-tileSize;
                    yp=0;
                    xs=2;
                    ys=0;
                }
                // position is(0,tileSize+barWidth)
                if ((0<=xPosition && xPosition<=tileSize) && (tileSize+barWidth<=yPosition && yPosition<=tileSize+barWidth+tileSize)){
                    xp=0;
                    yp=tileSize+barWidth;
                    xs=0;
                    ys=1;
                }
                //position is (0,barHeight-tileSize)
                if ((0<=xPosition && xPosition<=tileSize) && (barHeight-tileSize<=yPosition && yPosition<=barHeight)){
                    xp=0;
                    yp=barHeight-tileSize;
                    xs=0;
                    ys=2;
                }
                //position is (tileSize+barWidth,tileSize+barWidth)
                if ((tileSize+barWidth<=xPosition && xPosition<=tileSize+barWidth+tileSize) && (tileSize+barWidth<=yPosition && yPosition<=tileSize+barWidth+tileSize)){
                    xp=tileSize+barWidth;
                    yp=tileSize+barWidth;
                    xs=1;
                    ys=1;
                    
                }  
                //position is (tileSize+barWidth,barHeight-tileSize)
                if ((tileSize+barWidth<=xPosition && xPosition<=tileSize+barWidth+tileSize) && (tileSize+barWidth+tileSize<=yPosition && yPosition<=barHeight)){
                    xp=tileSize+barWidth;
                    yp=barHeight-tileSize;
                    xs=1;
                    ys=2;
                }
                //position is (barHeight-tileSize,tileSize+barWidth)
                if ((tileSize+barWidth+tileSize<=xPosition && xPosition<=barHeight) && (tileSize+barWidth<=yPosition && yPosition<=tileSize+barWidth+tileSize)){
                    xp=barHeight-tileSize;
                    yp=tileSize+barWidth;
                    xs=2;
                    ys=1;
                }
                //position is (barHeight-tileSize,barHeight-tileSize)
                if ((barHeight-tileSize<=xPosition && xPosition<=barHeight) && (barHeight-tileSize<=yPosition && yPosition<=barHeight)){
                    xp=barHeight-tileSize;
                    yp=barHeight-tileSize;
                    xs=2;
                    ys=2;
                }                
                // Update the game state object with the coordinates
                // ECE244 Student: insert code to update the object game_state here                
                game_state.set_clickedRow(ys);
                game_state.set_clickedColumn(xs);  
                // Update the game with the new move
                // ECE244 Student: invoke the playMove function here
                playMove(game_state);
                has_event = true; 
                //save all the cases
                bool turn;
                int value;
                turn=game_state.get_turn();
                //X case
                if (turn==!true){
                    value=X;
                } 
                //O case
                if (turn==!false){
                    value=O;
                }                    
                game_state.set_gameBoard(ys, xs , value);
            }
        }
        
        if (!game_state.get_moveValid()) continue;
                
        // Insert code to draw the tiles using the sprites created earlier        
        // You must determine the position of each cell on the grid, taking into account the width of
        // the border and then position the sprite there and draw it.
        // Draw the entire board, cell borders included,
        // reflecting any move that has just happened (check the gameBoard array)
        // Further, if the game is over and one player wins, you must create and draw a rectangle of
        // windowSize width and 10 pixels height to indicate the winning marks
        // The fill of this rectangle should be white

        // ECE244 Student: insert your code here
        
        
        
        // If the move is invalid, go to next event
        if (has_event==true && game_state.get_moveValid()) {
            // redraw the four border
            window.draw(myX1Border);
            window.draw(myX2Border);
            window.draw(myY1Border);
            window.draw(myY2Border);
            //reDraw the image    
            window.draw(bSprite1);
            window.draw(bSprite2);
            window.draw(bSprite3);
            window.draw(bSprite4);
            window.draw(bSprite5);
            window.draw(bSprite6);
            window.draw(bSprite7);
            window.draw(bSprite8);
            window.draw(bSprite9);
            
            //display all previous cases
            for (int i=0;i<=2; i+=1){
                for (int j=0; j<=2; j+=1){
                    if (game_state.get_gameBoard(i, j)==X){
                        sf::Texture x1Texture;
                        if (!x1Texture.loadFromFile("/share/copy/ece244f/lab2/data/X.jpg")){
                            return EXIT_FAILURE;
                        }
                        sf::Sprite x1Sprite(x1Texture);
                        x1Sprite.setPosition(j*(tileSize+barWidth),i*(tileSize+barWidth));
                        window.draw(x1Sprite);
                    }
                    if (game_state.get_gameBoard(i, j)==O){
                        sf::Texture o1Texture;
                        if (!o1Texture.loadFromFile("/share/copy/ece244f/lab2/data/O.jpg")){
                            return EXIT_FAILURE;
                        }
                        sf::Sprite o1Sprite(o1Texture);
                        o1Sprite.setPosition(j*(tileSize+barWidth),i*(tileSize+barWidth));
                        window.draw(o1Sprite);   
                    }
                }
            }
            

            //to determine is "0" or "X" should be displayed
            // X case
            if (game_state.get_turn()==!true){
                sf::Texture xTexture;
                if (!xTexture.loadFromFile("/share/copy/ece244f/lab2/data/X.jpg")){
                    return EXIT_FAILURE;
                }
                sf::Sprite xSprite(xTexture);
                xSprite.setPosition(xp,yp);
                window.draw(xSprite);
            }
            // O case
            else{
                sf::Texture oTexture;
                if (!oTexture.loadFromFile("/share/copy/ece244f/lab2/data/O.jpg")){
                    return EXIT_FAILURE;
                }
                sf::Sprite oSprite(oTexture);
                oSprite.setPosition(xp,yp);
                window.draw(oSprite);  
            }
            
        //to determine if there is a game over case happened
        //wincode if is 1
        if (game_state.get_winCode() == 1) {
            sf::RectangleShape line(sf::Vector2f(2 * barHeight, 10));
            line.setFillColor(sf::Color::White);
            line.setPosition(0, tileSize / 2);
            window.draw(line);    
        }
        //wincode if is 2
        if (game_state.get_winCode() == 2) {
            sf::RectangleShape line(sf::Vector2f(2 * barHeight, 10));
            line.setFillColor(sf::Color::White);
            line.setPosition(0, tileSize / 2 + (tileSize + barWidth));
            window.draw(line);     
        }
        //wincode if is 3
        if (game_state.get_winCode() == 3) {
            sf::RectangleShape line(sf::Vector2f(2 * barHeight, 10));
            line.setFillColor(sf::Color::White);
            line.setPosition(0, tileSize / 2 + 2 * (tileSize + barWidth));
            window.draw(line);    
        }
        //wincode if is 4
        if (game_state.get_winCode() == 4) {
            sf::RectangleShape line(sf::Vector2f(2 * barHeight, 10));
            line.setFillColor(sf::Color::White);
            line.rotate(90);
            line.setPosition(tileSize / 2, 0);
            window.draw(line);  
        }
        //wincode if is 5
        if (game_state.get_winCode() == 5) {
            sf::RectangleShape line(sf::Vector2f(2 * barHeight, 10));
            line.setFillColor(sf::Color::White);
            line.rotate(90);
            line.setPosition(tileSize / 2 + (tileSize + barWidth), 0);
            window.draw(line);      
        }
        //wincode if is 6
        if (game_state.get_winCode() == 6) {
            sf::RectangleShape line(sf::Vector2f(2 * barHeight, 10));
            line.setFillColor(sf::Color::White);
            line.rotate(90);
            line.setPosition(tileSize / 2 + 2 * (tileSize + barWidth), 0);
            window.draw(line);
        }
        //wincode if is 7
        if (game_state.get_winCode() == 7) {
            sf::RectangleShape line(sf::Vector2f(2 * barHeight, 10));
            line.setFillColor(sf::Color::White);
            line.rotate(45);
            window.draw(line);
        }
        //wincode if is 8
        if (game_state.get_winCode() == 8) {
            sf::RectangleShape line(sf::Vector2f(2 * barHeight, 10));
            line.setFillColor(sf::Color::White);
            line.rotate(135);
            line.setPosition(3 * tileSize + 2 * barWidth, 0);
            window.draw(line);
        }
        
            
        // Display to the window
        window.display();
        }
                

    }
    
    return EXIT_SUCCESS;
}

