#include <stdio.h>
#include <stdint.h>
#include <jit/jit.h>

#include "hashmap.h"

jit_context_t context;
HashMap* symbol_table;

/* AST Nodes definition */

typedef struct _Value
{
    int number;
} Value;


typedef struct _Identifier
{
    char* name; 

} Identifier;


typedef struct _Assignment
{   
    Identifier* identifier;
    Value* value;

} Assignment;


typedef struct _Statement
{
    Assignment* assignment;

} Statement;



jit_function_t get_jit_function_for_integer_assignment(){

    jit_type_t params[]={jit_type_ulong, jit_type_uint};

    jit_type_t signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, 2, 1);

    jit_function_t function = jit_function_create(context, signature);

    jit_value_t address_to_assign =  jit_value_get_param(function, 0);
    jit_value_t value_to_store =  jit_value_get_param(function, 1);
    
    jit_insn_store_relative(function,address_to_assign,0,value_to_store);

    jit_function_compile(function);

    return function;
}

void compile_and_run_assignment(Assignment* assignment){
      jit_function_t function = get_jit_function_for_integer_assignment();
      int64_t address_to_assign = (int64_t)hashmap_get(symbol_table, assignment->identifier->name);
      void *args[] = { &address_to_assign, &(assignment->value->number)};
      if(jit_function_apply(function, args, NULL)==0){
          printf("Failed to execute function");
      };
}

void compile_and_run_statement(Statement* statement){
    if(statement->assignment!=NULL){
        compile_and_run_assignment(statement->assignment);
    }
}

void initiate_jit(){
  context = jit_context_create();
  jit_context_build_start(context);

}

void initiate_symbol_table(){
  symbol_table = hashmap(INTEGER);
}

void destroy_jit(){
  jit_context_destroy(context);
}

void destroy_symbol_table(){
  free_hashmap(symbol_table);
}

int main(){

    /* Initiate contexts */

    initiate_jit();
    initiate_symbol_table();

    /* Create variable in symbol table with its memory slot */

    int my_var_slot = 0;
    hashmap_put(symbol_table, "my_variable", &my_var_slot);

    /* AST which represents int my_variable=8765432 */
    
    Value value = { .number = 65489 };
    Identifier identifier = { .name = "my_variable" };
    Assignment assignment = { .identifier=&identifier,  .value=&value };
    Statement statement={ .assignment=&assignment };

    compile_and_run_statement(&statement);

    printf("My Variable value: %d\n", my_var_slot);

    /* Destroy contexts */
    
    destroy_symbol_table();
    destroy_jit();
    
}



