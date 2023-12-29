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

        DrawText(buffer, textPosX, 500, 20, RED);
    }
    else
    {
        char *text = "No Prediction Available, Press Predict to make a Prediction";
        const int textWidth = MeasureText(text, 20);
        const int textHeight = 20;

        const int textPosX = (screenWidth - textWidth) / 2;

        DrawText(text, textPosX, 500, 20, RED);
    }
}
void ButtonsDraw(Rectangle clearButtonRec , Rectangle predictButtonRec)
{

    DrawRectangleRounded(clearButtonRec, 5.f, 1, RED);
    DrawText("Clear", clearButtonRec.x + (clearButtonRec.width - MeasureText("Clear", 26)) / 2, clearButtonRec.y + (clearButtonRec.height - 26) / 2, 26, BLACK);

    DrawRectangleRounded(predictButtonRec, 5.f, 1, RED);
    DrawText("Predict", predictButtonRec.x + (predictButtonRec.width - MeasureText("Predict", 26)) / 2, predictButtonRec.y + (predictButtonRec.height - 26) / 2, 26, BLACK);
}
void LinesDraw(int * pointsX , int * pointsY , bool * canvasColor , int * pointsCount)
{
    for (int i = 1; i < *pointsCount; i++)
    {
        DrawLineEx((Vector2){(float)pointsX[i - 1], (float)pointsY[i - 1]}, (Vector2){(float)pointsX[i], (float)pointsY[i]}, 5, RAYWHITE);

        int startX = pointsX[i - 1] - boxX;
        int startY = pointsY[i - 1] - boxY;
        int endX = pointsX[i] - boxX;
        int endY = pointsY[i] - boxY;

        int dx = abs(endX - startX);
        int dy = abs(endY - startY);
        int sx = (startX < endX) ? 1 : -1;
        int sy = (startY < endY) ? 1 : -1;
        int err = dx - dy;

        while (true)
        {
            canvasColor[startY * boxWidth + startX] = true;

            if (startX == endX && startY == endY)
                break;

            int e2 = 2 * err;

            if (e2 > -dy)
            {
                err -= dy;
                startX += sx;
            }

            if (e2 < dx)
            {
                err += dx;
                startY += sy;
            }
        }
    }
}
void UpdateCanvasAndPoints(int * pointsX , int * pointsY , bool * canvasColor , int * pointsCount)
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (CheckCollisionPointRec((Vector2){(float)mouseX, (float)mouseY}, (Rectangle){(float)boxX, (float)boxY, (float)boxWidth, (float)boxHeight}))
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            int canvasX = mouseX - boxX;
            int canvasY = mouseY - boxY;

            if (canvasX >= 0 && canvasX < boxWidth && canvasY >= 0 && canvasY < boxHeight)
            {
                canvasColor[canvasY * boxWidth + canvasX] = true;

                if (*pointsCount < MAX_POINTS)
                {
                    pointsX[*pointsCount] = canvasX + boxX;
                    pointsY[*pointsCount] = canvasY + boxY;
                    (*pointsCount)++;
                }
            }
        }
    }
}
bool IsClearButtonPressed(Rectangle clearButtonRec)
{
    return CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, clearButtonRec) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}
bool IsPredictButtonPressed(Rectangle predictButtonRec)
{
    return CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, predictButtonRec) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}