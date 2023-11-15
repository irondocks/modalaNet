#include <iostream>
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    const wchar_t CLASS_NAME[] = L"FloatingWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the root window
    HWND hwndRoot = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        L"",                            // Window text
        0,                              // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Position
        CW_USEDEFAULT, CW_USEDEFAULT,   // Size
        NULL,                           // Parent window
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    // Create the agent window
    HWND hwndAgent = CreateWindowEx(
        WS_EX_TOOLWINDOW,               // Extended window style for a tool window
        CLASS_NAME,                     // Window class
        L"Agent Window",                // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Position
        CW_USEDEFAULT, CW_USEDEFAULT,   // Size
        NULL,                           // Parent window
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    // Show the agent window
    ShowWindow(hwndAgent, nCmdShow);

    // Main message loop
    MSG msg = {};
    int childWindowCount = 1; // Start with 1 child window (the agent window)
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_DESTROY && msg.hwnd != hwndRoot) {
            childWindowCount--;
            if (childWindowCount == 0) {
                PostQuitMessage(0);
            }
        }
        else if (msg.message == WM_CREATE && msg.hwnd != hwndRoot) {
            childWindowCount++;
        }
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}