/*
 * Xournal++
 *
 * Handles Tools
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include "Tool.h"
#include "settings/Settings.h"

#include <Arrayiterator.h>
#include <XournalType.h>

class LastSelectedTool;

class ToolListener
{
public:
	virtual void toolColorChanged() = 0;
	virtual void setCustomColorSelected() = 0;
	virtual void toolSizeChanged() = 0;
	virtual void toolChanged() = 0;

	virtual ~ToolListener();
};

class ActionHandler;

class ToolHandler
{
public:
	ToolHandler(ToolListener* listener, ActionHandler* actionHandler, Settings* settings);
	virtual ~ToolHandler();

	void setColor(int color);
	int getColor();

	DrawingType getDrawingType();
	void setDrawingType(DrawingType drawingType);

	void setColorFound();

	ToolSize getSize();
	void setSize(ToolSize size);
	double getThickness();

	ToolSize getPenSize();
	ToolSize getEraserSize();
	ToolSize getHilighterSize();
	void setPenSize(ToolSize size);
	void setEraserSize(ToolSize size);
	void setHilighterSize(ToolSize size);


	void selectTool(ToolType type, bool fireToolChanged = true);
	ToolType getToolType();
	void fireToolChanged();

	Tool &getTool(ToolType type);

	void setEraserType(EraserType eraserType);
	EraserType getEraserType();
	void eraserTypeChanged();

	bool isEnableColor();
	bool isEnableSize();
	bool isEnableRuler();
	bool isEnableRectangle();
	bool isEnableCircle();
	bool isEnableArrow();
	bool isEnableShapreRecognizer();

	void saveSettings();
	void loadSettings();

	void copyCurrentConfig();
	void restoreLastConfig();

	ArrayIterator<Tool*> iterator();

	void setSelectionEditTools(bool setColor, bool setSize);

	const double* getToolThickness(ToolType type);

protected:
	void initTools();

private:
	XOJ_TYPE_ATTRIB;

	Tool* tools[TOOL_COUNT];
	Tool* current;

	/**
	 * Last selected tool, reference with color values etc.
	 */
	LastSelectedTool* lastSelectedTool;

	EraserType eraserType;

	/**
	 * If a color is selected, it may be in the list,
	 * so its a "predefined" color for us, but may it is
	 * not in the list, so its a "custom" color for us
	 */
	bool colorFound;
	ToolListener* listener;
	ActionHandler* actionHandler;

	Settings* settings;
};
