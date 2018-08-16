#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
    Display* dis;
    Window win;
    XSetWindowAttributes att;
    XVisualInfo vinfo;
    XEvent ev;

    dis = XOpenDisplay( NULL );

    XMatchVisualInfo(dis, DefaultScreen(dis), 32, TrueColor, &vinfo);
    
    att.colormap = XCreateColormap(dis, DefaultRootWindow(dis), vinfo.visual, AllocNone);
    att.border_pixel = 0;
    att.background_pixel = 0;

    win = XCreateWindow( dis, DefaultRootWindow(dis), 100, 100, 300, 200, 0, vinfo.depth,
                InputOutput, vinfo.visual,
                CWColormap | CWBorderPixel | CWBackPixel, &att);

    Atom wm_delete_window = XInternAtom(dis, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(dis, win, &wm_delete_window, 1);

    XMapWindow(dis, win);
    XFlush(dis);

    while(true){
        XNextEvent( dis, &ev );
        switch(ev.type){
        case ClientMessage:
            if (ev.xclient.data.l[0] == wm_delete_window)
                goto end;
            break;
        default:
            continue;
        }
    }
    end: 
    //getchar();
    XDestroyWindow( dis, win );
    XCloseDisplay( dis );

    return 0;
}
