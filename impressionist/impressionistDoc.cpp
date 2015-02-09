//
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//
#include <iostream>

#include <FL/fl_ask.H>

#include <algorithm>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "impBrush.h"

// Include individual brush headers here.
#include "pointBrush.h"
#include "lineBrush.h"
#include "circleBrush.h"
#include "scatpointBrush.h"
#include "scatlineBrush.h"
#include "scatcircleBrush.h"
#include "triangleBrush.h"
#include "randscatlineBrush.h"
#include <math.h>


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
    m_ucEdgeImage   = NULL;
    m_ucGrayscaleImage   = NULL;
	m_ucPreviewBackup = NULL;
    m_ucPreviewBackup2 = NULL;
    
    hasEdgeImage = false;
    hasGrayscaleImage = false;

	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatpointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatlineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatcircleBrush( this, "Scattered Circles" );
    ImpBrush::c_pBrushes[BRUSH_TRIANGLE]
    = new TriangleBrush( this, "Triangle" );
    ImpBrush::c_pBrushes[BRUSH_RANDSCATTERED_LINES]
    = new RandScatlineBrush( this, "RandScattered Lines" );

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}


//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// set the size of the brush.
//---------------------------------------------------------
void ImpressionistDoc::setSize(int size)
{
    return m_pUI->setSize(size);
}


//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
float ImpressionistDoc::getAlpha()
{
    return m_pUI->getAlpha();
}


// Returns the width of the line brush.
//---------------------------------------------------------
int ImpressionistDoc::getLineWidth()
{
    return m_pUI->getLineWidth();
}

//---------------------------------------------------------
// Returns the if multi color or not.
//---------------------------------------------------------
bool ImpressionistDoc::getMultiColor()
{
    return m_pUI->getMultiColor();
}

//---------------------------------------------------------
// Returns the if edge clipping or not.
//---------------------------------------------------------
bool ImpressionistDoc::getEdgeClipping()
{
    return m_pUI->getEdgeClipping();
}


// set the width of the line brush.
//---------------------------------------------------------
void ImpressionistDoc::setLineWidth(int lineWidth)
{
    return m_pUI->setLineWidth(lineWidth);
}

// Returns the angle of the line brush.
//---------------------------------------------------------
int ImpressionistDoc::getLineAngle()
{
    return m_pUI->getLineAngle();
}

// set the angle of the line brush.
//---------------------------------------------------------
void ImpressionistDoc::setLineAngle(int lineAngle)
{
    return m_pUI->setLineAngle(lineAngle);
}



// store edge image in m_ucEdgeImage
//----------------------------------------------------------
void ImpressionistDoc::getEdgeImage(){
    
    
    // grayscale
    const unsigned char* sourceBuffer = m_ucBitmap;
    int srcBufferWidth = m_nWidth;
    int srcBufferHeight = m_nHeight;
    unsigned char* destBuffer = m_ucPreviewBackup;
    
    grayscaleImage(sourceBuffer, destBuffer, srcBufferWidth, srcBufferHeight);
    
    // blurring
    double fltKernel[9] = {1,2,1,2,3,2,1,2,1};
    const double *filterKernel = fltKernel;
    
    int m_KernelWidth = 3;
    int m_KernelHeight = 3;
    
    sourceBuffer = m_ucPreviewBackup;
    destBuffer = m_ucPreviewBackup2;
    
    applyFilter(sourceBuffer, srcBufferWidth, srcBufferHeight, destBuffer, filterKernel, m_KernelWidth, m_KernelHeight, 1, 0);
    
    double sobelEdgeDetectKnl1[9] = {1,2,1,0,0,0,-1,-2,-1};
    double sobelEdgeDetectKnl2[9] = {1,0,-1,2,0,-2,1,0,-1};
    
    
    // edge detection
    sourceBuffer = m_ucPreviewBackup2;
    destBuffer = m_ucEdgeImage;
    edgeDetector(sourceBuffer, srcBufferWidth, srcBufferHeight, destBuffer, sobelEdgeDetectKnl1, sobelEdgeDetectKnl2, m_KernelWidth, m_KernelHeight);
}

// store grayscale image in m_ucGrayscaleImage
//----------------------------------------------------------
void ImpressionistDoc::getGrayscaleImage(){
    
    // grayscale
    const unsigned char* sourceBuffer = m_ucBitmap;
    unsigned char* destBuffer = m_ucGrayscaleImage;
    int srcBufferWidth = m_nWidth;
    int srcBufferHeight = m_nHeight;
    grayscaleImage(sourceBuffer, destBuffer, srcBufferWidth, srcBufferHeight);
}


//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	delete [] m_ucBitmap;
	delete [] m_ucPainting;
    delete [] m_ucEdgeImage;
    delete [] m_ucGrayscaleImage;
	delete [] m_ucPreviewBackup;
    delete [] m_ucPreviewBackup2;
    
	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting		= new unsigned char [width*height*3];
    m_ucEdgeImage		= new unsigned char [width*height*3];
    m_ucGrayscaleImage	= new unsigned char [width*height*3];
	m_ucPreviewBackup	= new unsigned char [width*height*3];
    m_ucPreviewBackup2	= new unsigned char [width*height*3];
    
    hasEdgeImage = false;
    hasGrayscaleImage = false;
    
	memset(m_ucPainting, 0, width*height*3);
    memset(m_ucEdgeImage, 0, width*height*3);
    memset(m_ucGrayscaleImage, 0, width*height*3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

// Apply the filter specified by filter_kernel to the 
// each pixel in the source buffer and place the resulting
// pixel in the destination buffer.  

// This is called from the UI when the
// "preview" or "apply" button is pressed in the filter dialog.



/*
 *	INPUT: 
 *		sourceBuffer:		the original image buffer, 
 *		srcBufferWidth:		the width of the image buffer
 *		srcBufferHeight:	the height of the image buffer
 *							the buffer is arranged such that 
 *							origImg[3*(row*srcBufferWidth+column)+0], 
 *							origImg[3*(row*srcBufferWidth+column)+1], 
 *							origImg[3*(row*srcBufferWidth+column)+2]
 *							are R, G, B values for pixel at (column, row).
 *		destBuffer:			the image buffer to put the resulting
 *							image in.  It is always the same size
 *							as the source buffer.
 *
 *      filterKernel:		the 2D filter kernel,
 *		knlWidth:			the width of the kernel
 *		knlHeight:			the height of the kernel
 *
 *		divisor, offset:	each pixel after filtering should be
 *							divided by divisor and then added by offset
 */
void ImpressionistDoc::applyFilter( const unsigned char* sourceBuffer,
		int srcBufferWidth, int srcBufferHeight,
		unsigned char* destBuffer,
		const double *filterKernel, 
		int knlWidth, int knlHeight, 
		double divisor, double offset )
{
	// This needs to be implemented for image filtering to work.
    
    std::cout << "divisor, offset: " << divisor <<","<<  offset<< ",";
    
    int knlSize =  knlWidth * knlHeight;
    int knlCenterRow = knlHeight / 2;
    int knlCenterCol = knlWidth / 2;
    
    int nRow = 0;
    int nCol = 0;
    
    
    for (int row = 0; row < srcBufferHeight; row++) {
        for (int col = 0; col < srcBufferWidth; col++) {
            
            int sumColor[3] = {0,0,0};
            int sumKernl = 0;
            for (int i = 0; i < knlSize; i++) {
                
                int nRow = i / knlWidth + (row - knlCenterRow);
                int nCol = i % knlWidth + (col - knlCenterCol);
                
           //     std::cout << nRow << "," << nCol << "\n";
                
                if (nRow < 0 || nCol < 0) continue;
                
                sumColor[0] += (sourceBuffer[3*(nRow*srcBufferWidth+nCol)+0] - '0') * filterKernel[i];
                
                
               // std::cout << "color[0]: " << sourceBuffer[3*(nRow*srcBufferWidth+nCol)+0] - '0' << "\n";
               // std::cout << "filterKernel2[i]: " << filterKernel2[i] << "\n";
               // std::cout << "sumcolor[0]: " << sumColor[0] << "\n";
                
                sumColor[1] += (sourceBuffer[3*(nRow*srcBufferWidth+nCol)+1] - '0') * filterKernel[i];
                
                
               // std::cout << "color[1]: " << sourceBuffer[3*(nRow*srcBufferWidth+nCol)+1] - '0' << "\n";
               // std::cout << "sumcolor[1]: " << sumColor[1] << "\n";
                
                sumColor[2] += (sourceBuffer[3*(nRow*srcBufferWidth+nCol)+2] - '0') * filterKernel[i];
                
               // std::cout << "color[2]: " << sourceBuffer[3*(nRow*srcBufferWidth+nCol)+2] - '0' << "\n";
              //  std::cout << "sumcolor[2]: " << sumColor[2] << "\n";
                
                
                sumKernl += filterKernel[i];
                
            //    std::cout << "sumKernel: " << sumKernl << "\n";
             //   int a;
             //   std::cin >> a;
               
            }
            
            
            for (int i = 0; i < 3; i++) {
                
                sumColor[i] = sumColor[i] / (sumKernl);
                
               
                
                sumColor[i] = sumColor[i] / divisor;
                sumColor[i] += offset;
                
                if (sumColor[i] < 0) sumColor[i] =0;
                else if (sumColor[i] > 255) sumColor[i] = 255;
                
                
                destBuffer[3*(row*srcBufferWidth+col)+i] = sumColor[i] + '0';
                
                
            //    std::cout << "sumcolor[i]: " << sumColor[i] << ",";
                
            }
            
            // std::cout << "\n";
            
        }
    }

}




void ImpressionistDoc::edgeDetector( const unsigned char* sourceBuffer,
                                    int srcBufferWidth, int srcBufferHeight,
                                    unsigned char* destBuffer,
                                    const double *filterKernel1,
                                    const double *filterKernel2,
                                    int knlWidth, int knlHeight)
{
    // This needs to be implemented for image filtering to work.
    
    knlWidth = 3;
    knlHeight = 3;
    
    int knlSize = knlWidth * knlHeight;
    int knlCenterRow = knlHeight / 2;
    int knlCenterCol = knlWidth / 2;
    
    int nRow = 0;
    int nCol = 0;
    
    for (int row = 0; row < srcBufferHeight; row++) {
        for (int col = 0; col < srcBufferWidth; col++) {
            
            double sumColor[3] = {0,0};
            double sumKernl1 = 0;
            double sumKernl2 = 0;
            
            for (int i = 0; i < knlSize; i++) {
                
                int nRow = i / knlWidth + (row - knlCenterRow);
                int nCol = i % knlWidth + (col - knlCenterCol);
                
                if (nRow < 0 || nCol < 0) continue;
                
                sumColor[0] += 3 * (sourceBuffer[3*(nRow*srcBufferWidth+nCol)+0] - '0') * filterKernel1[i];
                sumColor[1] += 3 * (sourceBuffer[3*(nRow*srcBufferWidth+nCol)+0] - '0') * filterKernel2[i];
                
            }
            
            unsigned long temp = 0;
            temp = sqrt(sumColor[0] * sumColor[0] + sumColor[1] * sumColor[1]);

            
            if ( temp > 255) {
                
                destBuffer[3*(row*srcBufferWidth+col)+0] = 255;
                destBuffer[3*(row*srcBufferWidth+col)+1] = 255;
                destBuffer[3*(row*srcBufferWidth+col)+2] = 255;
                
            } else {
                
                destBuffer[3*(row*srcBufferWidth+col)+0] = 0;
                destBuffer[3*(row*srcBufferWidth+col)+1] = 0;
                destBuffer[3*(row*srcBufferWidth+col)+2] = 0;
            }
            
        }
    }
    
}


void ImpressionistDoc::grayscaleImage( const unsigned char* sourceBuffer, unsigned char* destBuffer, int srcBufferWidth, int srcBufferHeight)
{
    
    for (int row = 0; row < srcBufferHeight; row++) {
        for (int col = 0; col < srcBufferWidth; col++) {
      
            
            double intensity = 0.299 * (sourceBuffer[3*(row*srcBufferWidth+col)+0] - '0') + 0.587 * (sourceBuffer[3*(row*srcBufferWidth+col)+1] - '0') + 0.114 * (sourceBuffer[3*(row*srcBufferWidth+col)+2] - '0');
                
                destBuffer[3*(row*srcBufferWidth+col)+0] = intensity + '0';
                destBuffer[3*(row*srcBufferWidth+col)+1] = intensity + '0';
                destBuffer[3*(row*srcBufferWidth+col)+2] = intensity + '0';
        
        }
    }
}


//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}


int ImpressionistDoc::checkEdge(int targetX, int targetY)
{
    
    if (targetX < 0) {
        targetX = 0;
    } else if (targetX >= m_nPaintWidth) {
        targetX = m_nPaintWidth - 1;
    }
    
    if (targetY < 0) {
        targetY = 0;
    } else if (targetY >= m_nPaintHeight) {
        targetY = m_nPaintHeight - 1;
    }
    
    
    if (m_ucEdgeImage) {
        
        if (m_ucEdgeImage[3*(targetY * m_nPaintWidth + targetX) + 0] == 255) return 1;
    }
    
    return 0;
}


/*
int ImpressionistDoc::previewPaintView(unsigned char* previewBackup){
    
    // note that both OpenGL pixel storage and the Windows BMP format
    // store pixels left-to-right, BOTTOM-to-TOP!!  thus all the fiddling
    // around with startrow.
    glDrawBuffer(GL_BACK);
    std::cout<<"hello prevoewPaintView func" <<"\n";
    
    Point scrollpos;// = GetScrollPosition();
    scrollpos.x = 0;
    scrollpos.y	= 0;
    
    int drawWidth, drawHeight;
    drawWidth = fmin( m_pUI->m_paintView->getWindowWidth(), m_nPaintWidth );
    drawHeight = fmin( m_pUI->m_paintView->getWindowHeight(), m_nPaintHeight );
    
    int startrow = m_nPaintHeight - (scrollpos.y + drawHeight);
    if ( startrow < 0 ) startrow = 0;
   
    GLvoid* bitstart;
    bitstart = previewBackup + 3 * ((m_nPaintWidth * startrow) + scrollpos.x);
    
    m_pUI->m_paintView->setPaintBitstart(bitstart);
    m_pUI->m_paintView->SaveCurrentContent();
    glFlush();
    m_pUI->m_paintView->refresh();
    
}
 */


