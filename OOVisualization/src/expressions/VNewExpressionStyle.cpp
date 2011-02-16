/***********************************************************************************************************************
 * VNewExpressionStyle.cpp
 *
 *  Created on: Feb 14, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "expressions/VNewExpressionStyle.h"
#include "VisualizationBase/headers/Styles.h"

namespace OOVisualization {

VNewExpressionStyle* VNewExpressionStyle::getDefault()
{
	static VNewExpressionStyle defaultStyle;
	return &defaultStyle;
}

void VNewExpressionStyle::load()
{
	ItemStyle::load();

	Visualization::Styles::load("container", container_);
	Visualization::Styles::load("newSymbol", newSymbol_);
	Visualization::Styles::load("amountSymbol", amountSymbol_);
}

}