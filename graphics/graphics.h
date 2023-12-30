#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../util/img.h"
#include "../matrix/matrix.h"
#include "../matrix/ops.h"
#include "raylib.h"

#define MAX_POINTS 1000
#define number_test_imgs 10000

#define screenWidth 800
#define screenHeight 600

#define boxWidth 280
#define boxHeight 280

#define boxX ((screenWidth - boxWidth) / 2)
#define boxY ((screenHeight - boxHeight) / 2)

void DrawPrediction(int PredictedNumber);
void ButtonsDraw(Rectangle clearButtonRec , Rectangle predictButtonRec);
void ButtonsDraw(Rectangle clearButtonRec , Rectangle predictButtonRec);
bool IsClearButtonPressed(Rectangle clearButtonRec);
bool IsPredictButtonPressed(Rectangle predictButtonRec);
