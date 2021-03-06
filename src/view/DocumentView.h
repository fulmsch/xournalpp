/*
 * Xournal++
 *
 * Paints a page to a cairo context
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include "ElementContainer.h"

#include "model/Element.h"
#include "model/Image.h"
#include "model/PageRef.h"
#include "model/Stroke.h"
#include "model/TexImage.h"
#include "model/Text.h"

#include <XournalType.h>

#include <gtk/gtk.h>

class EditSelection;
class MainBackgroundPainter;

class DocumentView
{
public:
	DocumentView();
	virtual ~DocumentView();

public:

	/**
	 * Draw the full page, usually you would like to call this method
	 * @param page The page to draw
	 * @param cr Draw to thgis context
	 * @param dontRenderEditingStroke false to draw currently drawing stroke
	 */
	void drawPage(PageRef page, cairo_t* cr, bool dontRenderEditingStroke);



	void drawStroke(cairo_t* cr, Stroke* s, int startPoint = 0, double scaleFactor = 1, bool changeSource = true);
	void drawEraseableStroke(cairo_t* cr, Stroke* s);

	static void applyColor(cairo_t* cr, Stroke* s);
	static void applyColor(cairo_t* cr, int c, int alpha = 255);
	static void applyColor(cairo_t* cr, Element* e, int alpha = 255);

	void limitArea(double x, double y, double width, double height);

	void drawSelection(cairo_t* cr, ElementContainer* container);

	// API for special drawing, usually you won't call this methods
public:
	/**
	 * Drawing first step
	 * @param page The page to draw
	 * @param cr Draw to thgis context
	 * @param dontRenderEditingStroke false to draw currently drawing stroke
	 */
	void initDrawing(PageRef page, cairo_t* cr, bool dontRenderEditingStroke);

	/**
	 * Draw the background
	 */
	void drawBackground();

	/**
	 * Draw a single layer
	 * @param cr Draw to thgis context
	 * @param l The layer to draw
	 */
	void drawLayer(cairo_t* cr, Layer* l);

	/**
	 * Last step in drawing
	 */
	void finializeDrawing();

private:
	void drawText(cairo_t* cr, Text* t);
	void drawImage(cairo_t* cr, Image* i);
	void drawTexImage(cairo_t* cr, TexImage* i);

	void drawElement(cairo_t* cr, Element* e);

	void paintBackgroundImage();

private:
	XOJ_TYPE_ATTRIB;

	cairo_t* cr;
	PageRef page;
	double width;
	double height;
	bool dontRenderEditingStroke;

	double lX;
	double lY;
	double lWidth;
	double lHeight;

	MainBackgroundPainter* backgroundPainter;
};
