# Versión mínima requerida de CMake. Se puede reducir o incrementar a riesgo del desarrollador.
# @see https://cmake.org/download/
cmake_minimum_required(VERSION 3.22)

# Nombre del proyecto, y lenguaje utilizado (C, en este caso).
project(Compiler C)

# Compilar el parser con Bison, generando contra-ejemplos en caso de que se presenten conflictos.
add_custom_command(
	OUTPUT ../src/frontend/syntactic-analysis/bison-parser.c ../src/frontend/syntactic-analysis/bison-parser.h
	COMMAND bison -Wcounterexamples -d ../src/frontend/syntactic-analysis/bison-grammar.y -o ../src/frontend/syntactic-analysis/bison-parser.c)

# Seleccionar estrategia según el compilador de C disponible en el sistema.
# @see https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
	message(NOTICE "El compilador de C es GCC.")

	# Opciones para GCC.
	add_compile_options(-static-libgcc)
	add_compile_options(-std=gnu99)
	add_compile_options(-O3)

	# Compilar el scanner con Flex.
	add_custom_command(
		OUTPUT ../src/frontend/lexical-analysis/flex-scanner.c
		COMMAND flex -o ../src/frontend/lexical-analysis/flex-scanner.c ../src/frontend/lexical-analysis/flex-patterns.l
		DEPENDS ../src/frontend/syntactic-analysis/bison-parser.c ../src/frontend/syntactic-analysis/bison-parser.h)

elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
	message(NOTICE "El compilador de C es Microsoft Visual Studio.")

	# Opciones para MSVC.
	# add_compile_options(...)

	# Compilar el scanner con Flex, usando compatibilidad con Microsoft Windows.
	add_custom_command(
		OUTPUT ../src/frontend/lexical-analysis/flex-scanner.c
		COMMAND flex --wincompat -o ../src/frontend/lexical-analysis/flex-scanner.c ../src/frontend/lexical-analysis/flex-patterns.l
		DEPENDS ../src/frontend/syntactic-analysis/bison-parser.c ../src/frontend/syntactic-analysis/bison-parser.h)

elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
	message(NOTICE "El compilador de C es LLVM Clang.")

	# Opciones para Clang.
	# add_compile_options(...)

	# Compilar el scanner con Flex.
	add_custom_command(
		OUTPUT ../src/frontend/lexical-analysis/flex-scanner.c
		COMMAND flex -o ../src/frontend/lexical-analysis/flex-scanner.c ../src/frontend/lexical-analysis/flex-patterns.l
		DEPENDS ../src/frontend/syntactic-analysis/bison-parser.c ../src/frontend/syntactic-analysis/bison-parser.h)
else ()
	message(NOTICE "El compilador de C es desconocido.")
	message(NOTICE "No se generará el scanner con Flex.")
	message(NOTICE "Incluya un 'elseif' adicional para manejar su compilador.")

endif ()

# Especificar punto de entrada del proyecto y códigos fuente (extensión *.c).
# Los *.h se incluyen automáticamente desde estos fuentes.
add_executable(Compiler
	src/main.c
	src/backend/code-generation/generator.c
	src/backend/domain-specific/calculator.c
	src/backend/semantic-analysis/symbol-scope/symbol-table/symbol-table.c
	src/backend/semantic-analysis/symbol-scope/scope/context.c
	src/backend/support/logger.c
	src/backend/support/assert.c
	src/frontend/lexical-analysis/flex-actions.c
	src/frontend/lexical-analysis/flex-scanner.c
	src/frontend/syntactic-analysis/bison-actions.c
	src/frontend/syntactic-analysis/bison-parser.c
	src/backend/semantic-analysis/ast/actions/program.c
	src/backend/semantic-analysis/ast/actions/assignment/assignment.c
	src/backend/semantic-analysis/ast/actions/block/block.c
	src/backend/semantic-analysis/ast/actions/constant/constant.c
	src/backend/semantic-analysis/ast/actions/declaration/declaration.c
	src/backend/semantic-analysis/ast/actions/expression/expression.c
	src/backend/semantic-analysis/ast/actions/factor/factor.c
	src/backend/semantic-analysis/ast/actions/for/for.c
	src/backend/semantic-analysis/ast/actions/functions/functions.c
	src/backend/semantic-analysis/ast/actions/if/if.c
	src/backend/semantic-analysis/ast/actions/instructions/instructions.c
	src/backend/semantic-analysis/ast/actions/member/member.c
	src/backend/semantic-analysis/ast/actions/property/property.c
	src/backend/semantic-analysis/ast/actions/statement/statement.c
	src/backend/semantic-analysis/ast/actions/vector/vector.c
	src/backend/semantic-analysis/ast/actions/while/while.c
	# Agregar otros archivos *.c (si no se incluyen, no se compilan).
	# ...
)

# Linkear el proyecto y sus librerías.
target_link_libraries(Compiler)
