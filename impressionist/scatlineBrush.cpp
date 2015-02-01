//
// scatlineBrush.cpp
//
// The implementation of Scatline Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatlineBrush.h"

extern float frand();

ScatlineBrush::ScatlineBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatlineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	//////??????????glScatlineSize( (float)size );

	BrushMove( source, target );
}

void ScatlineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	//glBegin( GL_Scatline );
	//	SetColor( source );

	//	glVertex2d( target.x, target.y );

	//glEnd();
}

void ScatlineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

