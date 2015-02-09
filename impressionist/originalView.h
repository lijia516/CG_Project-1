//
// originalview.h
//
// The header file for original view of the input images
//

#ifndef ORIGINALVIEW_H
#define ORIGINALVIEW_H

#include <FL/Fl.H>

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/glu.h>

#include <stdlib.h>

#include "impBrush.h"



// Each filter type has an associated constant.
enum
{
    ORIGINAL_IMAGE = 0,
    GRAYSCALE_IMAGE = 1,
    DEGE_IMAGE = 2,
    NUM_IMAGE_TYPE// Make sure this stays at the end!
};


class ImpressionistDoc;

class OriginalView : public Fl_Gl_Window
{
public:
	OriginalView(int x, int y, int w, int h, const char *l);
	
	void draw();
	void refresh();
    void setOriginalView(int originalView);
	void resizeWindow(int width, int height);

	ImpressionistDoc*	m_pDoc;

private:
	int	m_nWindowWidth, 
		m_nWindowHeight;
    int m_ncOriginalView;
    
    unsigned char*	m_ucShow;
    

};

#endif

