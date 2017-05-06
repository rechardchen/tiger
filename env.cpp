#include "env.h"
#include "type.h"

namespace tiger {

	namespace env {

		tiger::VarEnv baseVEnv()
		{
			//TODO: add version number etc
			return VarEnv();
		}

		tiger::FuncEnv baseFEnv()
		{
			//TODO: add built-in functions
			return FuncEnv();
		}

		tiger::TypeEnv baseTEnv()
		{
			TypeEnv tenv;
			
			//TODO: add float types and more int types
			tenv.Enter("int", IntType());
			tenv.Enter("string", StringType());

			return tenv;
		}

	}

}