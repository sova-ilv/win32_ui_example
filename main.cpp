/*
    First working example of win32 api gui
    Use for reference only
*/

#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "features.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
HWND textfield;
HWND hwndButton, hwndButton2, hwndCheckBox1 ;
char textSaved[100];
static char *title = TEXT("Check Box");
int active = 1;

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");



int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */


    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
           textfield = CreateWindow("STATIC",
                                      "Hello Word",
                                      WS_VISIBLE | WS_CHILD | WS_BORDER,
                                      20, 20, 300, 25,
                                      hwnd, NULL, NULL, NULL );

           hwndButton = CreateWindow(
                        "BUTTON",  // Predefined class; Unicode assumed
                        "Go",      // Button text
                        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                        40,         // x position
                        50,         // y position
                        100,        // Button width
                        25,        // Button height
                        hwnd,     // Parent window
                        (HMENU) 1,       // No menu.
                        (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);      // Pointer not needed.

           hwndButton2 = CreateWindow(
                        "BUTTON",  // Predefined class; Unicode assumed
                        "Go 2",      // Button text
                        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                        40,         // x position
                        100,         // y position
                        100,        // Button width
                        25,        // Button height
                        hwnd,     // Parent window
                        (HMENU) 2,       // No menu.
                        (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);      // Pointer not needed

           hwndCheckBox1 = CreateWindow("BUTTON",TEXT("Title A"),WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                        40,250,100,25,hwnd,(HMENU) 3, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
           CheckDlgButton(hwnd, 3, BST_CHECKED);

        //Create a timer
           SetTimer(hwnd, 4, 5000, NULL);

            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case 1: //Button 1
                    MessageBox(NULL, "You pressed my button 1!", "Hey", MB_OK);
                    int gwtstat;
                    gwtstat = GetWindowText(textfield, &textSaved[0], 100);
                    MessageBox(NULL, textSaved, NULL, MB_OK);

                    break;

                 case 2: //Button 2
                    MessageBox(NULL, "You pressed my button 2!", "Hey", MB_OK);
                    break;

                 case 3: //This handles the checkbox command
                    BOOL checked = IsDlgButtonChecked(hwnd, 3);
                    if (checked)
                    {
                        CheckDlgButton(hwnd, 3, BST_UNCHECKED);
                        SetWindowText(hwnd, TEXT(""));
                    }
                    else {
                     CheckDlgButton(hwnd, 3, BST_CHECKED);
                     SetWindowText(hwnd, title);
                    }
                    break;
            }
            break;

        case WM_TIMER:
            //Timer has fired.
            if (active) {
                MessageBox(NULL, "Active", "feature is active!", MB_OK);
                active=0;}

            else {
                MessageBox(NULL, "Timer", "Timer fired!", MB_OK);
                active=1;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
