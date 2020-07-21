#include "ir.h"

#include "panic.h"
#include "util.h"
#include "vec_ir_StackItem.h"

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
        } else if (i_token->tag == TOK_ASSIGN) {
            // Add an assignment to a procedure
            ir_StackItem what = vecPop_ir_StackItem(&stack);  // tos1
            if (what.tag != IR_STACK_ITEM_INT_LIT) {
                panic("Int literal expected.");
            }

            ir_StackItem var_num = vecPop_ir_StackItem(&stack);  // tos2
            if (what.tag != IR_STACK_ITEM_INT_LIT) {
                panic("Int literal (varnum) expected.");
            }

            vecPush_ir_IrItem(&some_proc.code,
                              (ir_IrItem){.var_num = var_num.data.int_lit,
                                          .tag = IR_ITEM_TAG_INT_LIT,
                                          .data.int_lit = what.data.int_lit});
        } else if (i_token->tag == TOK_CALL) {
            // Call a function and add an assignment to a procedure
            ir_StackItem func_name = vecPop_ir_StackItem(&stack);  // tos1
            if (func_name.tag != IR_STACK_ITEM_IDENT) {
                panic("Identifier expected.");
            }

            ir_StackItem arg1_varnum = vecPop_ir_StackItem(&stack);  // tos2
            if (arg1_varnum.tag != IR_STACK_ITEM_INT_LIT) {
                panic("Int literal expected.");
            }

            ir_StackItem arg2_varnum = vecPop_ir_StackItem(&stack);  // tos3
            if (arg2_varnum.tag != IR_STACK_ITEM_INT_LIT) {
                panic("Int literal expected.");
            }

            ir_StackItem var_num = vecPop_ir_StackItem(&stack);  // tos4
            if (var_num.tag != IR_STACK_ITEM_INT_LIT) {
                panic("Int literal expected.");
            }

            vecPush_ir_IrItem(
                &some_proc.code,
                (ir_IrItem){.var_num = var_num.data.int_lit,
                            .tag = IR_ITEM_TAG_FUNC_CALL,
                            .data.func_call = (ir_FuncCall){
                                .func_name = str_clone(func_name.data.name),
                                .arg1_varnum = arg1_varnum.data.int_lit,
                                .arg2_varnum = arg2_varnum.data.int_lit}});
        } else if (i_token->tag == TOK_IDENT) {
            vecPush_ir_StackItem(
                &stack, (ir_StackItem){.tag = IR_STACK_ITEM_IDENT,
                                        .data.name = i_token->data.name});
        } else if (i_token->tag == TOK_MAKEPROC) {
            ir_StackItem name = vecPop_ir_StackItem(&stack);  // tos1
            if (name.tag != IR_STACK_ITEM_IDENT) {
                panic("Identifier expected.");
            }

            some_proc.name = str_clone(name.data.name);
            vecPush_ir_Proc(&program.procs, some_proc);
        }
    }

    if (stack.len != 0) panic("Trailing tokens in program.");

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

