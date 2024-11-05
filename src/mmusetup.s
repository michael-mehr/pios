# 0 "src/mmusetup.S"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "src/mmusetup.S"
# 38 "src/mmusetup.S"
    .section .data.mmu
    .balign 2

    mmu_lock: .4byte 0


    mmu_init: .4byte 0


    .section .text.mmu_on
    .balign 2
    .global mmu_on
    .type mmu_on, @function

mmu_on:

    ADRP x0, mmu_lock
    ADD x0, x0, :lo12:mmu_lock
    MOV w1, #1
    SEVL
1:
    WFE
    LDAXR w2, [x0]
    CBNZ w2, 1b
    STXR w3, w1, [x0]
    CBNZ w3, 1b

check_already_initialised:

    ADRP x1, mmu_init
    ADD x1, x1, :lo12:mmu_init
    LDR w2, [x1]
    CBNZ w2, end

zero_out_tables:

    LDR x2, =0x200000
    LDR x3, =0x2000
    LSR x3, x3, #5
    FMOV d0, xzr
1:
    STP q0, q0, [x2], #32
    SUBS x3, x3, #1
    B.NE 1b

load_descriptor_templates:

    LDR x2, =0x20000000000705
    LDR x3, =0x20000000000707
    LDR x4, =0x20000000000701
    LDR x5, =0x20000000000703
    LDR x20, =0x781
    LDR x21, =0x783


program_table_0:

    LDR x8, =0x200000
    LDR x9, =0x40000000

program_table_0_entry_0:

    LDR x10, =0
    LDR x11, =0x201000
    ORR x11, x11, #0x3
    STR x11, [x8, x10, lsl #3]
program_table_1:

    LDR x8, =0x201000
    LDR x9, =0x200000

program_table_1_entry_0:

    LDR x10, =0
    LDR x11, =1
    LDR x12, =0x0
1:
    ORR x12, x12, x4
    STR X12, [x8, x10, lsl #3]
    ADD x10, x10, #1
    ADD x12, x12, x9
    SUBS x11, x11, #1
    B.NE 1b

init_done:

    MOV w2, #1
    STR w2, [x1]

end:

    LDR x1, =0x200000
    MSR ttbr0_el1, x1
    LDR x1, =0xff
    MSR mair_el1, x1
    LDR x1, =0x803520
    MSR tcr_el1, x1
    ISB
    MRS x2, tcr_el1
    CMP x2, x1
    B.NE .
    LDR x1, =0x1005
    MSR sctlr_el1, x1
    ISB
    STLR wzr, [x0]
    RET
