/***********************************************************************************************************************
**
** Copyright (c) 2011, 2013 ETH Zurich
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
** following conditions are met:
**
**    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
**      disclaimer.
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
***********************************************************************************************************************/

#include "layouts/LayoutStyle.h"

namespace Visualization {

LayoutStyle::LayoutStyle(int leftMargin, int rightMargin, int topMargin, int bottomMargin) :
	leftMargin_(leftMargin), rightMargin_(rightMargin), topMargin_(topMargin), bottomMargin_(bottomMargin)
{
}

void LayoutStyle::setMargins(int marginSize)
{
	if ( marginSize >= 0 )
	{
		leftMargin_ = marginSize;
		rightMargin_ = marginSize;
		topMargin_ = marginSize;
		bottomMargin_ = marginSize;
	}
}

void LayoutStyle::setMargins(int left, int right, int top, int bottom)
{
	if ( left >= 0 ) leftMargin_ = left;
	if ( right >= 0 ) rightMargin_ = right;
	if ( top >= 0 ) topMargin_ = top;
	if ( bottom >= 0 ) bottomMargin_ = bottom;
}

void LayoutStyle::load(StyleLoader& sl)
{
	ItemStyle::load(sl);
	sl.load("leftMargin", leftMargin_);
	sl.load("topMargin", topMargin_);
	sl.load("rightMargin", rightMargin_);
	sl.load("bottomMargin", bottomMargin_);
}

}
