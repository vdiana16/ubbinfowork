#include <iostream>
#include "teste.h"
#include "ui.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using std::cout;

int main() {
	{
		Teste rteste;
		rteste.runTeste();
		RepoProdus rep;
		ProdusValidator val;
		ServiceProdus srv{ rep,val };
		UI ui{ srv };
		ui.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
