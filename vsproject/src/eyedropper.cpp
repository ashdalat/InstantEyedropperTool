#include "eyedropper.h"
#include <windows.h>

// Function to get the average color from a 9x9 pixel area around the cursor
COLORREF GetAverageColorAtCursor(HDC hdc, int x, int y) {
    int r = 0, g = 0, b = 0;

    for (int dx = -4; dx <= 4; ++dx) {
        for (int dy = -4; ++dy) {
            COLORREF color = GetPixel(hdc, x + dx, y + dy);
            r += GetRValue(color);
            g += GetGValue(color);
            b += GetBValue(color);
        }
    }

    // Calculate the average color
    r /= 81;
    g /= 81;
    b /= 81;

    return RGB(r, g, b);
}

// Function that captures the color under the cursor
void CaptureColorUnderCursor() {
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    HDC hdcScreen = GetDC(NULL);
    COLORREF color = GetAverageColorAtCursor(hdcScreen, cursorPos.x, cursorPos.y);

    // Process the color as needed
    // ...

    ReleaseDC(NULL, hdcScreen);
}

// Constructor for the Eyedropper class
Eyedropper::Eyedropper() {
    // Initialization code
}

// Destructor for the Eyedropper class
Eyedropper::~Eyedropper() {
    // Cleanup code
}

// Additional Eyedropper functions
void Eyedropper::StartCapture() {
    // Code to start capturing the color
    CaptureColorUnderCursor();
}

void Eyedropper::StopCapture() {
    // Code to stop capturing
}

void Eyedropper::ProcessCapturedColor(COLORREF color) {
    // Code to process the captured color
}
