#include <cstdlib>

#define LUA_COMPAT_MODULE 1

#include <lua.hpp>

//#pragma comment(lib, "lua.so");

/*
	lua 调用 c++函数

*/

void lua_table_dump(lua_State *L, int index)
{
	int top = lua_gettop(L);

	// 把栈上给定索引处的元素作一个副本压栈
	lua_pushvalue(L, index);

	lua_pushnil(L);

	fprintf(stdout, "{\n");

	while(lua_next(L, -2) != 0) // key + value
	{
		fprintf(stdout, "\t");

		// print key
		int key_type = lua_type(L, -2);
		switch(key_type)
		{
			case LUA_TSTRING:
		             fprintf(stdout, "%s", lua_tostring(L, -2));
			break;

			case LUA_TBOOLEAN:
			     fprintf(stdout, "%s", lua_toboolean(L, -2) ? "true" : "false");
			break;

			case LUA_TNUMBER:
			     fprintf(stdout, "%g", lua_tonumber(L, -2));
			break;

			default:
			    fprintf(stdout, "%s:%p", lua_typename(L, -2), lua_topointer(L, -2));
			break;
		}
		

		// print value
		fprintf(stdout, "\t\t=\t");

		int value_type = lua_type(L, -1);

		switch(value_type)
		{
			case LUA_TSTRING:
		         fprintf(stdout, "%s", lua_tostring(L, -1));
			break;

			case LUA_TBOOLEAN:
			     fprintf(stdout, "%s", lua_toboolean(L, -1) ? "true" : "false");
			break;

			case LUA_TNUMBER:
			     fprintf(stdout, "%g", lua_tonumber(L, -1));
			break;

			case LUA_TFUNCTION:
			     fprintf(stdout, "%s:%p", lua_typename(L, -1), lua_topointer(L, -1));
			break;

			case LUA_TUSERDATA:
			     fprintf(stdout, "%s:%s", lua_typename(L, -1), lua_tostring(L, -1));
			break;

			default:
			    fprintf(stdout, "%s:%p", lua_typename(L, -1), lua_topointer(L, -1));
			break;
		}

		//

		fprintf(stdout, "\n");
		
		lua_pop(L, 1);
	}

	fprintf(stdout, "}\n");

	lua_settop(L, top);
}

// 打印栈
void lua_stack_dump(lua_State *L)
{
	int i = 0;
	int top = lua_gettop(L);

	printf("-------------------- lua start %d --------------------\n", top);

	for(int i=1; i<=top; ++i)
	{
		int t = lua_type(L, i); // 获取类型

		printf("type: %s, value:", lua_typename(L, t));


		switch(t)
		{
			case LUA_TSTRING:
		             printf("%s", lua_tostring(L, i));
			break;

			case LUA_TBOOLEAN:
		             printf(lua_toboolean(L, i) ? "true" : "false");
			break;

			case LUA_TNUMBER:
		             printf("%g", lua_tonumber(L, i));
			break;

			case LUA_TTABLE:
		            lua_table_dump(L, i);
			break;

			default:
				printf("%s", lua_typename(L, t));
			break;
		}
		printf("\n");
	}	

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
	setvbuf(stdout,NULL,_IONBF,0);
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
	lua_stack_dump(L);
	luaL_dostring(L, "mylibx.test1(100, 300)");
	
	

	lua_close(L);

	exit(EXIT_SUCCESS);
}
