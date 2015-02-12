//
// alphaMapBrush.cpp
//
// The implementation of alphaMap Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
#include <iostream>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "alphaMapBrush.h"
#include <math.h>

extern float frand();

AlphaMapBrush::AlphaMapBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void AlphaMapBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void AlphaMapBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "AlphaMapBrush::BrushMove  document is NULL\n" );
		return;
	}
    
    int half_Width = pDoc->m_nAlphaMapImageWidth / 2;
    int half_Height = pDoc->m_nAlphaMapImageHeight / 2;
    
    
	glBegin( GL_POINTS  );
    
        for (int i = -half_Width; i < half_Width; i++) {
            
            for (int j = -half_Height; j < half_Height; j++) {
                
                setAlphaMapBrushColor(source, i+half_Width, j+half_Height);
                glVertex2d( target.x + i, target.y + j);
                
            }
        }
	
	glEnd();
}

void AlphaMapBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}


void AlphaMapBrush::setAlphaMapBrushColor(Point source, int x, int y){
    
    
    ImpressionistDoc* pDoc = GetDocument();
    
    GLubyte color[4];
    
    memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
    
    if (pDoc->getColorBlending()) {
        
        color[0] = (color[0] + static_cast<GLubyte> (pDoc->m_pUI->m_ColorChooser->r() * 255.0f)) / 2;
        color[1] = (color[1] + static_cast<GLubyte> (pDoc->m_pUI->m_ColorChooser->g() * 255.0f)) / 2;
        color[2] = (color[2] + static_cast<GLubyte> (pDoc->m_pUI->m_ColorChooser->b() * 255.0f)) / 2;
    }
    
    // just assume the alpha values is the pixel intensities in an image
    double intensity = (pDoc->m_ucAlphaMapImage[3*(y*pDoc->m_nAlphaMapImageWidth+x)+0] + pDoc->m_ucAlphaMapImage[3*(y*pDoc->m_nAlphaMapImageWidth+x)+1] + pDoc->m_ucAlphaMapImage[3*(y*pDoc->m_nAlphaMapImageWidth+x)+2]) * 1.0 / (3 * 255);
    
    color[3] = static_cast<GLubyte>(255.0f * intensity);
    glColor4ubv( color );
    
}
