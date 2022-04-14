#pragma once

#define SINGLE(TYPE) friend class CSingleton<TYPE>;\
					 private:\
						TYPE();\
						~TYPE();