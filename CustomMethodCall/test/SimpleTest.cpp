/***********************************************************************************************************************
 * SimpleTest.cpp
 *
 *  Created on: Mar 24, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "custommethodcall.h"
#include "SelfTest/headers/SelfTestSuite.h"

#include "CustomVisualization.h"

#include "OOModel/headers/allOOModelNodes.h"

#include "VisualizationBase/headers/node_extensions/Position.h"
#include "VisualizationBase/headers/Scene.h"
#include "VisualizationBase/headers/views/MainView.h"

using namespace OOModel;
using namespace Visualization;

namespace CustomMethodCall {

Class* addCollection(Model::Model* model, Project* parent)
{
	Class* col = NULL;

	if (!parent) col = dynamic_cast<Class*> (model->createRoot("Class"));
	model->beginModification(parent ? static_cast<Model::Node*> (parent) :col, "Adding a collection class.");
	if (!col) col = parent->classes()->append<Class>();

	col->setName("Collection");
	col->setVisibility(Visibility::PUBLIC);

	Method* find = col->methods()->append<Method>();
	find->setName("find");
	find->extension<CustomVisualization>()->setVisName("FindMethodVis");
	FormalArgument* findArg = find->arguments()->append<FormalArgument>();
	findArg->setType<PrimitiveType>()->setType(PrimitiveType::INT);
	findArg->setName("x");
	find->results()->append<FormalResult>()->setType<PrimitiveType>()->setType(PrimitiveType::INT);

	Method* insert = col->methods()->append<Method>();
	insert->setName("insert");
	insert->extension<CustomVisualization>()->setVisName("InsertMethodVis");
	insert->extension<Position>()->setY(100);
	FormalArgument* insertArg = insert->arguments()->append<FormalArgument>();
	insertArg->setType<PrimitiveType>()->setType(PrimitiveType::INT);
	insertArg->setName("x");

	Method* empty = col->methods()->append<Method>();
	empty->setName("empty");
	empty->extension<CustomVisualization>()->setVisName("EmptyMethodVis");
	empty->extension<Position>()->setY(200);
	empty->results()->append<FormalResult>()->setType<PrimitiveType>()->setType(PrimitiveType::BOOLEAN);

	Method* exists = col->methods()->append<Method>();
	exists->setName("exists");
	exists->extension<CustomVisualization>()->setVisName("ExistsMethodVis");
	exists->extension<Position>()->setY(300);
	FormalArgument* existsArg = exists->arguments()->append<FormalArgument>();
	existsArg->setType<PrimitiveType>()->setType(PrimitiveType::INT);
	existsArg->setName("x");
	exists->results()->append<FormalResult>()->setType<PrimitiveType>()->setType(PrimitiveType::BOOLEAN);

	Method* test = col->methods()->append<Method>();
	test->setName("test");
	test->extension<Position>()->setX(300);

	MethodCallStatement* findCall = test->items()->append<MethodCallStatement>();
	findCall->ref()->set("method:find");
	findCall->arguments()->append<IntegerLiteral>()->setValue(42);

	MethodCallStatement* insertCall = test->items()->append<MethodCallStatement>();
	insertCall->ref()->set("method:insert");
	insertCall->arguments()->append<IntegerLiteral>()->setValue(-19);

	MethodCallStatement* emptyCall = test->items()->append<MethodCallStatement>();
	emptyCall->ref()->set("method:empty");

	MethodCallStatement* existsCall = test->items()->append<MethodCallStatement>();
	existsCall->ref()->set("method:exists");
	existsCall->arguments()->append<IntegerLiteral>()->setValue(101);


	model->endModification();
	return col;
}

TEST(CustomMethodCall, CustomVisTest)
{
	Scene* scene = new Scene();

	////////////////////////////////////////////////// Create Model
	Model::Model* model = new Model::Model();

	Class* collection = NULL;
	collection = addCollection(model, NULL);

	////////////////////////////////////////////////// Set Scene
	Model::Node* top_level = NULL;
	if(collection) top_level = collection;

	scene->addTopLevelItem( scene->defaultRenderer()->render(NULL, top_level) );
	scene->scheduleUpdate();
	scene->listenToModel(model);

	// Create view
	MainView* view = new MainView(scene);

	CHECK_CONDITION(view != NULL);
}

}
