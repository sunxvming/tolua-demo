extern "C"
{
#include "lualib.h"
#include "lauxlib.h"
}

#include "tfunction.h"


int main (void)
{
	int  tolua_tfunction_open (lua_State*);
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	 // 此方法是pkg文件生成的cpp文件中的方法，作用是将cpp类的属性和方法导入到lua环境栈中
	 // 见:tfunctionbind.cpp
	tolua_tfunction_open(L); 

	luaL_dofile(L,"tfunction.lua");

	lua_close(L);
	return 0;
}

