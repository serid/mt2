#include "ir.h"

#include <stdio.h>

#include "panic.h"
#include "util.h"
#include "vec_ir_StackItem.h"

static ir_StackItem safePopStackItem(vec_ir_StackItem* stack,
                                     char expected_tag) {
    if (vecIsEmpty_ir_StackItem(stack)) {
        fputs("Stack is empty!\n", stderr);
        switch (expected_tag) {
            case IR_STACK_ITEM_INT_LIT:
                fputs("Int literal expected.\n", stderr);
                break;
            case IR_STACK_ITEM_VAR_NUM:
                fputs("Variable number expected.\n", stderr);
                break;
            case IR_STACK_ITEM_IDENT:
                fputs("Identifier expected.\n", stderr);
                break;
            default:
                panic("Unknown identifier.\n");
                break;
        }
        exit(1);
    }
    ir_StackItem item = vecPop_ir_StackItem(stack);
    if (item.tag != expected_tag) {
        switch (expected_tag) {
            case IR_STACK_ITEM_INT_LIT:
                fputs("Int literal expected.\n", stderr);
                break;
            case IR_STACK_ITEM_VAR_NUM:
                fputs("Variable number expected.\n", stderr);
                break;
            case IR_STACK_ITEM_IDENT:
                fputs("Identifier expected.\n", stderr);
                break;
            default:
                panic("Unknown identifier.\n");
                break;
        }
        exit(1);
    }
    return item;
}

ir_Program compile(vec_Tok toks) {
    // Stack parser
    vec_ir_StackItem stack = vecNew_ir_StackItem();

    ir_Proc some_proc;
    some_proc.code = vecNew_ir_IrItem();
    ir_Program program;
    program.procs = vecNew_ir_Proc();

    for (size_t i = 0; i < toks.len; i++) {
        Tok* i_token = &toks.mem[i];
        if (i_token->tag == TOK_INT_LIT) {
            vecPush_ir_StackItem(
                &stack, (ir_StackItem){.tag = IR_STACK_ITEM_INT_LIT,
                                       .data.int_lit = i_token->data.int_lit});
        } else if (i_token->tag == TOK_VAR_NUM) {
            vecPush_ir_StackItem(
                &stack, (ir_StackItem){.tag = IR_STACK_ITEM_VAR_NUM,
                                       .data.var_num = i_token->data.var_num});
        } else if (i_token->tag == TOK_ASSIGN) {
            // Add an assignment to a procedure
            ir_StackItem what = safePopStackItem(&stack, IR_STACK_ITEM_INT_LIT);  // tos1

            ir_StackItem var_num = safePopStackItem(&stack, IR_STACK_ITEM_VAR_NUM);  // tos2

            vecPush_ir_IrItem(&some_proc.code,
                              (ir_IrItem){.var_num = var_num.data.var_num,
                                          .tag = IR_ITEM_TAG_INT_LIT,
                                          .data.int_lit = what.data.int_lit});
        } else if (i_token->tag == TOK_CALL) {
            // Call a function and add an assignment to a procedure
            ir_StackItem func_name = safePopStackItem(&stack, IR_STACK_ITEM_IDENT);  // tos1

            ir_StackItem arg1_varnum = safePopStackItem(&stack, IR_STACK_ITEM_VAR_NUM);  // tos2

            ir_StackItem arg2_varnum = safePopStackItem(&stack, IR_STACK_ITEM_VAR_NUM);  // tos3

            ir_StackItem var_num = safePopStackItem(&stack, IR_STACK_ITEM_VAR_NUM);  // tos4

            vecPush_ir_IrItem(
                &some_proc.code,
                (ir_IrItem){.var_num = var_num.data.var_num,
                            .tag = IR_ITEM_TAG_FUNC_CALL,
                            .data.func_call = (ir_FuncCall){
                                .func_name = str_clone(func_name.data.name),
                                .arg1_varnum = arg1_varnum.data.var_num,
                                .arg2_varnum = arg2_varnum.data.var_num}});
        } else if (i_token->tag == TOK_IDENT) {
            vecPush_ir_StackItem(
                &stack, (ir_StackItem){.tag = IR_STACK_ITEM_IDENT,
                                       .data.name = i_token->data.name});
        } else if (i_token->tag == TOK_MAKEPROC) {
            ir_StackItem name = safePopStackItem(&stack, IR_STACK_ITEM_IDENT);  // tos1

            some_proc.name = str_clone(name.data.name);
            vecPush_ir_Proc(&program.procs, some_proc);
        }
    }

    if (stack.len != 0) panic("Trailing tokens in program.\n");

    vecDestroy_ir_StackItem(&stack);

    return program;
}

void destroy_ir_IrItem(ir_IrItem* item) {
    if (item->tag == IR_ITEM_TAG_FUNC_CALL)
        free(item->data.func_call.func_name);
}

void destroy_ir_Proc(ir_Proc* proc) {
    for (size_t i = 0; i < proc->code.len; i++)
        destroy_ir_IrItem(&proc->code.mem[i]);
    free(proc->name);
    vecDestroy_ir_IrItem(&proc->code);
}

void destroy_ir_Program(ir_Program* program) {
    for (size_t i = 0; i < program->procs.len; i++)
        destroy_ir_Proc(&program->procs.mem[i]);
    vecDestroy_ir_Proc(&program->procs);
}
