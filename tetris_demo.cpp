#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "tetris_demo.h"

using namespace std;
using namespace cv;




/*
std::pair<vector<vector<cv::Point>>, cv::Scalar> convertToExpectedType(const std::pair<std::vector<cv::Point, std::allocator<cv::Point>>, cv::Scalar>& value) {
    std::pair<vector<vector<cv::Point>>, cv::Scalar> convertedValue;
    vector<vector<cv::Point>> convertedCoords(value.first.size());


    for (size_t i = 0; i < value.first.size(); i++) {
        for (auto& point : value.first) {
            convertedCoords.push_back(cv::Point(point.x, point.y));
        }
    }

    convertedValue.first = convertedCoords;

    convertedValue.second = value.second;

    return convertedValue;
};
*/
/*
vector<vector<cv::Point>> matToPoints(const cv::Mat& mat) {
    vector<vector<cv::Point>> points;
    int rows = mat.rows;
    int cols = mat.cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cv::Point point(j, i); // column index is x, row index is y
            points.push_back(point);
        }
    }

    return points;
};
*/


class TetrisPieceInfo {
private:
    vector<vector<cv::Point>> coords_tetris;
    cv::Scalar color;

public:

    vector<Point> makeblock(vector<Point> points, int x1, int x2, int y1, int y2)
    {

        int MinX = min(x1, x2);
        int MaxX = max(x1, x2);
        int MinY = min(y1, y2);
        int MaxY = max(y1, y2);
        try
        {
            for (int i = MinY; i < MaxY; i++)
                {
                    for (int j = MinX; j < MaxX; j++)
                    {
                        points.push_back(cv::Point(i, j));
                    }
                }
        }
        catch (const std::exception& e) {
            std::cout << "Исключение: " << e.what() << std::endl;
        }
        

        return points;
    }

    
    std::pair<vector<vector<cv::Point>>, cv::Scalar> get_info(std::string piece) {
        cv::Scalar color;
        int x1, x2, x3, x4, x5, y1, y2, y3, y4, y5;
        vector<vector<cv::Point>> blocks;
        vector<Point> block1, block2, block3, block4;

        if (piece == "I") {
            x1 = x3 = x5 = 0; 
            x2 = x4 = 20;
            y1 = 0;
            y2 = 20;
            y3 = 40;
            y4 = 60;
            y5 = 80;
            block1 = makeblock(block1, x1, x2, y1, y2);
            block2 = makeblock(block2, x2, x3, y2, y3);
            block3 = makeblock(block3, x3, x4, y3, y4);
            block4 = makeblock(block4, x4, x5, y4, y5);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(255, 155, 15);
        }
        else if (piece == "T") {
            x1 = x3 = 20;
            x2 = x5 = 40;
            x4 = 0;
            y1 = 0;
            y2 = y4 = 20;
            y3 = 40;
            y5 = 60;
            block1 = makeblock(block1, x1, x2, y1, y2);
            block2 = makeblock(block2, x2, x3, y2, y3);
            block3 = makeblock(block3, x3, x4, y3, y4);
            block4 = makeblock(block4, x3, x5, y3, y5);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(138, 41, 175);
        }
        else if (piece == "L") {
            x1 = x4 = 0;
            x2 = x5 = 20;
            x3 = 40;
            y1 = y3 = 0;
            y2 = 20;
            y4 = 40;
            y5 = 60;
            block1 = makeblock(block1, x1, x2, y1, y2);
            block2 = makeblock(block2, x2, x3, y2, y3);
            block3 = makeblock(block3, x2, x4, y2, y4);
            block4 = makeblock(block4, x4, x5, y4, y5);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(2, 91, 227);
        }
        else if (piece == "J") {
            x1 = 0;
            x2 = x5 = 20;
            x3 = x4 = 40;
            y1 = y3 = 0;
            y2 = 20;
            y4 = 40;
            y5 = 60;
            block1 = makeblock(block1, x1, x2, y1, y2);
            block2 = makeblock(block2, x2, x3, y2, y3);
            block3 = makeblock(block3, x2, x4, y2, y4);
            block4 = makeblock(block4, x4, x5, y4, y5);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(198, 65, 33);
        }
        else if (piece == "S") {
            x1 = 0;
            x2 = 20;
            x3 = x4 = 40;
            x5 = 60;
            y1 = y3 = 0;
            y2 = y5 = 20;
            y4 = 40;

            block1 = makeblock(block1, x1, x2, y1, y2);
            block2 = makeblock(block2, x2, x3, y2, y3);
            block3 = makeblock(block3, x2, x4, y2, y4);
            block4 = makeblock(block4, x4, x5, y4, y5);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(55, 15, 215);
        }
        else if (piece == "Z") {
            x1 = 60;
            x2 = 40;
            x3 = x4 = 20;
            x5 = 0;
            y1 = y3 = 0;
            y2 = y5 = 20;
            y4 = 40;


            block1 = makeblock(block1, x1, x2, y1, y2);
            block2 = makeblock(block2, x2, x3, y2, y3);
            block3 = makeblock(block3, x2, x4, y2, y4);
            block4 = makeblock(block4, x4, x5, y4, y5);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(1, 177, 89);
        }
        else {
            x1 = x4 = 0;
            x2 = 20;
            x3 = x5 = 40;
            y1 = y3 = 0;
            y2 = 20;
            y4 = y5 = 40;


            block1 = makeblock(block1, x1, x2, y1, y2);
            block2 = makeblock(block2, x2, x3, y2, y3);
            block3 = makeblock(block3, x2, x4, y2, y4);
            block4 = makeblock(block4, x2, x5, y2, y5);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(2, 159, 227);
        }

        for (size_t i = 0; i < blocks.size(); i++)
        {
            for (size_t j = 0; j < blocks[i].size(); j++)
            {
                blocks[i][j].x += 20;
                blocks[i][j].y += 20;

            }
        }

        return std::make_pair(blocks, color);
    };
};

vector<vector<cv::Point>> rotateMatrix90DegreesClockwise(vector<vector<cv::Point>> matrix) {
    vector<vector<cv::Point>> rotatedMatrix(matrix[0].size(), vector<cv::Point>(matrix.size()));

    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            rotatedMatrix[j][matrix.size() - 1 - i] = matrix[i][j];
        }
    }
    try {
        matrix = rotatedMatrix;
    }
    catch (const std::exception& e) {
        std::cout << "Исключение: " << e.what() << std::endl;
    }
    return matrix;
    
};
vector<vector<cv::Point>> rotateMatrix90DegreesCounterClockwise(vector<vector<cv::Point>> matrix) {
    vector<vector<cv::Point>> rotatedMatrix(matrix[0].size(), vector<cv::Point>(matrix.size()));

    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            rotatedMatrix[matrix[i].size() - 1 - j][i] = matrix[i][j];
        }
    }
    try {
        matrix = rotatedMatrix;
    }
    catch (const std::exception& e) {
        std::cout << "Исключение: " << e.what() << std::endl;
    }
    return matrix;
};






int display(cv::Mat& board, const vector<vector<cv::Point>>& coords_tetris, const cv::Scalar& color,
    const std::pair<vector<vector<cv::Point>>, cv::Scalar>& next_info,
    const std::pair<vector<vector<cv::Point>>, cv::Scalar>& held_info, int score, int SPEED) {
    // Generate the display

    // Create a border for the game board
    cv::Mat border = cv::Mat::zeros(400, 10, CV_8UC3) + cv::Scalar(127, 127, 127);
    cv::Mat border_ = cv::Mat::zeros(10, 400, CV_8UC3) + cv::Scalar(127, 127, 127);

    // Create a copy of the game board with the current tetris piece

    
    cv::Mat dummy = board.clone();
    /*for (const auto& coord : next_info.first) {
        for (auto& point : coord)
        {
            dummy.at<cv::Vec3b>(point) = cv::Vec3b(next_info.second[0], next_info.second[1], next_info.second[2]);
        }

    }*/

    for (int i = 0; i < board.cols; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            board.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
        }
    }

  
    for (const auto& coord : coords_tetris) {
        for (const auto& point : coord) {

            board.at<cv::Vec3b>(point.y-20, point.x) = cv::Vec3b(0, 0, 0); // Set to the background color (e.g., black)
        }
    }

    // Draw the shape on the board
    for (const auto& coord : coords_tetris) {
        for (const auto& point : coord) {
            board.at<cv::Vec3b>(point.y, point.x) = cv::Vec3b(color[0], color[1], color[2]); // Set to the desired color
        }
    }

    // Create a display for the next piece and held piece
    cv::Mat right = cv::Mat::zeros(400, 200, CV_8UC3);
    

    cv::Mat left = cv::Mat::zeros(400, 200, CV_8UC3);
    for (const auto& coord : held_info.first) {
        for (auto& point : coord)
        {
            left.at<cv::Vec3b>(point) = cv::Vec3b(held_info.second[0], held_info.second[1], held_info.second[2]);
        }
    }

    // Concatenate all the display elements


    cv::Mat matArray[] = { border, left, border };

    try {
        cv::hconcat(matArray, 3, dummy);
        cv::hconcat(dummy, board, dummy);
        cv::hconcat(dummy, border, dummy);
        cv::hconcat(dummy, right, dummy);
        cv::hconcat(dummy, border, dummy);
        // Convert the type of border_ to match dummy
        cv::Mat convertedBorder;
        border_.convertTo(convertedBorder, dummy.type());

        // Resize border_ to have the same number of columns as dummy
        cv::resize(convertedBorder, convertedBorder, cv::Size(dummy.cols, convertedBorder.rows));

        cv::vconcat(convertedBorder, dummy, dummy);

        cv::repeat(border_, dummy.rows / border_.rows, 1); // Fix the repeat function usage

        cv::Size borderSize(dummy.cols, 10); // Define the size of the border
        cv::Scalar borderColor(127, 127, 127); // Define the color of the border
        cv::Mat border = cv::Mat::zeros(borderSize, CV_8UC3) + borderColor;
        cv::vconcat(dummy, border, dummy);
    }
    catch (const std::exception& e) {
        std::cout << "Исключение: " << e.what() << std::endl;
    }

    // Add the score text to the display
    cv::putText(dummy, "Score:", cv::Point(450, 200), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 240, 255));
    cv::putText(dummy, std::to_string(score), cv::Point(550, 200), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 255, 0), 2);

    // Add instructions for the player
    cv::putText(dummy, "A - move left", cv::Point(25, 150), cv::FONT_HERSHEY_DUPLEX, 0.6, cv::Scalar(0, 240, 255));
    cv::putText(dummy, "D - move right", cv::Point(25, 175), cv::FONT_HERSHEY_DUPLEX, 0.6, cv::Scalar(0, 240, 255));
    cv::putText(dummy, "S - move down", cv::Point(25, 200), cv::FONT_HERSHEY_DUPLEX, 0.6, cv::Scalar(0, 240, 255));
    cv::putText(dummy, "J - rotate left", cv::Point(25, 225), cv::FONT_HERSHEY_DUPLEX, 0.6, cv::Scalar(0, 240, 255));
    cv::putText(dummy, "L - rotate right", cv::Point(25, 250), cv::FONT_HERSHEY_DUPLEX, 0.6, cv::Scalar(0, 240, 255));

    // Display the generated image
    cv::imshow("Tetris", dummy);

    // Wait for user input and return the key pressed
    int key = cv::waitKey(1000 / SPEED);
    return key;
};



    int main() {
        srand(time(0));
        vector<string> tetris_pieces = { "O", "I", "S", "Z", "L", "J", "T" };
        string next_piece = tetris_pieces[rand()%7];

        string current_piece = "";
        int SPEED = 1;
        cv::Mat board = cv::Mat::zeros(400, 200, CV_8UC3);
        bool count = 0;
        bool quit = false;
        bool place = false;
        bool drop = false;
        bool switcher = false;
        std::string held_piece = "";
        int flag = 0;
        int score = 0;
        TetrisPieceInfo tetris_info;
        std::vector< vector<cv::Point>> arr;
        vector<cv::Point> pov;
        vector<vector<cv::Point>> dummy;
        std::pair<vector<vector<cv::Point>>, cv::Scalar> next_info = tetris_info.get_info(next_piece);

        while (!quit) 
        {
            bool restingOnSomething = false;
            // Check if user wants to swap held and current pieces
            std::pair<vector<vector<cv::Point>>, cv::Scalar> held_info;
            current_piece = next_piece;
            int random_index = rand() % 7;
            next_piece = tetris_pieces[random_index];
            

            
            
            
            //std::pair<vector<vector<cv::Point>>, cv::Scalar> current_info = tetris_info.get_info(current_piece);
            vector<vector<cv::Point>> coords = next_info.first;
            cv::Scalar color = next_info.second;
            std::vector<int> top_left;
            if (current_piece == "I") 
            {
                top_left = { -20, 40 };
            }

            int maxY = coords[0][0].y;
            for (int i = 0; i < coords.size(); i++)
            {
                for (int j = 0; j < coords[i].size(); j++)
                {
                    Point point = coords[i][j];
                    maxY = std::max(maxY, point.y);
                }
            }
            int maxBoard;
            if (next_piece == "I" || next_piece == "L" || next_piece == "O") maxBoard = 380;
            else maxBoard = 380;
            if (maxY < maxBoard)
            {
                // Move the piece left if it isn't against the left wall
                for (int i = 0; i < next_info.first.size(); i++)
                {
                    for (int j = 0; j < next_info.first[i].size(); j++)
                    {
                       
                        //  cv::Point2i k = next_info.first[2][4];
                        if (board.at<cv::Vec3b>(next_info.first[2][4].y + 20, next_info.first[2][4].x) != cv::Vec3b(0, 0, 0)) {
                            place = true;
                        }
                        if (place)
                        {

                            restingOnSomething = true;
                            board.at<cv::Vec3b>(next_info.first[i][j]) = cv::Vec3b(color[0], color[1], color[2]);
                            int random_index = rand() % 7;
                            next_piece = tetris_pieces[random_index];
                            next_info = tetris_info.get_info(next_piece);
                            place = false;
                        }
                        else
                        {
                            next_info.first[i][j].y += 20;
                        }
                        
                    }

                }
            }
            else
            {   
                for (size_t i = 0; i < next_info.first.size(); i++)
                {
                    for (size_t j = 0; i < next_info.first[i].size(); j++)
                    { /*
                    if (board.at<cv::Vec3b>(next_info.first[i][j].y + 1, next_info.first[i][j].x) != cv::Vec3b(0, 0, 0)) {
                        place = true;
                        break;*/
                    }
                }
                restingOnSomething = true;
                
                int random_index = rand() % 7;
                next_piece = tetris_pieces[random_index];
                next_info = tetris_info.get_info(next_piece);
            }
             
            /*

            // Flatten the coords vector
            std::vector<cv::Point> flattenedCoords;
            for (size_t i = 0; i < coords.size(); i++) {
                flattenedCoords.insert(flattenedCoords.end(), coords[i].begin(), coords[i].end());
            }

            // Check if any non-zero pixels exist in the specified coordinates
            bool allZero = true;
            for (size_t i = 0; i < flattenedCoords.size(); i++)
            {
                cv::Vec3b pixel = board.at<cv::Vec3b>(flattenedCoords[i].y, flattenedCoords[i].x);
                if (pixel != cv::Vec3b(0, 0, 0)) 
                {
                    allZero = false;
                    break;
                }
            }

            if (!allZero) 
            {
                break;
            }
            */

            

            size_t numRows = coords.size(); // Get the number of rows

           // size_t numCols = coords_tetris.size(); // Get the number of columns in the first row

            int key = display(board, coords, color, next_info, held_info, score, SPEED);
            
            

            if (key == 'a') 
            {
                // Find the minimum x-coordinate
                int minX = coords[0][0].x;
                for (int i = 0; i < coords.size(); i++) 
                {
                    for (int j = 0; j < coords[i].size(); j++) 
                    {
                        Point point = coords[i][j];
                        minX = std::min(minX, point.x);
                    }
                }
                if (minX > 0)
                {
                    // Move the piece left if it isn't against the left wall
                    for (int i = 0; i < next_info.first.size(); i++)
                    {
                        for (int j = 0; j < next_info.first[i].size(); j++)
                        {
                            //  cv::Point2i k = next_info.first[2][4];

                            board.at<cv::Vec3b>(next_info.first[i][j].y-20, next_info.first[i][j].x) = cv::Vec3b(0, 0, 0); // Set to the background color (e.g., black)
                            board.at<cv::Vec3b>(next_info.first[i][j].y-20, next_info.first[i][j].x+20) = cv::Vec3b(0, 0, 0);
                            next_info.first[i][j].x -= 20;
                            
                        }

                    }
                }
                

                
            }
            if (key == 'd') 
            {
                // Find the maximum x-coordinate
                int maxX = next_info.first[0][0].x;
                for (int i = 0; i < next_info.first.size(); i++)
                {
                    for (int j = 0; j < next_info.first[i].size(); j++)
                    {
                        Point point = next_info.first[i][j];
                        maxX = std::max(maxX, point.x);
                    }
                }

                // Move the piece right if it isn't against the right wall
                if (maxX < 180)
                {
                    for (int i = 0; i < next_info.first.size(); i++)
                    {
                        for (int j = 0; j < next_info.first[i].size(); j++)
                        {
                            //  cv::Point2i k = next_info.first[2][4];
                            board.at<cv::Vec3b>(next_info.first[i][j].y - 20, next_info.first[i][j].x) = cv::Vec3b(0, 0, 0); // Set to the background color (e.g., black)
                            board.at<cv::Vec3b>(next_info.first[i][j].y - 20, next_info.first[i][j].x - 20) = cv::Vec3b(0, 0, 0);
                            next_info.first[i][j].x += 20;
                        }

                    }
                    if (current_piece == "I") {
                        top_left[1] += 20;
                    }
                }


             }   // Update the coords vector with the modified dummy vector
                
            
            
            if (key == 'j' || key == 'l') {
                // ...
                try
                {
                    if (key == 'j') {
                        next_info.first = rotateMatrix90DegreesCounterClockwise(next_info.first);
                    }
                    else {
                        next_info.first = rotateMatrix90DegreesClockwise(next_info.first);
                    }

                }
                catch (cv::Exception& e)
                {
                    std::cerr << e.msg << std::endl; // Output exception message
                }
            }

            
            if (key == 's')
            {
                score += 1;

                int maxBoard;
                maxBoard = 320;
                if (maxY < maxBoard)
                {
                    
                
                for (int i = 0; i < next_info.first.size(); i++)
                {
                    for (int j = 0; j < next_info.first[i].size(); j++)
                    {
                        //  cv::Point2i k = next_info.first[2][4];
                        if (board.at<cv::Vec3b>(next_info.first[i][0].y+40, next_info.first[i][0].x) != cv::Vec3b(0, 0, 0)) {
                            next_info.first[i][j].y += 40;
                            place = true;
                        }
                        if (place)
                        {

                            board.at<cv::Vec3b>(next_info.first[i][j]) = cv::Vec3b(color[0], color[1], color[2]);
                            int random_index = rand() % 7;
                            next_piece = tetris_pieces[random_index];
                            next_info = tetris_info.get_info(next_piece);
                            place = false;
                        }
                        else
                        {
                            board.at<cv::Vec3b>(next_info.first[i][j].y - 20, next_info.first[i][j].x) = cv::Vec3b(0, 0, 0); // Set to the background color (e.g., black)
                            board.at<cv::Vec3b>(next_info.first[i][j].y - 40, next_info.first[i][j].x) = cv::Vec3b(0, 0, 0);
                            next_info.first[i][j].y += 40;
                        }
                    }
                }
            }
            }

            if (key == 8 || key == 27) 
            {
                quit = true;
                break;
            }
            

            



            

           
            
            if (current_piece == "I") 
            {
                top_left[0] += 20;
            }
            coords = dummy;
            cv::Mat board; // assume the board is a cv::Mat object

    // count the number of non-zero elements in each row of the board
            cv::Mat rowCounts;
            rowCounts = cv::countNonZero(board);

            // count the number of rows where the count is equal to the number of columns
            int lines = 0;
            for (int line = 0; line < board.rows; line++) 
            {
                if (rowCounts.at<int>(line) == board.cols) 
                {
                    lines += 1;
                    for (int i = line; i > 0; i--) 
                    {
                        board.row(i) = board.row(i - 1);
                    }
                    board.row(0).setTo(cv::Scalar(0));
                }
            }


            if (lines == 1) {
                score += 40;
            }
            else if (lines == 2) {
                score += 100;
            }
            else if (lines == 3) {
                score += 300;
            }
            else if (lines == 4) {
                score += 1200;
            }



        }
   }
