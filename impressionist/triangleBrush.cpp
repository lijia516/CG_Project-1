//
// triangleBrush.cpp
//
// The implementation of Triangle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "triangleBrush.h"

extern float frand();

TriangleBrush::TriangleBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void TriangleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	BrushMove( source, target );
}

void TriangleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "TriangleBrush::BrushMove  document is NULL\n" );
		return;
	}
    
    int size = pDoc->getSize();
    
    double half_size = size * 1.0 / 2;

	glBegin( GL_POLYGON );
		SetColor( source );
    
        if (1) {
        
            
            double upSize = 0;
            for (; upSize <= half_size; upSize++) {
                if (pDoc->checkEdge(target.x, target.y + upSize)) break;
            }
            
            double leftSize = 0;
            for (; leftSize <= half_size; leftSize++) {
                if (pDoc->checkEdge(target.x - leftSize, target.y - leftSize)) break;
            }
            
            double rightSize = 0;
            for (; rightSize <= half_size; rightSize++) {
                if (pDoc->checkEdge(target.x + rightSize, target.y - rightSize)) break;
            }
            
        
            glVertex2d( target.x, target.y + upSize );
            glVertex2d( target.x - leftSize, target.y - leftSize );
            glVertex2d( target.x + rightSize, target.y - rightSize );
            
            
        }else {
    
            glVertex2d( target.x, target.y + half_size );
            glVertex2d( target.x - half_size, target.y - half_size );
            glVertex2d( target.x + half_size, target.y - half_size );
        }

	glEnd();
}

void TriangleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

