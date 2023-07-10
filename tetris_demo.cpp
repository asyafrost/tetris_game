#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "tetris_demo.h"

using namespace std;
using namespace cv;


//показывает, если одна фигура легла на другую
bool count_figures = false;


//конец игры
void showGameOverWindow() {
    cv::Mat image(200, 450, CV_8UC3, cv::Scalar(0, 0, 0));

    cv::putText(image, "Game over!", cv::Point(50, 100), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 2);

    // Display the image in a named window
    cv::imshow("Game Over", image);

    // Wait for a key press
    cv::waitKey(0);
}

//класс тетриминошек
class TetrisPieceInfo {
private:
    vector<vector<cv::Point>> coords_tetris;
    cv::Scalar color;

public:


    //создает фигуры и их цвета
    std::pair<vector<Rect>, cv::Scalar> get_info(std::string piece, cv::Mat board) {
        cv::Scalar color;
        //фигура из блоков
        vector<cv::Rect> blocks;
        //сами блоки
        cv::Rect block1, block2, block3, block4;

        int x = 0;
        int y = 0;


        if (piece == "I") {
            //если фигура легла на другую
            
            block1 = Rect(x + 20, y + 0, 20, 20);
            block2 = Rect(40, y + 0, 20, 20);
            block3 = Rect(60, y + 0, 20, 20);
            block4 = Rect(80, 0, 20, 20);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(255, 155, 15);
        }
        else if (piece == "T") {
         
            block1 = Rect(x + 20,  0, 20, 20);
            block2 = Rect(40, 0, 20, 20);
            block3 = Rect(60, 0, 20, 20);
            block4 = Rect(40, y + 20, 20, 20);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(138, 41, 175);
        }
        else if (piece == "L") {
          

            block1 = Rect(x + 20,0, 20, 20);
            block2 = Rect(40, 0, 20, 20);
            block3 = Rect(60,0, 20, 20);
            block4 = Rect(20, y + 20, 20, 20);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(2, 91, 227);
        }
        else if (piece == "J") {


            block1 = Rect(x + 20, 0, 20, 20);
            block2 = Rect(40,  0, 20, 20);
            block3 = Rect(60, 0, 20, 20);
            block4 = Rect(60, y + 20, 20, 20);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(198, 65, 33);
        }
        else if (piece == "S") {

            

            block1 = Rect(x + 20, 20, 20, 20);
            block2 = Rect(x + 40, y + 20, 20, 20);
            block3 = Rect(x + 40, 0, 20, 20);
            block4 = Rect(x + 60, 0, 20, 20);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(55, 15, 215);
        }
        else if (piece == "Z") {

            

            block1 = Rect(x + 20, y + 0, 20, 20);
            block2 = Rect(x + 40, 0, 20, 20);
            block3 = Rect(x + 40, 20, 20, 20);
            block4 = Rect(x + 60, 20, 20, 20);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(1, 177, 89);
        }
        //квадрат, "О"
        else {

           
            block1 = Rect(20,  0, 20, 20);
            block2 = Rect(40, 0, 20, 20);
            block3 = Rect(20, 20, 20, 20);
            block4 = Rect(40, 20, 20, 20);

            blocks = { block1, block2, block3, block4 };
            color = cv::Scalar(2, 159, 227);
        }

        //возвращаем фигуру и ее цвет
        return std::make_pair(blocks, color);
    };
};







//игровое окно
int display(cv::Mat& board, const vector<cv::Rect>& coords_tetris, const cv::Scalar& color,
    const std::pair<vector<cv::Rect>, cv::Scalar>& next_info, int score, int SPEED, bool place, bool rotate) {


    // создаем обводку
    cv::Mat border = cv::Mat::zeros(400, 20, CV_8UC3) + cv::Scalar(127, 127, 127);
    cv::Mat border_ = cv::Mat::zeros(20, 400, CV_8UC3) + cv::Scalar(127, 127, 127);


    cv::Mat dummy = board.clone();



    //фигуры отражаются на игровом поле, во время движения "путь" фигуры очищается
    for (const auto& coord : coords_tetris) {
        if (coord.y >= 20 && !place && coord.y < 400)
        {
            // блоки, находящиеся выше падающего
            cv::Rect roi(coord.x, coord.y - 20, coord.width, coord.height);
            cv::Rect roi_3(coord.x, coord.y - 40, coord.width, coord.height);
            cv::Rect roi_4(coord.x, coord.y - 60, coord.width, coord.height);


            //ДОПИСАТЬ

                        //чтобы фигура могла повернутся, ее нижние блоки должны быть ниже 60 строчек
            
            board(roi).setTo(cv::Scalar(0, 0, 0)); // Set the color of the ROI to black
            /*
            if (color != cv::Scalar(2, 159, 227))
            {
                board(roi).setTo(cv::Scalar(0, 0, 0));
            }
*/

            if (coords_tetris[0].y > 80 && color != cv::Scalar(255, 155, 15))
            {
                board(roi_3).setTo(cv::Scalar(0, 0, 0));
                board(roi_4).setTo(cv::Scalar(0, 0, 0));
            }
        }



    }
    for (const auto& coord : coords_tetris) {
        cv::rectangle(board, coord, color, -1); // Draw filled rectangle
    }


    // создаем соседние поля для инструкции и счета
    cv::Mat right = cv::Mat::zeros(400, 200, CV_8UC3);
    cv::Mat left = cv::Mat::zeros(400, 200, CV_8UC3);


    // соединяем элементы
    cv::Mat matArray[] = { border, left, border };

    try {
        //горизоньальное объединение
        cv::hconcat(matArray, 3, dummy);
        cv::hconcat(dummy, board, dummy);
        cv::hconcat(dummy, border, dummy);
        cv::hconcat(dummy, right, dummy);
        cv::hconcat(dummy, border, dummy);
        // изменяем тип рамки
        cv::Mat convertedBorder;
        border_.convertTo(convertedBorder, dummy.type());

        //меняем разиер, чтобы не возникло конфликтов
        cv::resize(convertedBorder, convertedBorder, cv::Size(dummy.cols, convertedBorder.rows));
        //вертикальное объединение
        cv::vconcat(convertedBorder, dummy, dummy);

        cv::repeat(border_, dummy.rows / border_.rows, 1); // Fix the repeat function usage

        cv::Size borderSize(dummy.cols, 20); //задаем ра
        cv::Scalar borderColor(127, 127, 127); // Define the color of the border
        cv::Mat border = cv::Mat::zeros(borderSize, CV_8UC3) + borderColor;
        cv::vconcat(dummy, border, dummy);
    }
    catch (const std::exception& e) {
        std::cout << "Исключение: " << e.what() << std::endl;
    }

    // Поле игрового счета
    cv::putText(dummy, "Score:", cv::Point(500, 200), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 240, 255));
    cv::putText(dummy, std::to_string(score), cv::Point(600, 200), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 255, 0), 2);

    // Поле инструкций
    cv::putText(dummy, "A - move left", cv::Point(25, 175), cv::FONT_HERSHEY_DUPLEX, 0.6, cv::Scalar(0, 240, 255));
    cv::putText(dummy, "D - move right", cv::Point(25, 200), cv::FONT_HERSHEY_DUPLEX, 0.6, cv::Scalar(0, 240, 255));
    cv::putText(dummy, "S - move down", cv::Point(25, 225), cv::FONT_HERSHEY_DUPLEX, 0.6, cv::Scalar(0, 240, 255));
    cv::putText(dummy, "W - rotate", cv::Point(25, 250), cv::FONT_HERSHEY_DUPLEX, 0.6, cv::Scalar(0, 240, 255));

    // отображение окна игры
    cv::imshow("Tetris", dummy);

    // задаем скорость и ждем от пользователя нажатия клавиш
    int key = cv::waitKey(500 / SPEED);
    return key;
};




int main() {
    srand(time(0));
    vector<string> tetris_pieces = { "O", "I", "S", "Z", "L", "J", "T" };
    string next_piece = tetris_pieces[rand() % 7];
    std::vector<std::pair<int, int>> fallenFigures;
    string current_piece = "";
    int SPEED = 1;
    cv::Mat board = cv::Mat::zeros(400, 200, CV_8UC3);
    bool count = 0;
    bool rotate = false;
    bool quit = false;
    bool place = false;
    std::string held_piece = "";
    int score = 0;
    TetrisPieceInfo tetris_info;
    //создание первой тетриминошки
    std::pair<vector<cv::Rect>, cv::Scalar> next_info = tetris_info.get_info(next_piece, board);

    //пока игра не окончена или не прервана пользователем
    while (!quit)
    {
        
        bool restingOnSomething = false;

        current_piece = next_piece;
        //блоки текущей фигуры
        vector<Rect> coords = next_info.first;
        cv::Scalar color = next_info.second;

        //находим максимальную координату блоков по y
        int maxY = coords[0].y;
        for (int i = 0; i < coords.size(); i++)
        {
            maxY = std::max(maxY, coords[i].y);

        }
        maxY += 20;
        //граница по у
        int maxBoard = 400;
        //вектор нижних блоков, которые будут касаться нижней границы и других фигур
        vector<int> count;
        for (int i = 0; i < next_info.first.size(); i++)
        {

            if (next_info.first[0].y < 60) rotate = false;
            //если нижняя граница блока пуста, запоминаем его индекс

            if (board.at<cv::Vec3b>(next_info.first[i].y + 20, next_info.first[i].x) == cv::Vec3b(0, 0, 0))
            {
                count.emplace_back(i);
            }


        }
        
        if (maxY < maxBoard)
        {
            bool allXTouch = false;
            // пока нижняя координата фигуры в пределах поля, перемещаем ее вниз
            for (int i = 0; i < 4; i++)
            {
                  //проходимся по нижним блокам
                for (int j = 0; j < count.size(); j++)
                {
                    int k = count[j];
                    //если ниже несущего блока что-то есть, размещаем его на нем
                    int count_x = 0;
                    //проверяем, что ниже несущих блоков что-то есть
                    if (board.at<cv::Vec3b>(next_info.first[k].y + 20, next_info.first[k].x + 10) != cv::Vec3b(0, 0, 0))
                    {
                         // проходимся по всем x нижней строки блока
                        for (int x = next_info.first[i].x; x < next_info.first[i].x + next_info.first[i].width; x++)
                        {
                            // проверяем, чтобы все х в нижней строке блока касались препятствия
                            if (board.at<cv::Vec3b>(next_info.first[i].y + 20, x) != cv::Vec3b(0, 0, 0))
                            {
                                count_x++;
                            }
                        }
                        if (count_x >= 10)
                        {
                            allXTouch = true;
                        }

                        if (allXTouch)
                        {
                            
                            for (int k = 0; k < 4; k++)
                            {
                                
                                fallenFigures.push_back(std::make_pair(next_info.first[k].x, next_info.first[k].y + 20));
                                board.at<cv::Vec3b>(next_info.first[k].y + 20, next_info.first[k].x) = cv::Vec3b(color[0], color[1], color[2]);
                                
                            }
                            place = true;
                        }
                    }


                }

                //что происходит при размещении фигуры

                if (place)
                {
                    //обратно меняется скорость
                    SPEED = 1;
                    if (rotate)
                    {
                        next_info.first[i].y += 20;
                   }
                    
                    //идет проверка загятости верхних строк
                    bool isNotEmpty = false;
                    for (int i = 0; i < 20; i++)
                    {
                        bool rowNotEmpty = false;
                        for (int j = 0; j < board.cols; j++) {
                            if (board.at<cv::Vec3b>(i, j) != cv::Vec3b(0, 0, 0))
                            {
                                rowNotEmpty = true;
                                break;
                            }
                        }
                        if (rowNotEmpty)
                        {
                            isNotEmpty = true;
                            break;
                        }
                    }
                    //если строки заняты, игра завершается
                    if (isNotEmpty)
                    {
                        cv::putText(board, "Game over!", cv::Point(1000, 200), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 255));
                        quit = true;
                    }
                    //если нет - меняем фигуру
                    else
                    {

                        for (const auto& fallenFigure : fallenFigures)
                        {
                            if (next_info.first[i].x == fallenFigure.first && next_info.first[i].y == fallenFigure.second)
                            {
                                count_figures = true;
                                break;
                            }
                        }


                        //добавляем фигуру к игровому полю
              //        board.at<cv::Vec3b>(next_info.first[i].y, next_info.first[i].x) = cv::Vec3b(color[0], color[1], color[2]);

                        //создаем новую фигуру
                        int random_index = rand() % 7;
                        next_piece = tetris_pieces[random_index];
                        //обновляем place
                        place = false;
                        std::this_thread::sleep_for(std::chrono::milliseconds(3)); 
                        //обновляем состояние поворота фигуры
                        rotate = false;
                        next_info.first[0].x = next_info.first[0].y = 0;
                        next_info.first[1].x = next_info.first[1].y = 0;
                        next_info.first[2].x = next_info.first[2].y = 0;
                        next_info.first[3].x = next_info.first[3].y = 0;
                        next_info = tetris_info.get_info(next_piece, board);

                    }

                }
                else
                {
                    //движение вниз
                    next_info.first[i].y += 20;
                    
                }

            }
        }
        else  //если фигура дошла до конца, задаем новую фигуру
        {
            
            SPEED = 1;
            count_figures = false;
            restingOnSomething = true;
            int random_index = rand() % 7;
            next_piece = tetris_pieces[random_index];
            next_info.first[0].x = next_info.first[0].y = 0;
            next_info.first[1].x = next_info.first[1].y = 0;
            next_info.first[2].x = next_info.first[2].y = 0;
            next_info.first[3].x = next_info.first[3].y = 0;
            next_info = tetris_info.get_info(next_piece, board);
        }



        int key = display(board, coords, color, next_info, score, SPEED, place, rotate);

        //находим минимальные и максимальные координаты фигуры
        int minX = coords[0].x;
        for (int i = 0; i < next_info.first.size(); i++)
        {
            Rect point = next_info.first[i];
            minX = std::min(minX, point.x);

        }
        int maxX = coords[0].x;
        for (int i = 0; i < next_info.first.size(); i++)
        {
            Rect point = next_info.first[i];
            maxX = std::max(maxX, point.x);

        }
        maxX += 20;
        //движение влево, если минимальный х не выходит за левую границу
        if (key == 'a')
        {
            if (minX > 0)
            {
                for (int i = 0; i < next_info.first.size(); i++)
                {
                    next_info.first[i].x -= 20;
                    if (minX >= 0 && maxX <= 200)
                    {
                        //очищаем старые координаты от цвета
                        cv::Rect roi_1(next_info.first[i].x + 20, next_info.first[i].y - 20, next_info.first[i].width, next_info.first[i].height);
                        cv::Rect roi_2(next_info.first[i].x + 20, next_info.first[i].y, next_info.first[i].width, next_info.first[i].height);
                        board(roi_1).setTo(cv::Scalar(0, 0, 0));
                        board(roi_2).setTo(cv::Scalar(0, 0, 0));
                    }
                }
            }

        }
        if (key == 'd')
        {
            // движение вправо, если максимальный x не выходит за правую границу
            if (maxX < 200)
            {
                for (int i = 0; i < next_info.first.size(); i++)
                {
                    next_info.first[i].x += 20;
                    if (minX >= 0 && maxX <= 200)
                    {
                        cv::Rect roi_2(next_info.first[i].x - 20, next_info.first[i].y - 20, next_info.first[i].width, next_info.first[i].height);
                        cv::Rect roi_3(next_info.first[i].x - 20, next_info.first[i].y, next_info.first[i].width, next_info.first[i].height);
                        board(roi_2).setTo(cv::Scalar(0, 0, 0));
                        board(roi_3).setTo(cv::Scalar(0, 0, 0));
                    }
                }
            }
        }


        //поворот
        if (key == 'w') {
            try
            {
                rotate = true;

                //берем один из центральных блоков для точки опоры
                Rect center = next_info.first[2];
                board(center).setTo(cv::Scalar(0, 0, 0));

                for (int i = 0; i < 4; i++)
                {
                    //убираем цвет на старых координатах
                    cv::Rect roi(next_info.first[i].x, next_info.first[i].y, next_info.first[i].width, next_info.first[i].height);
                    board(roi).setTo(cv::Scalar(0, 0, 0));

                    //высчитываем по формулам поворот
                    int x = center.y - next_info.first[i].y;
                    int y = center.x - next_info.first[i].x;

                    next_info.second = cv::Scalar(0);
                    next_info.first[i].x = center.x + x;
                    next_info.first[i].y = center.y + y;


                    //у каждой из фигур в процессе поворота оставались блоки, поэтому в момент поворота я их убирала
                    if (current_piece == "Z")
                    {
                        cv::Rect roi2(next_info.first[3].x - 20, next_info.first[3].y - 20, next_info.first[i].width, next_info.first[i].height);
                        board(roi2).setTo(cv::Scalar(0, 0, 0));
                        
                    }
                    if (current_piece == "S")
                    {
                        cv::Rect roi2(next_info.first[3].x + 20, next_info.first[3].y, next_info.first[i].width, next_info.first[i].height);
                        board(roi2).setTo(cv::Scalar(0, 0, 0));
                    }
                    if (current_piece == "L")
                    {
                        cv::Rect roi2(next_info.first[2].x - 40, next_info.first[2].y - 20, next_info.first[i].width, next_info.first[i].height);
                        board(roi2).setTo(cv::Scalar(0, 0, 0));
                    }
                    if (current_piece == "T")
                    {
                        cv::Rect roi2(next_info.first[2].x - 40, next_info.first[2].y - 20, next_info.first[i].width, next_info.first[i].height);
                        board(roi2).setTo(cv::Scalar(0, 0, 0));
                    }
                    if (current_piece == "J")
                    {
                        cv::Rect roi2(next_info.first[3].x - 20, next_info.first[3].y - 20, next_info.first[i].width, next_info.first[i].height);
                        board(roi2).setTo(cv::Scalar(0, 0, 0));
                    }
                    if (current_piece == "I")
                    {
                        cv::Rect roi2(next_info.first[3].x - 20, next_info.first[3].y, next_info.first[i].width, next_info.first[i].height);
                        cv::Rect roi3(next_info.first[3].x - 40, next_info.first[3].y, next_info.first[i].width, next_info.first[i].height);
                        cv::Rect roi4(next_info.first[3].x + 20, next_info.first[3].y, next_info.first[i].width, next_info.first[i].height);
                       
                        board(roi2).setTo(cv::Scalar(0, 0, 0));
                        board(roi3).setTo(cv::Scalar(0, 0, 0));
                        board(roi4).setTo(cv::Scalar(0, 0, 0));
                    }


                    //присваеваем цвет новым координатам
                    next_info.second = color;

                }





            }
            catch (cv::Exception& e)
            {
                std::cerr << e.msg << std::endl; 
            }

        }

        //кладем тетриминошки быстрее
        if (key == 's')
        {

            //в конце поля уже увеличивать скорость не стоит
            int maxBoardS = 320;


            if (maxY < maxBoardS)
            {
                SPEED = 100;

            }
        }
        //выход из игры
        if (key == 8 || key == 27)
        {
            quit = true;
            break;
        }

        //для того, чтобы убирать заполненные строки и увеличивать счет
        int k = board.rows - 1;
        for (int i = board.rows - 1; i > 0; i--) {
            int count_rows = 0;
            for (int j = 0; j < board.cols; j++) {
                if (board.at<int>(i, j)) {
                    count_rows++;
                }
                board.at<int>(k, j) = board.at<int>(i, j);
            }
            if (count_rows < board.cols) {
                k--;
            }
            else {
                score += 1;
            }
        }
        
        score = score + (score % 2);



    }
    //при выходе из игры прерывается процесс и показывается окошко "Game over!"
    if (quit)
    {
        showGameOverWindow();
    }
}

