//
// scatpointBrush.cpp
//
// The implementation of Scatpoint Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatpointBrush.h"

extern float frand();

ScatpointBrush::ScatpointBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatpointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void ScatpointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}
    
    int size = pDoc->getSize();
    
    int half_size = size / 2;
    
    glPointSize(1);

	glBegin( GL_POINTS );
    
		SetColor( source );
    
        for (int i = -half_size; i < half_size; i++) {
            for (int j = -half_size; j < half_size; j++) {
                
                if (frand() < 0.8f) continue;
                glVertex2d( target.x + i, target.y + j);
            }
        }
    
	glEnd();
}

void ScatpointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

