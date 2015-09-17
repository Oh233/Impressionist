// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"
#include "utility\Filter.h"
#include "utility\SaveMatrix.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType

	int		getStrokeDirectionType();
	int		getSize();						// get the UI size
	int		getWidth();
	int		getAngle();						// get the brush angle
	int		getAlpha();
	bool	getEdgeClipping();
	
	void	setStrokeDirectionType(int type); // called by the UI to set the brushType
	void	setSize(int size);				// set the UI size
	void	setWidth(int width);
	void	setAngle(int angle);			// set the brush angle
	char*	getImageName();					// get the current image name

	GLubyte GetIntensity(int x, int y);
	GLint GetGradientX(int x, int y);
	GLint GetGradientY(int x, int y);
	GLuint GetGradientMod(int x, int y);
	GLboolean GetEdge(int x, int y);
	GLubyte GetIntensity(Point point);
	GLint GetGradientX(Point point);
	GLint GetGradientY(Point point);
	GLuint GetGradientMod(Point point);
	GLboolean GetEdge(Point point);

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	GLubyte*	m_ucBitmap;
	GLubyte*	m_ucPainting;
	// Bitmap for intensity of original image.
	GLubyte*	m_ucIntensity;
	// Gradient map for intensity of original image.
	GLint * m_iGradientX;
	GLint * m_iGradientY;
	// Gradient modulo
	GLuint * m_iGradientMod;
	
	// Edge map
	GLubyte * m_ucEdge;


	// The current active brush.
	ImpBrush*			m_pCurrentBrush;
	int				m_pCurrentDirection;
	// Size of the brush.
	int m_nSize;							

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  
	// Calculate the edge map using gradient mod and threshold
	GLubyte* GetEdgeMap(int EdgeThreshold);

private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
