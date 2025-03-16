#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

#define OK 0
#define BAD 1
#define END 2
#define PASS 3
#define MEMORY 4
#define TREE_EMPTY -2
#define TREE_NOTFOUND -1
#define TREE_DUPLICATE -1

#define CONSOLE_MODE 0
#define TXTFILE_MODE 1
#define BINFILE_MODE 2

#define NOFILE NULL

#define SHORT_TYPE 1
#define INT_TYPE 2
#define UINT_TYPE 3

#define EMPTYRULE_FALSE false
#define EMPTYRULE_TRUE true


short dialogue_menu(Tree* tree)
{
        short panel = 1;
        short checker, guard;
        while (panel) {
                printf("Choose an option from the list below:\n"
                        "\t(1) Fill the tree with values from the file\n"
                        "\t(2) Insert (multiple) values into the tree\n"
                        "\t(3) Insert (one) a value into the tree\n"
                        "\t(4) Delete one info element from the tree\n"
                        "\t(5) Clear the tree\n"
                        "\t(6) Tree traversal (print)\n"
                        "\t(7) Print the tree\n"
                        "\t(8) Find elements by key\n"
                        "\t(9) Special search\n"
                        "\t(10) Finish the program\n");
                guard = read_int_inrange(&panel, SHORT_TYPE, 1, 11);
                if (guard == EOF || panel == 10) {
                        printf("Finishing the program\n");
                        return OK;
                }
                checker = dialog_switch(tree, panel);
                if (checker == BAD)
                        return BAD;
                if (checker == END)
                        return OK;
        }
        return OK;
}


short dialog_switch(Tree* tree, int panel)
{
        short checker = OK;
        switch (panel) {
        case 1:
                checker = dialog_fill_file(tree);
                if (checker) // может, вынести за свитч?
                // тогда по умолч ещё поставить OK, т.к. при clear ничего не будет в нём
                        return checker;
                // if (!checker)
                //      print();
                break;
        case 2:
                checker = dialog_insert_multiple(tree);
                if (checker)
                        return checker;
                break;
        case 3:
                checker = dialog_insert(tree);
                if (checker)
                        return checker;
                break;
        case 4:
                checker = dialog_delete(tree);
                if (checker)
                        return checker;
                break;
        case 5:
                printf("Clearing the tree...\n");
                job_clear(tree);
                break;
        case 6:
                checker = dialog_traversal(tree);
                if (checker)
                        return checker;
                break;
        case 7:
                checker = dialog_print(tree);
                if (checker)
                        return checker;
                break;
        case 8:
                checker = dialog_find(tree, 0);
                if (checker)
                        return checker;
                break;
        case 9:
                checker = dialog_find(tree, 1);
                if (checker)
                        return checker;
                break;
        }
        if (checker)
                return checker;
        return OK;
}


short dialog_fill_file(Tree* tree)
{
        short checker;
        FILE* file;
        checker = dialog_get_file(&file, "r\0\0");
        if (checker)
                return checker;

        short guard = EOF + 1;
        char* key;
        unsigned int info;
        while (guard != EOF) {
                guard = readline(&key, file, TXTFILE_MODE, EMPTYRULE_FALSE);
                if (guard == EOF) {
                        fclose(file);
                        return OK;
                }
                if (!guard) {
                        printf("Memory allocation error!\n");
                        fclose(file);
                        return BAD;
                }
                guard = scanfUIntType(&info, file, TXTFILE_MODE);
                if (guard == EOF || !guard) {
                        if (guard == EOF)
                                printf("One key has no info in pair!\n");
                        fclose(file);
                        free(key);
                        return OK;
                }
                checker = job_insert(tree, key, info, NULL);
                if (checker == MEMORY) {
                        printf("Memory allocation error!\n");
                        fclose(file);
                        free(key);
                        return BAD;
                }
        }
        // fclose(file); // а сюда и не дойдёт
        return OK;
}


short dialog_insert_multiple(Tree* tree)
{
        short guard;
        unsigned int amount;
        printf("Number of values to insert:\n");
        guard = scanfUIntType(&amount, NULL, CONSOLE_MODE);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program\n");
                return END;
        }
        short checker;
        for (int i = 0; i < amount; i++) {
                printf("Value #%d:\n", i + 1);
                checker = dialog_insert(tree);
                if (checker) {
                        return checker;
                }
        }
        return OK;
}


short dialog_insert(Tree* tree)
{
        short guard;
        char* key;
        unsigned int info;
        printf("Key to insert (string):\n");
        guard = readline(&key, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program\n");
                return END;
        }
        if (!guard) {
                printf("Memory allocation error!\n");
                return BAD;
        }
        printf("Info to insert (integer >= 0):\n");
        guard = scanfUIntType(&info, NULL, CONSOLE_MODE);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program\n");
                free(key);
                return END;
        }
        unsigned int previnfo;
        printf("Inserting the value into the tree...\n");
        short checker = job_insert(tree, key, info, &previnfo);
        if (checker == MEMORY) {
                printf("Memory allocation error!\n");
                free(key);
                return BAD;
        }
        if (checker == TREE_DUPLICATE)
                printf("Key duplicate was found!\n"
                        "previously: \"%s\" - %u\n", key, previnfo);
        return OK;
}


short dialog_delete(Tree* tree)
{
        short guard;
        char* key;
        printf("Key to delete (string):\n");
        guard = readline(&key, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program\n");
                return END;
        }
        if (!guard) {
                printf("Memory allocation error!\n");
                return BAD;
        }
        printf("Deleting the value from the tree...\n");
        short checker = job_delete(tree, key);
        free(key);
        if (checker == MEMORY) {
                printf("Memory allocation error!\n");
                return BAD;
        }
        if (checker == -2) {
                printf("The tree is empty!\n");
                return PASS;
        }
        if (checker == -1) {
                printf("Nothing to delete was found!\n");
                return PASS;
        }
        return OK;
}


short dialog_traversal(Tree* tree)
{
        short guard, mode;
        printf("Which traversal to do:\n"
                "(0 - inOrder, -1 - preOrder, 1 - postOrder)\n");
        guard = read_int_inrange(&mode, SHORT_TYPE, -1, 1);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program\n");
                return END;
        }
        char* key;
        printf("Type a min key (string):\n"
                "(just press ENTER if should print all keys)\n");
        guard = readline(&key, NOFILE, CONSOLE_MODE, EMPTYRULE_TRUE);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program\n");
                return END;
        }
        if (!guard) {
                printf("Memory allocation error!\n");
                return BAD;
        }
        printf("Traversing the tree...\n");
        job_traversal(tree, key, mode);
        free(key);
        return OK;
}


short dialog_print(Tree* tree)
{
        short guard, mode;
        printf("Where to output the tree:\n"
                "(0 - console, 1 - txt file, 2 - graphviz)\n");
        guard = read_int_inrange(&mode, SHORT_TYPE, 0, 2);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program\n");
                return END;
        }
        short checker;
        switch (mode) {
        case 0:
                checker = dialog_print_console(tree);
                break;
        case 1:
                checker = dialog_print_txtfile(tree);
                break;
        case 2:
                checker = dialog_print_graphviz(tree);
                break;
        }
        if (checker)
                return checker;
        return OK;
}


short dialog_print_console(Tree* tree)
{
        short guard, mode;
        // deep и breadth вроде, но предлог? типа в глубину, а у них in deep?
        printf("в глубину (громоздко) - 0 или в ширину - 1?\n");
        guard = read_int_inrange(&mode, SHORT_TYPE, 0, 1);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program\n");
                return END;
        }
        printf("Printing the tree...\n");
        // доделать: выбрать вид, ну или как там сделать, короче в консоль или graphviz
        short checker = job_print(tree, NOFILE, mode);
        if (checker) {
                printf("Memory allocation error!\n");
                return BAD;
        }
        return OK;
}


short dialog_print_txtfile(Tree* tree)
{
        short mode = 2;
        FILE* file;
        short checker = dialog_get_file(&file, "w\0\0");
        if (checker)
                return checker;

        printf("Printing the tree...\n");
        job_print(tree, file, mode);
        fclose(file);
        return OK;
}


short dialog_print_graphviz(Tree* tree)
{
        short checker;
        FILE* file;
        printf("(need to add \".dot\" at the end of filename)");
        checker = dialog_get_file(&file, "w\0\0");
        if (checker) return checker;

        checker = job_print(tree, file, 3);
        fclose(file);
        if (checker) return checker;
        return OK;
}


short dialog_find(Tree* tree, short mode)
{
        short guard;
        char* key;
        printf("Key to find (string):\n");
        guard = readline(&key, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program\n");
                return END;
        }
        if (!guard) {
                printf("Memory allocation error!\n");
                return BAD;
        }
        char* foundkey;
        unsigned int foundinfo;
        printf("Finding the values in the tree...\n");
        short checker = job_find(tree, key, mode, &foundkey, &foundinfo);
        free(key);
        if (checker == -2) {
                printf("The tree is empty!\n");
                return PASS;
        }
        if (checker == -1) {
                printf("The key was not found!\n");
                return PASS;
        }

        printf("The key was found:\n"
                "\"%s\" - %u\n", foundkey, foundinfo);
        return OK;
}


short dialog_get_file(FILE** file, char filemode[3])
{
        short guard;
        char* filename;
        printf("Name of file to open:\n");
        guard = readline(&filename, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program\n");
                return END;
        }
        if (!guard) {
                printf("Memory allocation error!\n");
                return BAD;
        }
        *file = fopen(filename, filemode);
        free(filename);
        if (!*file) {
                printf("File opening error!\n");
                return PASS;
        }
        return OK;
}