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

#include "nodes/Float.h"
#include "commands/FieldSet.h"
#include "ModelException.h"

#include "ModelBase/src/nodes/TypedListDefinition.h"
DEFINE_TYPED_LIST(Model::Float)

namespace Model {

NODE_DEFINE_TYPE_REGISTRATION_METHODS(Float, Node)

Float::Float(Node *parent) :
	Node(parent), value(0.0)
{
}

Float::Float(Node *parent, PersistentStore &store, bool) :
	Node(parent)
{
	value = store.loadDoubleValue();
}

void Float::set(const double& newValue)
{
	execute(new FieldSet<double> (this, value, newValue));
}

void Float::save(PersistentStore &store) const
{
	store.saveDoubleValue(value);
}

void Float::load(PersistentStore &store)
{
	if (store.currentNodeType() != typeName())
		throw ModelException("Trying to load a Float node from an incompatible node type " + store.currentNodeType());

	set(store.loadDoubleValue());
}

}
