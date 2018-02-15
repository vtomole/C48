# include "print-bison-merge.h" 
void print_pair(object *pair) {
    object *car_obj;
    object *cdr_obj;
    
    car_obj = car(pair);
    cdr_obj = cdr(pair);
    print(car_obj);
    if (cdr_obj->obj_type == PAIR) {
        printf(" ");
        print_pair(cdr_obj);
    }
    else if (cdr_obj->obj_type == EMPTY_LIST) {
        return;
    }
    else {
        printf(" . ");
        print(cdr_obj);
    }
}

void print(object *obj) {
    char c;
    char *str;
    
    switch (obj->obj_type) {
        case EMPTY_LIST:
            printf("()");
            break;
        case BOOLEAN:
            printf("#%c", falsep(obj) ? 'f' : 't');
            break;
        case SYMBOL:
            printf("%s", obj->symbol);
            break;
        case NUMBER:
            printf("%d", obj->number);
            break;
        case CHARACTER:
            c = obj->character;
            printf("#\\");
            switch (c) {
                case '\n':
                    printf("newline");
                    break;
                case ' ':
                    printf("space");
                    break;
                default:
                    putchar(c);
            }
            break;
        case STRING:
            str = obj->string;
            putchar('"');
            while (*str != '\0') {
                switch (*str) {
                    case '\n':
                        printf("\\n");
                        break;
                    case '\\':
                        printf("\\\\");
                        break;
                    case '"':
                        printf("\\\"");
                        break;
                    default:
                        putchar(*str);
                }
                str++;
            }
            putchar('"');
            break;
        case PAIR:
            printf("(");
            print_pair(obj);
            printf(")");
            break;
        case PRIMITIVE_PROCEDURE:
        case COMPOUND_PROCEDURE:
            printf("#<procedure>");
            break;
        default:
            fprintf(stderr, "cannot write unknown type\n");
            exit(1);
    }
}
