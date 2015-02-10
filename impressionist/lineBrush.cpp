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
#include <iostream>

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
            
            if (pDoc->getEdgeClipping()) {
                
                int leftSize = 0;
                for (; leftSize <= size / 2; leftSize++) {
                    if (pDoc->checkEdge(target.x - leftSize * cos(lineAngle) + i*cos(lineAngle + PI / 2), target.y - leftSize * sin(lineAngle) + i* sin(lineAngle + PI / 2))) break;
                }
                
                
                leftSize = leftSize > size / 2 ? size / 2 : leftSize;
                
                int rightSize = 0;
                
                for (; rightSize <= size / 2; rightSize++) {
                    if (pDoc->checkEdge(target.x + rightSize * cos(lineAngle) + i*cos(lineAngle + PI / 2), target.y + rightSize * sin(lineAngle) + i* sin(lineAngle + PI / 2))) break;
                }
                
                rightSize = rightSize > size / 2 ? size / 2 : rightSize;
                
                glVertex2d( target.x - leftSize * cos(lineAngle) + i*cos(lineAngle + PI / 2), target.y - leftSize * sin(lineAngle) + i* sin(lineAngle + PI / 2));
                glVertex2d( target.x + rightSize * cos(lineAngle) + i*cos(lineAngle + PI / 2), target.y + rightSize * sin(lineAngle) + i* sin(lineAngle + PI / 2));
                
            } else {
                
                glVertex2d( target.x - size * cos(lineAngle) / 2 + i*cos(lineAngle + PI / 2), target.y - size * sin(lineAngle) / 2 + i* sin(lineAngle + PI / 2));
                glVertex2d( target.x + size * cos(lineAngle) / 2+ i*cos(lineAngle + PI / 2), target.y + size * sin(lineAngle) / 2 + i* sin(lineAngle + PI / 2));
            }
            
        }

	glEnd();
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

