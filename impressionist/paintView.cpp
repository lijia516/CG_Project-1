//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintView.h"
#include "impBrush.h"
#include <math.h> 
#include <iostream>

#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;
static Point	pre_coord;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}


void PaintView::draw()
{
//	#ifndef MESA
	// To avoid flicker on some machines.
  //	glDrawBuffer(GL_FRONT_AND_BACK);
//	#endif // !MESA

	if(!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );
        
		ortho();
		glClear( GL_COLOR_BUFFER_BIT );
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

    
    
    
	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting +
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	if ( m_pDoc->m_ucPainting && !isAnEvent)
	{
		RestoreContent();

	}

	if ( m_pDoc->m_ucPainting && isAnEvent)
	{

		// Clear it after processing.
		isAnEvent	= 0;	

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );
		
		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
    
			m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
            
			break;
		case LEFT_MOUSE_DRAG:
          
			m_pDoc->m_pCurrentBrush->BrushMove( source, target );
			break;
		case LEFT_MOUSE_UP:
          
			m_pDoc->m_pCurrentBrush->BrushEnd( source, target );
			SaveCurrentContent();
			RestoreContent();
			break;
		case RIGHT_MOUSE_DOWN:
            lineAngleStartPoint = target;
			break;
		case RIGHT_MOUSE_DRAG:
            
            glLineWidth(2);
            
            glBegin(GL_LINES);
                m_pDoc->m_pCurrentBrush->SetColor(source);
                glVertex2d(lineAngleStartPoint.x, lineAngleStartPoint.y);
                glVertex2d(target.x, target.y);
            glEnd();
			
            break;
                
		case RIGHT_MOUSE_UP:
            
            if (target.x == lineAngleStartPoint.x) {
                
                m_pDoc->setLineAngle(90);
                   
            } else {
                
                double temp = (target.y - lineAngleStartPoint.y)*1.0 / (target.x - lineAngleStartPoint.x);
                
           //     std::cout << "temp: " << temp<< "\n";
           //     std::cout << "angle: " << atan(temp) * 180 / PI<< "\n";

                m_pDoc->setLineAngle(atan(temp) * 180 / PI);
            }
                
			break;

		default:
			printf("Unknown event!!\n");		
			break;
		}
	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA
}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
             pre_coord = coord;
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
             pre_coord = coord;
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		redraw();
		break;
	case FL_RELEASE:
             pre_coord = coord;
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
             pre_coord = coord;
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		break;
	default:
		return 0;
		break;

	}



	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
    glReadBuffer(GL_BACK);
     // glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}



int PaintView::getPerpendicularDirectionToGradient()
{
    
    int xGradFilter[3] = {-1, 0, 1};
    int yGradFilter[3] = {1, 0, -1};
    
    double sumXGF = 0;
    for (int i = 0; i < 3; i++) {
        
        Point source( coord.x + i - 1, m_nEndRow - coord.y );
        
        GLubyte color[3];
        memcpy ( color, m_pDoc->GetOriginalPixel( source ), 3 );
        
        sumXGF += (0.299 * (color[0] - '0') + 0.587 * (color[1] - '0') + 0.114 * (color[2] - '0')) * xGradFilter[i];
        
    }
    
    double sumYGF = 0;
    for (int j = 0; j < 3; j++) {
        
        Point source( coord.x, m_nWindowHeight - (coord.y + j - 1) );
        
        GLubyte color[3];
        memcpy ( color, m_pDoc->GetOriginalPixel( source ), 3 );
        
        sumYGF += (0.299 * (color[0] - '0') + 0.587 * (color[1] - '0') + 0.114 * (color[2] - '0')) * yGradFilter[j];
        
    }
    
    return int (atan(sumYGF/sumXGF) * 180 / PI + 90);
}

int PaintView::getBrushDirection() {
    
    if (pre_coord.x == coord.x) return 90;
    
    return int (atan((coord.y - pre_coord.y)/(coord.x - pre_coord.x)) * 180 / PI);
    
}

int PaintView::getWindowWidth() {
    
    return m_nWindowWidth;
}

int PaintView::getWindowHeight() {
    
    return m_nWindowHeight;
}


void PaintView::setPaintBitstart(GLvoid* painBitstart) {
    
    m_pPaintBitstart = painBitstart;
}
