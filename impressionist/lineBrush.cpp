//
// lineBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "lineBrush.h"
#include <math.h>


LineBrush::LineBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void LineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "LineBrush::BrushMove  document is NULL\n" );
		return;
	}
    
    int size = pDoc->getSize();
    double half_lineWidth = pDoc->getLineWidth() / 2;
    double lineAngle = pDoc->getLineAngle() * 1.0 / 180 * PI;
    
	glBegin( GL_LINES );
        SetColor( source );
    
        for (double i = half_lineWidth; i >= - half_lineWidth; i -= 0.5) {
            glVertex2d( target.x + i*cos(lineAngle + PI / 2), target.y + i* sin(lineAngle + PI / 2));
            glVertex2d( target.x + size * cos(lineAngle)+ i*cos(lineAngle + PI / 2), target.y + size * sin(lineAngle)+ i* sin(lineAngle + PI / 2));
        }

	glEnd();
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

