/***********************************************************************************************************************
 **
 ** Copyright (c) 2011, 2013 ETH Zurich
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 ** following conditions are met:
 **
 **    * Redistributions of source code must retain the above copyright notice, this list of conditions and the
 **      following disclaimer.
 **    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 **      following disclaimer in the documentation and/or other materials provided with the distribution.
 **    * Neither the name of the ETH Zurich nor the names of its contributors may be used to endorse or promote products
 **      derived from this software without specific prior written permission.
 **
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 ** INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 ** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 ** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 ** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **
 **********************************************************************************************************************/

#include "UnaryOperatorStringOffsetProvider.h"
#include "Cell.h"

#include "OOVisualization/src/expressions/VUnaryOperation.h"

namespace OOInteraction {

UnaryOperatorStringOffsetProvider::UnaryOperatorStringOffsetProvider(OOVisualization::VUnaryOperation* vis)
	: GridBasedOffsetProvider(vis), vis_(vis)
{
	if (vis->node()->op() == OOModel::UnaryOperation::PARENTHESIS)
	{
		add(new Cell(1, vis->expression(), 1));
		setSize(3, 1);
	}
	else
		for(int i = 0; i<vis->layout()->length(); ++i)
			add(new Cell(i, vis->layout()->at<Visualization::Item>(i), i));
}

QStringList UnaryOperatorStringOffsetProvider::components()
{
	QStringList components = StringOffsetProvider::components();

	if (components.size() != vis_->layout()->length())
	{
		for (int i = components.size() - 1; i>=0; --i)
			if (components[i].isNull())
				components.removeAt(i);
	}
	if (components.size() != vis_->layout()->length())
		components.removeAll(QString(""));

	return components;
}

} /* namespace OOInteraction */