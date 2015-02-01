//
// circleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circleBrush.h"
#include <math.h>

extern float frand();

CircleBrush::CircleBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void CircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	//int size = pDoc->getSize();

	//glPointSize( (float)size );

	BrushMove( source, target );
}

void CircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "CircleBrush::BrushMove  document is NULL\n" );
		return;
	}


    
    
    int size = pDoc->getSize();
    double radius = size/2;
    
    
	glBegin( GL_POLYGON );
        SetColor( source );
    
        for (int i = 0; i < EDGES; i++) {
            double angle = 2 * M_PI * i / EDGES;
            glVertex2d( target.x + radius * cos(angle), target.y + radius * sin(angle));
        }
	
	glEnd();
}

void CircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

