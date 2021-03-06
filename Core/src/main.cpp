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

#include "EnvisionWindow.h"
#include "PluginManager.h"
#include "EnvisionApplication.h"
#include "EnvisionException.h"
#include "DefaultEnvisionManager.h"
#include "TestRunner.h"

// Enable core dumps of debug builds on Linux
#ifdef Q_OS_LINUX
#ifdef DEBUG
#include <sys/resource.h>
#endif
#endif

using namespace Core;

/**
 * This is the main executed when Envision is started. It shows the main window, loads all plug-ins and starts the event
 * loop.
 */
int main(int argc, char *argv[])
{
	EnvisionApplication a(argc, argv);

	// Enable core dumps of debug builds on Linux
#ifdef Q_OS_LINUX
#ifdef DEBUG
	struct rlimit core_limit;
	core_limit.rlim_cur = RLIM_INFINITY;
	core_limit.rlim_max = RLIM_INFINITY;

	if(setrlimit(RLIMIT_CORE, &core_limit) < 0)
		qDebug() << "Error while enabling core dumps:" << strerror(errno);
	else QFile::remove("./core");
#endif
#endif

	EnvisionWindow w;
	w.show();

	TestRunner testr;

	int retCode = 0;
	try
	{
		PluginManager pm;
		DefaultEnvisionManager manager;

		// Give the Envision manager all the information it needs to operate properly.
		manager.setPluginManager(&pm);
		manager.setMainWindow(&w);

		pm.loadAllPlugins(manager);

		testr.enqueueSelfTests(pm);

		QTextStream out(stdout);
		out << "==============================" << endl;

		retCode = a.exec();
	}
	catch (EnvisionException &e)
	{
		e.printError();
		retCode = 1;
	}

	return retCode;
}
