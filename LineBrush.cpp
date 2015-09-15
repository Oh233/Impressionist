//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"
#include <iostream>
using namespace std;

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name), lineLength(10), lineAngle(0), lineXProj(10), lineYProj(0)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int width = pDoc->getWidth();
	glLineWidth((float)width);

	//get the size of the brush and save it
	lineLength = pDoc->getSize();

	//get the angle of the brush and save it
	lineAngle = pDoc->getAngle();

	//calculate the x and y projection of line length
	lineXProj = (int)lineLength * cos(((double)lineAngle) * PI / 360);
	lineYProj = (int)lineLength * sin(((double)lineAngle) * PI / 360);

	cout << endl;
	// If the option is ....
	prevMouseX = target.x;
	prevMouseY = target.y;

	BrushMove(source, target);

}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int strokeDirection = pDoc->getStrokeDirectionType();
	switch (strokeDirection)
	{
	case DIR_SLIDER_OR_RIGHT_MOUSE:
		// Already setted parameter in PaintView::draw()
		break;
	case DIR_BRUSH_DIRECTION:
	{
		double moveAngle;
		double diffX = target.x - prevMouseX;
		if (diffX == 0) moveAngle = PI / 2.0;
		else {
			double diffY = target.y - prevMouseY;
			moveAngle = atan(diffY / diffX);
		}
		prevMouseX = target.x;
		prevMouseY = target.y;
		lineXProj = (int)lineLength * cos(double(moveAngle));
		lineYProj = (int)lineLength * sin(double(moveAngle));
		break;
	}
	case DIR_GRADIENT:
	{
		//get the gradient at given source pixel
		GLint gradientX = pDoc->GetGradientX(source);
		GLint gradientY = pDoc->GetGradientY(source);
		//calculate line Angle and projection
		lineAngle = (int)(atan2(gradientX, -gradientY) / PI * 360); //rotate 90 degree counter clockwise
		printf("gradientX: %d gradientY: %d lineAngle: %d\n", gradientX, gradientY, lineAngle);
		lineXProj = (int)lineLength * cos(((double)lineAngle) * PI / 360);
		lineYProj = (int)lineLength * sin(((double)lineAngle) * PI / 360);
		break;
	}
	}

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove document is NULL \n");
		return;
	}

	//calculate the start and end point of the line to draw
	int x1 = target.x - lineXProj / 2;
	int y1 = target.y - lineYProj / 2;
	int x2 = target.x + lineXProj / 2;
	int y2 = target.y + lineYProj / 2;
	SetColor(source);
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);

	GLenum error_flag;
	error_flag = glGetError();
	if (error_flag != GL_NO_ERROR) {
		printf("Error: %1s (%i) in %1s.\n", gluErrorString(error_flag), error_flag, "method name");
	}
	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}