#include <cstdlib>
#include <lua.hpp>

//#pragma comment(lib, "lua.so");

/*
	lua 环境建立
	lua 打印字符串
	lua 脚本调用
	lua 栈打印
*/
// 打印栈
void lua_stack_dump(lua_State *L)
{
	int i = 0;
	int top = lua_gettop(L);
	printf("-------------------- lua start %d --------------------\n", top);
	
	printf("-------------------- lua end --------------------\n");
}

int main(int argc, char* argv[])
{

	lua_State *L = luaL_newstate();
		
	luaopen_base(L);
	luaopen_table(L);
	luaopen_io(L);
	luaopen_string(L);

	luaL_dostring(L, "print('hello lua')"); // 打印字符串

	// 执行 add.lua
	luaL_dofile(L, "add.lua");

	lua_getglobal(L, "addFunc");
	lua_pushinteger(L, 20);
	lua_pushinteger(L, 30);

	lua_call(L, 2, 1);

	int result = lua_tointeger(L, -1); // -1 表示栈顶
	lua_pop(L, 1); // 清空栈

	printf("result = %d \n", result);

	lua_close(L);

	exit(EXIT_SUCCESS);
}
