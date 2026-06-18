#include <stdio.h>
#include <windows.h>

int main() {
    LARGE_INTEGER frequency, start, now;
    double elapsed_seconds;
    int h, m, s;

    // Get the counter frequency (ticks per second)
    QueryPerformanceFrequency(&frequency);

    // Record starting time
    QueryPerformanceCounter(&start);

    printf("Timer started...\n");

    while (1) {
        // Get current time
        QueryPerformanceCounter(&now);

        // Calculate elapsed time in seconds
        elapsed_seconds = (double)(now.QuadPart - start.QuadPart) / frequency.QuadPart;

        // Convert to hours, minutes, seconds
        s = (int)elapsed_seconds;
        m = s / 60;
        s %= 60;
        h = m / 60;
        m %= 60;

        // Print time in HH:MM:SS format
        printf("\r%02d:%02d:%02d", h, m, s);
        fflush(stdout);

        Sleep(1000); // Update every ~1 second
    }

    return 0;
}   
