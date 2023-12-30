#include "graphics.h"

void DrawPrediction(int PredictedNumber)
{
    if (PredictedNumber != -1)
    {
        const int textWidth = MeasureText("Predicted Number: 0", 20);
        const int textHeight = 20;

        const int textPosX = (screenWidth - textWidth) / 2;

        char buffer[20];
        sprintf(buffer, "Predicted Number: %d", PredictedNumber);

        DrawText(buffer, textPosX, 500, 20, WHITE);
    }
    else
    {
        char *text = "No Prediction Available, Press Predict to make a Prediction";
        const int textWidth = MeasureText(text, 20);
        const int textHeight = 20;

        const int textPosX = (screenWidth - textWidth) / 2;

        DrawText(text, textPosX, 500, 20, WHITE);
    }
}
void ButtonsDraw(Rectangle clearButtonRec , Rectangle predictButtonRec)
{

    DrawRectangleRounded(clearButtonRec, 5.f, 1, WHITE);
    DrawText("Clear", clearButtonRec.x + (clearButtonRec.width - MeasureText("Clear", 26)) / 2, clearButtonRec.y + (clearButtonRec.height - 26) / 2, 26, BLACK);

    DrawRectangleRounded(predictButtonRec, 5.f, 1, WHITE);
    DrawText("Predict", predictButtonRec.x + (predictButtonRec.width - MeasureText("Predict", 26)) / 2, predictButtonRec.y + (predictButtonRec.height - 26) / 2, 26, BLACK);
}
bool IsClearButtonPressed(Rectangle clearButtonRec)
{
    return CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, clearButtonRec) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}
bool IsPredictButtonPressed(Rectangle predictButtonRec)
{
    return CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, predictButtonRec) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}