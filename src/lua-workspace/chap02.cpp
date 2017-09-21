#include <cstdlib>

#define LUA_COMPAT_MODULE 1

#include <lua.hpp>

//#pragma comment(lib, "lua.so");

/*
	lua 调用 c++函数

*/



// 打印栈
void lua_stack_dump(lua_State *L)
{
	int i = 0;
	int top = lua_gettop(L);
	printf("-------------------- lua start %d --------------------\n", top);
	
	printf("-------------------- lua end --------------------\n");
}

// lua注册函数与宿主函数分离
int add_func(lua_State *L)
{
	int a = lua_tointeger(L, 1);
	int b = lua_tointeger(L, 2);

	lua_pushinteger(L, a+b);	
	printf("%d+%d=%d \n", a, b, a+b);

	// 1表示压入栈数据个数

	return 1;
}

luaL_Reg   funcs_mylib[] =
{
	{"test1", add_func},
	{"test2", add_func},
	{"test3", add_func},
	{"test4", add_func},
	{0,0},
};

int func_add_test1(lua_State* L)
{
	luaL_newlib(L, funcs_mylib);
	return 1;
}

int main(int argc, char* argv[])
{

	lua_State *L = luaL_newstate();
		
	luaopen_base(L);
	luaopen_table(L);
	luaopen_io(L);
	luaopen_string(L);

	// 将函数暴露给lua脚本， 1个函数
	// 方法1 注册c++函数到Lua栈，全局
	//lua_register(L, "load_add_func", add_func);
	//luaL_dostring(L, "load_add_func(111, 333)");
	
	// 方法2  批量加入函数, 会在全局库中添加 mylib
	//luaL_openlib(L, "mylib", funcs_mylib, 0);
	//luaL_dostring(L, "mylib.test1(100, 300)");

	// 方法3 推荐, 不会在全局库中添加
	luaL_requiref(L, "mylibx", func_add_test1, 1);
	luaL_dostring(L, "mylibx.test1(100, 300)");

	lua_close(L);

	exit(EXIT_SUCCESS);
}
