//
// scatcircleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatcircleBrush.h"

extern float frand();

ScatcircleBrush::ScatcircleBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatcircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void ScatcircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}
    
    int size = pDoc->getSize();
      

	////????glBegin( GL_Scatcircle );
	//	SetColor( source );

	//	glVertex2d( target.x, target.y );

	//glEnd();
}

void ScatcircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

