#include "graphics/graphics.h"
#include "neural/activations.h"
#include "neural/nn.h"

int main(void)
{
    NeuralNetwork *net = network_load("model2");
    int PredictedNumber = -1;

    InitWindow(screenWidth, screenHeight, "Raylib Canvas Drawing");

    SetTargetFPS(60);

    bool canvasColor[boxWidth * boxHeight];
    memset(canvasColor, false, sizeof(canvasColor));

    Rectangle clearButtonRec = {200 , 20 , 100, 40};
    Rectangle predictButtonRec = {500 , 20 , 100, 40};


    bool clearButtonPressed = false;
    bool predictButtonPressed = false;

    int pointsX[MAX_POINTS];
    int pointsY[MAX_POINTS];
    int pointsCount = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangleLines(boxX - 1, boxY - 1, boxWidth + 2, boxHeight + 2, WHITE);

        UpdateCanvasAndPoints(pointsX ,pointsY ,canvasColor , &pointsCount);

        ButtonsDraw(clearButtonRec ,predictButtonRec);

        LinesDraw(pointsX ,pointsY ,canvasColor , &pointsCount);

       
        clearButtonPressed = IsClearButtonPressed(clearButtonRec);
        predictButtonPressed = IsPredictButtonPressed(predictButtonRec);

        if (clearButtonPressed)
        {
            memset(canvasColor, false, sizeof(canvasColor));
            pointsCount = 0;
            PredictedNumber = -1;
        }

        if (predictButtonPressed)
        {
            matrix * img = GetImage(canvasColor , boxWidth , boxHeight);
            matrix* img_data = matrix_flatten(img, 0);

            matrix * pred = network_predict(net , img_data , leakeyRelu);
            PredictedNumber = matrix_argmax(pred);
        }

        DrawPrediction(PredictedNumber);


        clearButtonPressed = false;
        predictButtonPressed = false;

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
