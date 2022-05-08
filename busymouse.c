#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main(int argc, char *argv[]) {

     Display *display;
     Screen *screen;
     Window root_window;

     Bool result;
     Window window_returned;
     int root_x, root_y;
     int win_x, win_y;
     int mid_x, mid_y;
     int new_x, new_y;
     unsigned int mask_return;
     struct sigaction sigact;
     sigset_t waitset;
     siginfo_t info;
     struct timespec timeout;

     display = XOpenDisplay(NULL);

     screen = DefaultScreenOfDisplay(display);
     //     printf("Screen size %dX%d\n", screen->width, screen->height);
     mid_x = screen->width / 2;
     mid_y = screen->height / 2;
     root_window = XRootWindow(display, 0);
     //     printf("Screen middle %dX%d\n", mid_x, mid_y);

     sigemptyset(&waitset);
     sigaddset(&waitset, SIGINT);
     sigaddset(&waitset, SIGTERM);
     sigaddset(&waitset, SIGKILL);
     sigaddset(&waitset, SIGQUIT);
     timeout.tv_sec = 60;
     
     do {
         result = XQueryPointer(display, root_window, &window_returned,
                                &window_returned, &root_x, &root_y, &win_x, &win_y,
                                &mask_return);
         //         printf("Mouse is at (%d,%d)\n", root_x, root_y);

         if (root_x >= mid_x) new_x = root_x -1;
         else new_x = root_x + 1;
         if (root_y >= mid_y) new_y = root_y -1;
         else new_y = root_y + 1;

         XWarpPointer(display, None, root_window, 0, 0, 0, 0, new_x, new_y);

         result = XQueryPointer(display, root_window, &window_returned,
                                &window_returned, &root_x, &root_y, &win_x, &win_y,
                                &mask_return);

         //    printf("Mouse is at (%d,%d)\n", root_x, root_y);

         sigtimedwait(&waitset, &info, &timeout);
     } while (info.si_signo == 0);
     //    printf("Got %d\nExiting gracefully\n",info.si_signo);

     return 0;
}
