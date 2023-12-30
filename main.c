#include "graphics/graphics.h"
#include "neural/activations.h"
#include "neural/nn.h"
#include "train_test.h"
int main(void) {

    NeuralNetwork *net = network_load("model2");
    int PredictedNumber = -1;

    InitWindow(screenWidth, screenHeight, "Raylib Canvas Drawing");


    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, 1);

    Rectangle clearButtonRec = {200 , 20 , 100, 40};
    Rectangle predictButtonRec = {500 , 20 , 100, 40};

    bool clearButtonPressed = false;
    bool predictButtonPressed = false;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    Color brushColor = WHITE;
    int brushSize = 10;

    Vector2 prevMousePosition = { -1, -1 };

    while (!WindowShouldClose()) {

        Vector2 currentMousePosition = {GetMouseX() , GetMouseY()};

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            BeginTextureMode(target);

            if ((prevMousePosition.x >= boxX) && (prevMousePosition.y >= boxY) &&
                (prevMousePosition.x <= boxX + boxWidth) && (prevMousePosition.y <= boxY + boxHeight)) 

                    if ((currentMousePosition.x >= boxX) && (currentMousePosition.y >= boxY) &&
                    (currentMousePosition.x <= boxX + boxWidth) && (currentMousePosition.y <= boxY + boxHeight)) {

                       DrawCircleV(currentMousePosition, brushSize, brushColor);
            }


            EndTextureMode();
        }

        prevMousePosition = currentMousePosition;

        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangleLines(boxX - 1, boxY - 1, boxWidth + 2, boxHeight + 2, WHITE);

        DrawTextureRec(target.texture, (Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height}, (Vector2){0, 0}, WHITE);

        ButtonsDraw(clearButtonRec ,predictButtonRec);

        clearButtonPressed = IsClearButtonPressed(clearButtonRec);
        predictButtonPressed = IsPredictButtonPressed(predictButtonRec);

        if (clearButtonPressed) {
            target = LoadRenderTexture(screenWidth, screenHeight);
            SetTextureFilter(target.texture, 1);

            ClearBackground(BLACK);
            PredictedNumber = -1;

        }


        if (predictButtonPressed) {
            matrix * img = GetImage(target.texture , (Rectangle){boxX, boxY, boxWidth, boxHeight});
            matrix* img_data = matrix_flatten(img, 0);

            matrix * pred = network_predict(net , img_data , leakeyRelu);
            PredictedNumber = matrix_argmax(pred);
        }

        DrawPrediction(PredictedNumber);

        clearButtonPressed = false;
        predictButtonPressed = false;

        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
