# Simple JIT Prototype using libjit

Simple JIT Engine prototype , supports only integer variable assignment.

## To Compile and Run

You need to place the libjit paths properly in Makefile, Before running these commands.

```
make engine
./engine
```

```c
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

    /* Prints  My Variable value: 65489*/
    printf("My Variable value: %d\n", my_var_slot); 

    /* Destroy contexts */
    
    destroy_symbol_table();
    destroy_jit();
    
}
```

Prints, "My Variable value: 65489"
